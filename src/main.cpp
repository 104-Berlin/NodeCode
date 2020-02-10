#include "core/prefix.h"
#include <iostream>

using namespace NodeCode;


int main()
{
    Type* tInt = new PrimitiveType(Int);
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

    std::vector<std::string> cParts;
    cParts.push_back("");
    cParts.push_back("=");
    cParts.push_back("+");
    cParts.push_back(";\n");

    std::vector<std::string> fill;
    fill.push_back("out");
    fill.push_back("in 1");
    fill.push_back("in 2");

    CNode additionNode = CNode(in,out,cParts,fill);

    std::vector<std::string> mParts;
    mParts.push_back("");
    mParts.push_back("=");
    mParts.push_back("*");
    mParts.push_back(";\n");

    CNode multiplicationNode = CNode(in,out,mParts,fill);

    ConstNode int3 = ConstNode(tInt, "3");
    ConstNode int5 = ConstNode(tInt, "5");

    NodeInstance c3Node = NodeInstance(&int3);
    NodeInstance c5Node = NodeInstance(&int5);
    NodeInstance addNode = NodeInstance(&additionNode);
    NodeInstance mulNode = NodeInstance(&multiplicationNode);

    addNode.connectWith("in 1", &c3Node, "out");
    addNode.connectWith("in 2", &c5Node, "out");
    mulNode.connectWith("in 1", &addNode, "out");
    mulNode.connectWith("in 2", &c3Node, "out");

    std::vector<NodeInstance*> nodes;
    nodes.push_back(&mulNode);
    nodes.push_back(&addNode);
    nodes.push_back(&c3Node);
    nodes.push_back(&c5Node);

    std::cout << NC_getCCodeFromNodes(nodes) << std::endl;
    return 0;
}