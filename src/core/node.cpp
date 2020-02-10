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
  for(Connection* con : fIns){
    if(con == nullptr) continue;
    if(!con->fHasVal) return false;
  }
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
  for(Connection& out : fOuts) {
    out.fHasVal = true;
  }
}

std::string NodeCode::NCgetCCodeFromNodes(std::vector<NodeInstance*> nodes) {
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