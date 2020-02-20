#pragma once

namespace NodeCode 
{
    class ValueBuffer
    {
    public:
        ValueBuffer(size_t size);
        ValueBuffer(const ValueBuffer& copy);
        virtual ~ValueBuffer();

        void SetValue(void* data);
        void* GetValue() const;

        ValueBuffer& operator=(const ValueBuffer& other);
    private:
        void* fBuffer;
        size_t* fRefCount;
        size_t fSize;
    };
}