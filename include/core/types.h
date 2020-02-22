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

  extern EType GetTypeFromTypeId(const std::type_info& type);
  extern size_t GetSizeFromType(EType type);

  class Value
  {
  public:
    Value(const std::string& name);
    virtual ~Value();

    template<typename T>
    Value* SetValue(const T& value)
    {
        EType type = GetTypeFromTypeId(typeid(T));
        fType = type;
        size_t bufferSize = GetSizeFromType(fType);
        if (type != fType && !fBuffer) 
        { 
          free(fBuffer);
        }
        if (!fBuffer)
        {
          fBuffer = malloc(bufferSize);
        }
        memcpy(fBuffer, &value, bufferSize);
        return this;
    }

    template <typename T>
    const T& GetValue() const 
    {
        EType type = GetTypeFromTypeId(typeid(T));
        if (type != fType) { printf("Wrong type to get the value!"); }
        return *((T*)fBuffer);
    }

  private:
    std::string fName;
    void* fBuffer;
    EType fType;
  };

} 
