#include <core/prefix.h>

using namespace NodeCode;

NodeInstance::NodeInstance(NodeDescription* nodeDsc)
    : fNodeDsc(nodeDsc)
{
    for (const ValueDescription& valueDsc : nodeDsc->Outputs)
    {
        outValues.push_back(Connection(valueDsc.Type));
    }
}

NodeInstance::~NodeInstance()
{
    inValues.clear();
    outValues.clear();
}