#include <core/prefix.h>

using namespace NodeCode;

EType NC_GetTypeFromTypeId(const type_info& t)
{
    if (t == typeid(int))           return EType::Int;
    else if (t == typeid(float))    return EType::Float;
    else if (t == typeid(double))   return EType::Double;
    else if (t == typeid(long))     return EType::Long;
    else if (t == typeid(char))     return EType::Char;
    else if (t == typeid(bool))     return EType::Bool;

    return EType::Unknown;
}


Value::Value(const std::string& name)
    : fName(name), fType(EType::Unknown), fValuePtr(nullptr)
{

}

Value::~Value()
{
    if (fValuePtr)
    {
        delete fValuePtr;
        fValuePtr = nullptr;
    }
}

template <>
void Value::SetValue<int>(const int& value) 
{
    if (fType != EType::Int)
    {
        fType = EType::Int;
        if (fValuePtr) {
            delete fValuePtr;
            fValuePtr = nullptr;
        }
        fValuePtr = new int;
    }
    *((int*) fValuePtr) = value;
}

template <>
void Value::SetValue<float>(const float& value)
{
    if (fType != EType::Float)
    {
        fType = EType::Float;
        if (fValuePtr) {
            delete fValuePtr;
            fValuePtr = nullptr;
        }
        fValuePtr = new float;
    }
    *((float*)fValuePtr) = value;
}

template <>
void Value::SetValue<char>(const char& value)
{

}

template <>
void Value::SetValue<double>(const double& value)
{

}

template <>
void Value::SetValue<long>(const long& value)
{

}

template <>
void Value::SetValue<bool>(const bool& value)
{
    
}   
