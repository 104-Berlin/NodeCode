#include <core/prefix.h>

using namespace NodeCode;

PrimitiveType::PrimitiveType(EType type){
  fPrimitive = type;
}

std::string PrimitiveType::getCType(){
  switch (fPrimitive)
  {
  case Int:
    return "int";
  case Float:
    return "float";
  case Double:
    return "double";
  case Long:
    return "long";
  case Char:
    return "char";
  case Bool:
    return "bool";
  default:
    return "void*";
  }
}