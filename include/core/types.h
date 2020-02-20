#pragma once

namespace NodeCode
{

  class Value
  {
  public:
    Value(const std::string& name);
    virtual ~Value();

    template<typename T>
    Value* SetValue(const T& value)
    {
      EType type = GetTypeFromTypeId(typeid(T));
    }

    template <typename T>
    const T& GetValue() const 
    {
      printf("Get value not implemented yet!");
    }

  private:
    std::string fName;
    ValueBuffer fValueBuffer;
  };

} 