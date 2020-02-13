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
  void get();
  void getTypes();
  void run();
  string getLine();
  string getName();
  void putLine(string line);
};
}  // namespace NodeCode