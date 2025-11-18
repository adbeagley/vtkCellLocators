#pragma once
#include <vtkPythonUtil.h>
#include <vtkIdList.h>
// #include <PyVTKObject.h>

void print(std::string msg, bool new_line = true)
{
    std::cout << msg;
    if (new_line)
    {
        std::cout << std::endl;
    }
}

const char *PyRepr(PyObject *obj)
{
    PyObject *srcRepr = PyObject_Repr(obj);
    PyObject *str = PyUnicode_AsEncodedString(srcRepr, "utf-8", "~E~");
    const char *bytes = PyBytes_AS_STRING(str);
    return bytes;
}

const char *PyTypeName(PyTypeObject *obj)
{
    auto pyName = PyType_GetName(obj);
    const char *original = PyRepr(pyName);
    std::string copy = strdup(original);
    if (copy.size() < 3)
    {
        const char *result = {'\0'};
        return result;
    }
    // return substring as const char*
    return copy.substr(1, copy.size() - 2).c_str();
}

const char *PyTypeName(PyObject *obj)
{
    PyTypeObject *pyType = Py_TYPE(obj);
    ;
    return PyTypeName(pyType);
}

template <typename T>
std::string stringVector(std::vector<T> vec)
{
    std::string result = "[";
    for (T val : vec)
    {
        result = result + std::to_string(val) + ", ";
    }
    result = result.append("]");
    return result;
}

template <typename T, size_t N>
std::string stringArray(const T (&arr)[N])
{
    std::string result = "[";
    for (int i = 0; i < N; i++)
    {
        result = result + std::to_string(arr[i]) + ", ";
    }
    result = result.append("]");
    return result;
}

// template <typename T>
// std::string stringArray(const T* arr){
//     if (arr == nullptr){
//         return std::string("Array is null.");
//     }
//     std::string result = "[";
//     for(T v : &arr){
//         result = result + std::to_string(v) + ", ";
//     }
//     result = result.append("]");
//     return result;

//     // int N = sizeof(*arr) / sizeof(arr[0]);
//     // std::string result = "[";
//     // for (int i = 0; i < N; i++){
//     //     result = result + std::to_string(arr[i]) + ", ";
//     // }
//     // result = result.append("]");
//     // return result;
// }

// template <typename T, size_t N>
// std::string stringArray(const (T&)(arr)[N]){
//     std::string result = "[";
//     for (int i = 0; i < N ; i++){
//         result = result + std::to_string(arr[i]) + ", ";
//     }
//     result = result.append("]");
//     return result;
// }

// template <typename T, size_t N>
// std::string stringArray(const std::array<T*, N>& arr){
//     if (arr == nullptr) {
//         std::string result = "Array is null.";
//         return result;
//     }
//     std::string result = "[";
//     for (int i = 0; i < N ; i++){
//         result = result + std::to_string((*arr)[i]) + ", ";
//     }
//     result = result.append("]");
//     return result;
// }

std::string stringvtkIdList(vtkIdList *id_list)
{
    std::string result = "[";
    for (int i = 0; i < id_list->GetNumberOfIds(); i++)
    {
        result = result + std::to_string(id_list->GetId(i)) + ", ";
    }
    result = result.append("]");
    return result;
}
