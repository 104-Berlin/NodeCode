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
  class Type
  {
  public:

  private:
    EType fType;
    Type* fArrayType;
    struct Struct* fStruct;
    //Value maybe ect..
    std::string fName;
  };



  struct Struct
  {
    std::vector<StructElement> fElements;
  };

  struct StructElement
  {
    std::string fName;
    Type* fType;
  };
} 