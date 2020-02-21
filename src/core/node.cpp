#include <core/prefix.h>

using namespace NodeCode;

Node::~Node()
{
    inValues.clear();
    outValues.clear();
}