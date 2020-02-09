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

  extern EType NC_GetTypeFromTypeId(const type_info& t);

  class Value
  {
  public:
    Value(const std::string& name);
    virtual ~Value();

    template<typename T>
    void SetValue(const T& value);

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