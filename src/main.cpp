#include <iostream>
#include "core/prefix.h"

using namespace NodeCode;

int main() {
  // create used types
  Type* tInt = new PrimitiveType(Int);

  // create used io configs
  struct NodeInOut i1;
  i1.type = tInt;
  i1.fName = "in 1";
  struct NodeInOut i2;
  i2.type = tInt;
  i2.fName = "in 2";
  struct NodeInOut o;
  o.type = tInt;
  o.fName = "out";

  std::vector<NodeInOut> in;
  in.push_back(i1);
  in.push_back(i2);

  std::vector<NodeInOut> out;
  out.push_back(o);

  // create node data
  std::vector<std::string> cParts;
  cParts.push_back("");
  cParts.push_back("=");
  cParts.push_back("+");
  cParts.push_back(";\n");

  std::vector<std::string> fill;
  fill.push_back("out");
  fill.push_back("in 1");
  fill.push_back("in 2");

  // build node
  CNode additionNode = CNode(in, out, cParts, fill);

  // same for mult
  std::vector<std::string> mParts;
  mParts.push_back("");
  mParts.push_back("=");
  mParts.push_back("*");
  mParts.push_back(";\n");

  CNode multiplicationNode = CNode(in, out, mParts, fill);

  std::vector<std::string> pParts;
  pParts.push_back("printf(\"%d\\n\", ");
  pParts.push_back(");\n");

  std::vector<std::string> pFill;
  pFill.push_back("in 1");

  std::vector<NodeInOut> pIn;
  pIn.push_back(i1);

  CNode printNode = CNode(in, std::vector<NodeInOut>(), pParts, pFill);
  printNode.addInclude("stdio.h");

  // create const nodes
  ConstNode int3 = ConstNode(tInt, "3");
  ConstNode int5 = ConstNode(tInt, "5");

  // instantiate nodes for use in function
  NodeInstance* c3Node = new NodeInstance(&int3);
  NodeInstance* c5Node = new NodeInstance(&int5);
  NodeInstance* addNode = new NodeInstance(&additionNode);
  NodeInstance* mulNode = new NodeInstance(&multiplicationNode);

  addNode->connectWith("in 2", c5Node, "out");
  mulNode->connectWith("in 1", addNode, "out");
  mulNode->connectWith("in 2", c3Node, "out");

  std::vector<NodeInstance*> nodes;
  nodes.push_back(c3Node);
  nodes.push_back(c5Node);
  nodes.push_back(mulNode);
  nodes.push_back(addNode);

  // prepare function node
  std::vector<NodeInOut> fIn;
  fIn.push_back(i1);

  std::vector<NodeInOut> fOut;
  fOut.push_back(o);

  FunctionNode fNode = FunctionNode(fIn, nodes, fOut);

  // connect function body with function node
  addNode->connectWith("in 1", &fNode, "in 1");
  fNode.connectWith("out", mulNode, "out");

  // create main nodes
  NodeInstance main5 = NodeInstance(&int5);
  NodeInstance fInst = NodeInstance(&fNode);
  NodeInstance fIns2 = NodeInstance(&fNode);
  NodeInstance pInst = NodeInstance(&printNode);
  fInst.connectWith("in 1", &main5, "out");
  fIns2.connectWith("in 1", &fInst, "out");
  pInst.connectWith("in 1", &fIns2, "out");

  std::vector<NodeInstance*> mainProg;
  mainProg.push_back(&main5);
  mainProg.push_back(&fInst);
  mainProg.push_back(&fIns2);
  mainProg.push_back(&pInst);

  std::vector<FunctionNode*> funcs;
  funcs.push_back(&fNode);

  std::vector<CNode*> cnodes;
  cnodes.push_back(&printNode);
  cnodes.push_back(&additionNode);
  cnodes.push_back(&multiplicationNode);

  CLI cli = CLI();
  cli.run();

  NC_compileAndRun(mainProg, funcs, cnodes);
  return 0;
}