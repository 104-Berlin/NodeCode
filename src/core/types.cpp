#include <core/prefix.h>

using namespace NodeCode;

EType NodeCode::GetTypeFromTypeId(const std::type_info& type) 
{
    if (type == typeid(int)) { return EType::Int; }
    else if (type == typeid(float)) { return EType::Float; }
    else if (type == typeid(long)) { return EType::Long; }
    else if (type == typeid(double)) { return EType::Double; }
    else if (type == typeid(char)) { return EType::Char; }
    else if (type == typeid(bool)) { return EType::Bool; } 

    return EType::Unknown;
}

size_t NodeCode::GetSizeFromType(EType type) 
{
    switch (type)
    {
    case EType::Bool:
        return sizeof(bool);
    case EType::Int:
        return sizeof(int); 
    case EType::Long:
        return sizeof(long);
    case EType::Float:
        return sizeof(float);
    case EType::Double:
        return sizeof(double);
    case EType::Char:
        return sizeof(char);
    default:
        return 0;
    }
    return 0;
}

Value:: Value(const std::string& name)
    : fName(name), fType(EType::Unknown), fBuffer(nullptr)
{

}

Value::~Value()
{
    free(fBuffer);
}