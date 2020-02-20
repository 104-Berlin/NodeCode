#pragma once

namespace NodeCode 
{
    enum EType
    {
        Unknown,

        Int,
        Float,
        Double,
        Long,
        Char,
        Bool
    };

    EType GetTypeFromTypeId(const std::type_info type);
    size_t GetSizeFromType(EType type);

    class ValueBuffer
    {
    public:
        ValueBuffer();
        ValueBuffer(const ValueBuffer& copy);
        virtual ~ValueBuffer();

        template <typename T>
        void SetValue(const T& value);

        ValueBuffer& operator=(const ValueBuffer& other);
    private:
        void* fBuffer;
        size_t* fRefCount;
    }
}