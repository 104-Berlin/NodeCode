#include "core/prefix.h"
#include <iostream>

using namespace NodeCode;


int main()
{
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
    CNode additionNode = CNode(in,out,cParts,fill);
    
    // same for mult
    std::vector<std::string> mParts;
    mParts.push_back("");
    mParts.push_back("=");
    mParts.push_back("*");
    mParts.push_back(";\n");

    CNode multiplicationNode = CNode(in,out,mParts,fill);

    // create const nodes
    ConstNode int3 = ConstNode(tInt, "3");
    ConstNode int5 = ConstNode(tInt, "5");

    // instantiate nodes for use in function
    NodeInstance* c3Node = new NodeInstance(&int3);
    NodeInstance* c5Node = new NodeInstance(&int5);
    NodeInstance* addNode = new NodeInstance(&additionNode);
    NodeInstance* mulNode = new NodeInstance(&multiplicationNode);

    std::vector<NodeInOut> fIn;
    fIn.push_back(i1);

    addNode->connectWith("in 2", c5Node, "out");
    mulNode->connectWith("in 1", addNode, "out");
    mulNode->connectWith("in 2", c3Node, "out");

    std::vector<NodeInstance*> nodes;
    nodes.push_back(c3Node);
    nodes.push_back(c5Node);
    nodes.push_back(mulNode);
    nodes.push_back(addNode);
    
    std::vector<NodeInOut> fOut;
    fOut.push_back(o);

    FunctionNode fNode = FunctionNode(fIn, nodes, fOut);
    addNode->connectWith("in 1", &fNode, "in 1");
    fNode.connectWith("out", mulNode, "out");


    NodeInstance main5 = NodeInstance(&int5);
    NodeInstance fInst = NodeInstance(&fNode); 
    fInst.connectWith("in 1", &main5, "out");

    std::vector<NodeInstance*> mainProg;
    mainProg.push_back(&fInst);
    mainProg.push_back(&main5);


    std::cout << fNode.getFunctionCode() << std::endl;
    std::cout << NC_getCCodeFromNodes(mainProg) << std::endl;
    return 0;
}