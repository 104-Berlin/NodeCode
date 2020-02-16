#include <core/prefix.h>

using namespace NodeCode;


Value::Value(const std::string& name)
    : fName(name), fType(EType::Unknown), fValuePtr(nullptr)
{

}

Value::~Value()
{
    if (fValuePtr)
    {
        free(fValuePtr);
        fValuePtr = nullptr;
    }
}

template <>
Value* Value::SetValue<int>(const int& value) 
{
    if (fType != EType::Int)
    {
        fType = EType::Int;
        if (fValuePtr) {
            free(fValuePtr);
            fValuePtr = nullptr;
        }
        fValuePtr = malloc(sizeof(int));
    }
    *((int*) fValuePtr) = value;
    return this;
}

template <>
Value* Value::SetValue<float>(const float& value)
{
    if (fType != EType::Float)
    {
        fType = EType::Float;
        if (fValuePtr) {
            free(fValuePtr);
            fValuePtr = nullptr;
        }
        fValuePtr = malloc(sizeof(float));
    }
    *((float*)fValuePtr) = value;
    return this;
}

template <>
Value* Value::SetValue<char>(const char& value)
{
    if (fType != EType::Char)
    {
        fType = EType::Char;
        if (fValuePtr) {
            free(fValuePtr);
            fValuePtr = nullptr;
        }
        fValuePtr = malloc(sizeof(char));
    }
    *((char*)fValuePtr) = value;
    return this;
}

template <>
Value* Value::SetValue<double>(const double& value)
{
    if (fType != EType::Double)
    {
        fType = EType::Double;
        if (fValuePtr) {
            free(fValuePtr);
            fValuePtr = nullptr;
        }
        fValuePtr = malloc(sizeof(double));
    }
    *((double*)fValuePtr) = value;    
    return this;
}

template <>
Value* Value::SetValue<long>(const long& value)
{
    if (fType != EType::Long)
    {
        fType = EType::Long;
        if (fValuePtr) {
            free(fValuePtr);
            fValuePtr = nullptr;
        }
        fValuePtr = malloc(sizeof(long));
    }
    *((long*)fValuePtr) = value;    
    return this;
}

template <>
Value* Value::SetValue<bool>(const bool& value)
{
    if (fType != EType::Bool)
    {
        fType = EType::Bool;
        if (fValuePtr) {
            free(fValuePtr);
            fValuePtr = nullptr;
        }
        fValuePtr = malloc(sizeof(bool));
    }
    *((bool*)fValuePtr) = value;    
    return this;
}   
