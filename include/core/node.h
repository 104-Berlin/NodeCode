#pragma once

namespace NodeCode 
{
  struct NodeInOut {
    std::string fName;
    Type* type;
  };
  
  class Node {
    public:
      std::vector<NodeInOut> fInputs;
      std::vector<NodeInOut> fOutputs;
      virtual std::string getCCode(std::vector<Connection*> inputs, std::vector<Connection> outputs) = 0;
  };

  class CNode : public Node {
    private:
      std::vector<std::string> fCParts;
      std::vector<std::string> fFiller;
    public:
      CNode(std::vector<NodeInOut> in, std::vector<NodeInOut> out, std::vector<std::string> cParts, std::vector<std::string> filler);
      std::string getCCode(std::vector<Connection*> inputs, std::vector<Connection> outputs);
  };

  class ConstNode : public Node {
    private:
      Type* fType;
      std::string fCVal;
    public:
      ConstNode(Type* type, std::string cVal);
      std::string getCCode(std::vector<Connection*> inputs, std::vector<Connection> outputs);
  };

  class NodeInstance {
    private:
      Node* fNode;
      std::vector<Connection*> fIns;
      std::vector<Connection> fOuts;
    public:
      NodeInstance(Node* node);
      bool connectWith(std::string inName, NodeInstance* prevNode, std::string outName);
      bool canBeEvaluated();
      std::string getCode();
      void setEvaluated();
  };

  std::string NC_getCCodeFromNodes(std::vector<NodeInstance*> nodes);
}
