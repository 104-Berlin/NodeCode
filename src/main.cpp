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

    ConstNode int3 = ConstNode(tInt, "3");

    NodeInstance cNode = NodeInstance(&int3);
    NodeInstance addNode = NodeInstance(&additionNode);
    addNode.connectWith("in 1", &cNode, "out");
    addNode.connectWith("in 2", &cNode, "out");

    std::vector<NodeInstance*> nodes;
    nodes.push_back(&cNode);
    nodes.push_back(&addNode);

    std::cout << NCgetCCodeFromNodes(nodes) << std::endl;
    return 0;
}