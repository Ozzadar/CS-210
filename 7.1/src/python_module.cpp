/*
 *  python_module.cpp
 *
 *  Date: Feb 13th 2022
 *  Author: Paul Mauviel
 */

#include "python_module.h"
#include <iostream>

PythonModule::PythonModule(const std::string &modulePath) {
    // Initialize the interpreter
    Py_Initialize();

    // We need to add the current working directory
    // to python path so that it can find our local python modules
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("import os");
    PyRun_SimpleString("sys.path.append(os.getcwd())");

    // Load the python module
    auto* pythonModuleName = PyUnicode_FromString(modulePath.c_str());
    m_pyModule = PyImport_Import(pythonModuleName);

    // we no longer need the module name, so let's remove the reference count
    Py_DECREF(pythonModuleName);

    // If the module failed to load, stop processing and shut down the interpreter.
    if (!m_pyModule || !PyModule_Check(m_pyModule)) {
        std::cerr << "Failed to load python module: " << modulePath << std::endl;
        Py_Finalize();
        return;
    }

    // Load the python dictionary
    m_pyDict = PyModule_GetDict(m_pyModule);

    // if the dictionary doesn't load, something went wrong. Print the error and shut down
    if (!m_pyDict || !PyDict_Check(m_pyDict)) {
        // decrease the reference count of the module
        Py_DECREF(m_pyModule);
        m_pyModule = nullptr;

        std::cerr << "Failed to load python dictionary for module: " << modulePath << std::endl;
        Py_Finalize();
        return;
    }

    // We can now interate through the dictionary of tokens
    // These pyobjects are going to be borrowed references so no need
    // to decref
    PyObject *key, *value;
    Py_ssize_t pos = 0;

    while (PyDict_Next(m_pyDict, &pos, &key, &value)) {
        // if the token is a function, add it to the function list
        if (PyCallable_Check(value)) {
            m_moduleFunctions[PyUnicode_AsUTF8AndSize(key, nullptr)] = value;
        }
    }

    // everything is loaded, mark module as valid
    m_isValid = true;
}

PythonModule::~PythonModule() {
    if (IsValid()) {
        // We need to decrease the reference counts appropriately
        Py_DECREF(m_pyModule);

        // Shut down the interpreter
        Py_Finalize();
    }
}

bool PythonModule::hasFunction(const std::string& functionName) const {
    return m_moduleFunctions.count(functionName);
}


PyObject *PythonModule::callFunc(const std::string& functionName, const std::vector<Parameter>& params) const {

    if (!IsValid()) {
        std::cerr << "Module is invalid! Cannot call functions!" << std::endl;
        return nullptr;
    }

    if (!hasFunction(functionName)) {
        std::cerr << "Function " << functionName << " does not exist." << std::endl;
        return nullptr;
    }

    // We build a tuple of appropriate size to pass as the function parameters
    auto pyParams = PyTuple_New(static_cast<Py_ssize_t>(params.size()));

    for (int i = 0; i < params.size(); i++) {
        auto param = params[i];

        // PyTuple_SET_ITEM steals ownership of the python object provided
        // Working nicely with our GetPyValue ownership structure
        PyTuple_SET_ITEM(pyParams, i, GetPyValue(param));
    }

    auto result = PyObject_CallObject(m_moduleFunctions.at(functionName), pyParams);

    Py_DECREF(pyParams);

    return result;
}
