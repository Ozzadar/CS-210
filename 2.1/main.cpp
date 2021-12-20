#include <iostream>
#include <string>
#include <Python.h>

int main() {
    std::cout << "Start 1 \n";
    Py_Initialize();

    std::cout << "2\n";

    PyObject* my_module = PyImport_ImportModule("python.myfirstprogram");
    std::cerr << my_module << std::endl;
    PyErr_Print();

    std::cout << "3\n";
    PyObject* my_function = PyObject_GetAttrString(my_module, "printsomething");


    std::cout << "4\n";

    PyObject* my_result = PyObject_CallObject(my_function, NULL);
    Py_Finalize();
    return 0;
}
