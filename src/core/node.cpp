#include <core/prefix.h>

using namespace NodeCode;

CNode::CNode(std::vector<NodeInOut> in, std::vector<NodeInOut> out, std::vector<std::string> cParts, std::vector<std::string> filler){
  fInputs = in;
  fOutputs = out;
  fCParts = cParts;
  fFiller = filler;
}

int getIndex(std::vector<NodeInOut> v, std::string nIO){
  int res = -1;
  for (size_t i = 0; i < v.size(); i++)
  {
    if(v[i].fName == nIO){
      res = i;
      break;
    }
  }
  return res;
}

void log(std::string msg) {
  std::cout << msg << std::endl;
}

std::string CNode::getCCode(std::vector<Connection*> inputs, std::vector<Connection> outputs){
  std::string res = "";
  for (size_t i = 0; i < fCParts.size(); i++)
  {
    res = res + fCParts[i];
    if(fFiller.size() > i){
      std::string io = fFiller[i];
      int inIndex = getIndex(fInputs, io);
      if(inIndex != -1){
        res = res + inputs[inIndex]->getVarName();
      }
      int outIndex = getIndex(fOutputs, io);
      if(outIndex != -1){
        res = res + outputs[outIndex].getVarName();
      }
    }
  }
  return res;
}

ConstNode::ConstNode(Type* type, std::string cVal){
  fType = type;
  fCVal = cVal;
  struct NodeInOut io;
  io.fName = "out";
  io.type = type;
  fOutputs.push_back(io);
}

std::string ConstNode::getCCode(std::vector<Connection*> inputs, std::vector<Connection> outputs){
  return outputs[0].getVarName() + "=" + fCVal + ";\n";
}

FunctionNode::FunctionNode(std::vector<NodeInOut> in, std::vector<NodeInstance*> innerNodes, std::vector<NodeInOut> out){
  for (size_t i = 0; i < in.size(); i++) {
    fInputs.push_back(in[i]);
    fInConnections.push_back(Connection());
  }
  for (size_t i = 0; i < out.size(); i++) {
    fOutputs.push_back(out[i]);
    fOutConnections.push_back(nullptr);
  }
  fName = "";
  fInnerNodes = innerNodes;
}

size_t FunctionNode::fIndex = 0;

std::string FunctionNode::getName() {
  if(fName == "") {
    fName = "function_" + std::to_string(fIndex++);
  }
  return fName;
}

std::string FunctionNode::getFunctionCode() {
  std::string res = "void";
  res += " "+ getName() + "(";

  bool hasInputs = false;
  for (size_t i = 0; i < fInputs.size(); i++)
  {
    if(i != 0) res += ", ";
    res += fInputs[i].type->getCType() + " " + fInConnections[i].getVarName();
    fInConnections[i].fHasVal = true;
    hasInputs = true;
  }
  for (size_t i = 0; i < fOutputs.size(); i++)
  {
    if(i != 0 || hasInputs) res += ", ";
    res += fOutputs[i].type->getCType() + "* " + fOutConnections[i]->getVarName()+"_out";
  }
  res += ") {\n";

  res += NC_getCCodeFromNodes(fInnerNodes);

  for (size_t i = 0; i < fOutConnections.size(); i++) {
    res += "*" + fOutConnections[i]->getVarName() + "_out=" + fOutConnections[i]->getVarName() + ";\n";
  }

  res += "}\n";
  return res;
}

std::string FunctionNode::getCCode(std::vector<Connection*> inputs, std::vector<Connection> outputs) {
  std::string res = "";
  res += getName() + "(";

  bool hasInputs = false;
  for (size_t i = 0; i < inputs.size(); i++)
  {
    if(i != 0) res += ", ";
    res += inputs[i]->getVarName();
    hasInputs = true;
  }
  for (size_t i = 0; i < outputs.size(); i++)
  {
    if(i != 0 || hasInputs) res += ", ";
    res += "&" + outputs[i].getVarName();
  }
  res += ");";
  return res;
}

bool FunctionNode::connectWith(std::string funcOut, NodeInstance* node, std::string nodeOut) {
  int fOutIndex = getIndex(fOutputs, funcOut);
  if(fOutIndex == -1) return false;
  int outIndex = getIndex(node->fNode->fOutputs, nodeOut);
  if(outIndex == -1) return false;
  fOutConnections[fOutIndex] = &node->fOuts[outIndex];
  return true;
}

NodeInstance::NodeInstance(Node* node){
  fNode = node;
  fIns = std::vector<Connection*>();
  fOuts = std::vector<Connection>();
  for(size_t i = 0; i < node->fInputs.size(); i++){
    fIns.push_back(nullptr);
  }
  for(size_t i = 0; i < node->fOutputs.size(); i++){
    fOuts.push_back(Connection(this));
  }
}

bool NodeInstance::connectWith(std::string inName, FunctionNode* funcNode, std::string funcIn){
  int inIndex = getIndex(fNode->fInputs, inName);
  if(inIndex == -1) return false;
  int fInIndex = getIndex(funcNode->fInputs,funcIn);
  if(fInIndex == -1) return false;
  fIns[inIndex] = &funcNode->fInConnections[fInIndex];
  funcNode->fInConnections[fInIndex].addEndpoint(this);
  return true;
}

bool NodeInstance::connectWith(std::string inName, NodeInstance* prevNode, std::string outName){
  int outIndex = getIndex(prevNode->fNode->fOutputs, outName);
  if(outIndex == -1) return false;
  int inIndex = getIndex(fNode->fInputs, inName);
  if(inIndex == -1) return false;
  fIns[inIndex] = &prevNode->fOuts[outIndex];
  prevNode->fOuts[outIndex].addEndpoint(this);
  return true;
}

bool NodeInstance::canBeEvaluated() {
  //log("eval?");
  for(size_t i = 0; i < fIns.size(); i++){
    if(fIns[i] == nullptr) {
      continue;
    }
    if(!fIns[i]->fHasVal) {
      //log("no val");
      return false;
    }
  }
  //log("eval!");
  return true;
}

std::string NodeInstance::getCode() {
  std::string res = "";
  for(size_t i = 0; i < fOuts.size(); i++){
    res += fNode->fOutputs[i].type->getCType() + " " + fOuts[i].getVarName() + ";\n";
  }
  res += fNode->getCCode(fIns, fOuts);
  return res;
}

void NodeInstance::setEvaluated() {
  for (size_t i = 0; i < fOuts.size(); i++)
  {
    fOuts[i].fHasVal = true;
  }
}

Connection* NodeInstance::getOut(std::string outName) {
  int outIndex = getIndex(fNode->fOutputs, outName);
  if(outIndex == -1) return nullptr;
  return &fOuts[outIndex];
}

std::string NodeCode::NC_getCCodeFromNodes(std::vector<NodeInstance*> nodes) {
  std::string res = "";
  size_t i = 0;
  while (i < nodes.size()) {
    if(nodes[i] != nullptr && nodes[i]->canBeEvaluated()){
      res += nodes[i]->getCode();
      nodes[i]->setEvaluated();
      nodes.erase(nodes.begin()+i);
      i = 0;
      continue;
    }
    i++;
  }
  return res;
}