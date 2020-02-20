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
    Value(const std::string& name, EType type);
    virtual ~Value();

    template<typename T>
    Value* SetValue(const T& value)
    {
        EType type = GetTypeFromTypeId(typeid(T));
        if (type != fType) { printf("Wrong type to set the value!"); return nullptr; }
        fValueBuffer.SetValue((void*) &value);
        return this;
    }

    template <typename T>
    const T& GetValue() const 
    {
        EType type = GetTypeFromTypeId(typeid(T));
        if (type != fType) { printf("Wrong type to get the value!"); }
        return *((T*)fValueBuffer.GetValue());
    }

  private:
    std::string fName;
    ValueBuffer fValueBuffer;
    EType fType;
  };

} 