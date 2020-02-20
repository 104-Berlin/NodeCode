#include <core/prefix.h>

using namespace NodeCode;

EType GetTypeFromTypeId(const std::type_info type) 
{
    if (type == typeid(int)) { return EType::Int; }
    else if (type == typeid(float)) { return EType::Float; }
    else if (type == typeid(long)) { return EType::Long; }
    else if (type == typeid(double)) { return EType::Double; }
    else if (type == typeid(char)) { return EType::Char; }
    else if (type == typeid(bool)) { return EType::Bool; } 

    return EType::Unknown;
}

size_t GetSizeFromType(EType type) 
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

ValueBuffer::ValueBuffer()
    : fBuffer(nullptr)
{
    fRefCount = new size_t(1); //Set the ref count to one at the first 
}

ValueBuffer::ValueBuffer(const ValueBuffer& copy)
{
    fBuffer = copy.fBuffer;
    fRefCount = copy.fRefCount;
    (*fRefCount)++;
}

ValueBuffer::~ValueBuffer()
{
    (*fRefCount)--;

    if ((*fRefCount) <= 0) {
        if (fBuffer) {
            free(fBuffer);
        }
        delete fRefCount;
    }
}

ValueBuffer& ValueBuffer::operator=(const ValueBuffer& other)
{
    if (fBuffer) {
        (*fRefCount)--;
        if ((*fRefCount) <= 0) {
            free(fBuffer);
            delete fRefCount;
        }
    }

    fBuffer = other.fBuffer;
    fRefCount = other.fRefCount;
    (*fRefCount)++;
}

template <typename T>
void ValueBuffer::SetValue<T>(const T& value) 
{
    
}