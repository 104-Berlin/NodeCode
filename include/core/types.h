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
      Bool,

      Struct,
      Array
    };

  class Value
  {
  public:

  private:
    EType fType;
    Value* fValue;
    std::vector<Value*> fArray;


    //Value maybe ect..
    std::string fName;
  };



  struct Struct : public Value
  {
    private:
    std::vector<Value> fValues;
    std::string fObjectName;
  };

}