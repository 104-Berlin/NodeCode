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
    Type(EType primitive);
    Type(struct Struct* struc);
    Type(Type* arrayOf);

    std::string getTypeString() const;
    std::string getPrimitiveTypeString() const;

  private:
    EType fType;
    Type* fArrayType;
    struct Struct* fStruct;
    //Value maybe ect..
    std::string fName;
  };



  struct Struct
  {
    std::vector<struct StructElement> fElements;
  };

  struct StructElement
  {
    std::string fName;
    Type* fType;
  };
} 