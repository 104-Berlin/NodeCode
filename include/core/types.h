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

  struct ValueDescription
  { 
    std::string Name;
    EType Type;
  };

  class Connection
  {
  public:
    Connection(EType type);
    virtual ~Connection();

    template<typename T>
    Connection* SetValue(const T& value)
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
        if (type != fType) { printf("Wrong type to get the value!\n"); }
        if (!fBuffer) { printf("The value was never set. This is going to crash the programm!\n"); }
        return *((T*)fBuffer);
    }

  private:
    void* fBuffer;
    EType fType;
  };

} 
