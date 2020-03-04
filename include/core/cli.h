#pragma once

using namespace std;
namespace NodeCode {
class CLI {
 private:
  map<string, NodeInstance*> fMainNodes;
  map<string, CNode*> fCNodes;
  map<string, ConstNode*> fConst;
  map<string, Type*> fTypes;
  map<string, FunctionNode*> fFunctions;

 public:
  void add();
  void addType();
  void addConst();
  void get();
  void getTypes();
  void getConst();
  void run();
  string getLine();
  string getName();
  void putLine(string line);
};
}  // namespace NodeCode