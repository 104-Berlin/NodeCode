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
        return *((T*)fValuePtr);
    }

  private:
    EType fType;
    std::string fName;
    void* fValuePtr;
  };

} 