#include <core/prefix.h>

void NodeCode::GarbageCollector::CleanUp()
{
    for (Value* v : storedValues) {
        delete v;
    }
    storedValues.clear();
}
