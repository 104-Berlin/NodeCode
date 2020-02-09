#include <core/prefix.h>

using namespace NodeCode;

Node::~Node()
{
    for (Value* v : inValues)
        delete v;
    inValues.clear();


    for (Value* v : outValues)
        delete v;
    outValues.clear();
}