/*
 *  python_module.h
 *
 *  Date: Feb 13th 2022
 *  Author: Paul Mauviel
 */

#ifndef INC_7_1_PYTHON_MODULE_H
#define INC_7_1_PYTHON_MODULE_H

#include <Python.h>
#include <string>
#include <unordered_map>
#include <any>
#include <iostream>
#include <type_traits>

enum class ParamType {
    Integer,
    Floating,
    Boolean,
    String
};

struct Parameter {
    ParamType type;
    std::any value;
};

// This function will be leaky. It's assumed that the consumer
// is going to take ownership of this python reference
// It's static to make more clear that this function does not own the object
[[nodiscard]] static  PyObject* GetPyValue(Parameter param) {
    switch (param.type) {
        case ParamType::Integer:
            return PyLong_FromLong(std::any_cast<int>(param.value));
        case ParamType::Floating:
            return PyFloat_FromDouble(std::any_cast<double>(param.value));
        case ParamType::Boolean:
            return PyBool_FromLong(std::any_cast<bool>(param.value));
        case ParamType::String:
            return PyUnicode_FromString(std::any_cast<std::string>(param.value).c_str());
    }
}

template <typename T>
static std::enable_if_t<!std::is_same_v<T, std::string>, T> GetValueFromPython(PyObject* value) {
    if (!value) return T{};

    if (std::is_same_v<T, int>) {
        return PyLong_AsLong(value);
    }

    else if (std::is_same_v<T, double> || std::is_same_v<T, float>) {
        return PyFloat_AsDouble(value);
    }

    else if (std::is_same_v<T, bool>) {
        return static_cast<bool>(PyLong_AsLong(value));
    }

    return T{};
}

template <typename T>
static std::enable_if_t<std::is_same_v<T, std::string>, T> GetValueFromPython(PyObject* value) {
    if (!value) return T{};
    if (std::is_same_v<T, std::string>) {
        return T(PyUnicode_AsUTF8(value));
    }
}

class PythonModule {
public:
    explicit PythonModule(const std::string& modulePath);
    ~PythonModule();

    template <typename T>
    std::enable_if_t<!std::is_same_v<T, void>, T> CallFunc(const std::string &functionName, const std::vector<Parameter>& params) const {
        auto result = callFunc(functionName, params);
        return GetValueFromPython<T>(result);
    }

    template <typename T>
    std::enable_if_t<std::is_same_v<T, void>, void> CallFunc(const std::string &functionName, const std::vector<Parameter>& params) const {
        callFunc(functionName, params);
    }

    [[nodiscard]] bool IsValid() const { return m_isValid; }

private:
    PyObject* callFunc(const std::string &functionName, const std::vector<Parameter>& params) const;
    [[nodiscard]] bool hasFunction(const std::string& functionName) const;

private:
    bool m_isValid { false };
    PyObject* m_pyModule { nullptr };
    PyObject* m_pyDict { nullptr };

    // These are borrowed references, so dont need to be decref'd
    std::unordered_map<std::string, PyObject*> m_moduleFunctions {};
};

#endif //INC_7_1_PYTHON_MODULE_H
