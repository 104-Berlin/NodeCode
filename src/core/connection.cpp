#include <core/prefix.h>

using namespace NodeCode;

size_t Connection::cIndex = 0;

Connection::Connection(){
  *this = Connection(nullptr);
}

Connection::Connection(NodeInstance* origin){
  fHasVal = false;
  fVarName = "";
  fOrigin = origin;
}

bool Connection::addEndpoint(NodeInstance* endpoint){
  fEndpoints.push_back(endpoint);
  return true;
}

std::string Connection::getVarName(){
  if(fVarName != "") return fVarName;
  fVarName = "var_" + std::to_string(cIndex++);
  return fVarName;
}