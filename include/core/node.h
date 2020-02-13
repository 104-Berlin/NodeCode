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
      std::vector<std::string> fIncludes;
    public:
      CNode(std::vector<NodeInOut> in, std::vector<NodeInOut> out, std::vector<std::string> cParts, std::vector<std::string> filler);
      std::string getCCode(std::vector<Connection*> inputs, std::vector<Connection> outputs);
      void addInclude(std::string include);
      std::vector<std::string> getIncludes();
  };

  class ConstNode : public Node {
    private:
      Type* fType;
      std::string fCVal;
    public:
      ConstNode(Type* type, std::string cVal);
      std::string getCCode(std::vector<Connection*> inputs, std::vector<Connection> outputs);
  };

  class FunctionNode : public Node {
    private:
      std::vector<NodeInstance*> fInnerNodes;
      std::vector<Connection*> fOutConnections;
      std::string fName;

      static size_t fIndex;
    public:
      std::vector<Connection> fInConnections;
      FunctionNode(std::vector<NodeInOut> in, std::vector<NodeInstance*> innerNodes, std::vector<NodeInOut> out);
      std::string getCCode(std::vector<Connection*> inputs, std::vector<Connection> outputs);
      std::string getFunctionCode();
      std::string getName();
      bool connectWith(std::string funcOut, NodeInstance* node, std::string nodeOut);
  };

  class NodeInstance {
    private:
      std::vector<Connection*> fIns;
    public:
      std::vector<Connection> fOuts;
      Node* fNode;
      NodeInstance(Node* node);
      bool connectWith(std::string inName, FunctionNode* funcNode, std::string funcIn);
      bool connectWith(std::string inName, NodeInstance* prevNode, std::string outName);
      Connection* getOut(std::string outName);
      bool canBeEvaluated();
      std::string getCode();
      void setEvaluated();
  };

  std::string NC_getCCodeFromNodes(std::vector<NodeInstance*> nodes);
  std::string NC_getCProg(std::vector<NodeInstance*> main, std::vector<FunctionNode*> funcs, std::vector<CNode*> cNodes);
  void NC_compileAndRun(std::vector<NodeInstance*> main, std::vector<FunctionNode*> funcs, std::vector<CNode*> cNodes);
}
