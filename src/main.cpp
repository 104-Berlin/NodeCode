#include "core/prefix.h"
#include <iostream>

using namespace NodeCode;

int main()
{
    Node n;
    n.inValues.push_back(new PrimitiveValue());

    n.inValues[0]->Print();
    
    return 0;
}