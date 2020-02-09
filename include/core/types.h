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
    virtual std::string getTypeString() const;
  private:
    std::string fName;
  };

} 