#pragma once

namespace NodeCode
{
    namespace GarbageCollector
    {
        static std::vector<Value*> storedValues;

        void CleanUp();
    }
}
