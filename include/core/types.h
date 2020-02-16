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

  class Value
  {
  public:
    Value(const std::string& name);
    virtual ~Value();

    template<typename T>
    Value* SetValue(const T& value);

    template <typename T>
    const T& GetValue() const 
    {
      if (!fValuePtr) {
        printf("Could not get the value \"%s\". It is not set yet!\n", fName.c_str());
        return T();
      }
      return *((T*)fValuePtr);
    }

  private:
    EType fType;
    std::string fName;
    void* fValuePtr;
  };

} 