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
  class Type
  {
  public:
    virtual std::string getCType()=0;
    //virtual std::string getTypeString() const;
  private:
    std::string fName;
  };

  class PrimitiveType : public Type {
  private:
    EType fPrimitive;
  public:
    PrimitiveType(EType type);
    std::string getCType();
  };
} 