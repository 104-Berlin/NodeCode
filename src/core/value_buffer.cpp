#include <core/prefix.h>

using namespace NodeCode;

ValueBuffer::ValueBuffer(size_t size)
    : fBuffer(nullptr), fSize(size)
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
    return *this;
}

void ValueBuffer::SetValue(void* value) 
{
    memcpy(fBuffer, value, fSize);
}

void* ValueBuffer::GetValue() const
{
    return fBuffer;
}