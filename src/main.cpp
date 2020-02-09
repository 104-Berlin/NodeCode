#include "core/prefix.h"
#include <iostream>

using namespace NodeCode;

int main()
{
    Node n;
    n.inValues.push_back(new Type(Int));

    n.inValues[0]->getTypeString();
    
    return 0;
}