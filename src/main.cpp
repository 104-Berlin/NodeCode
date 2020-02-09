#include "core/prefix.h"
#include <iostream>

using namespace NodeCode;

template <typename T>
void Addition(Node* n) 
{
    T result;
    result = 0;
    const std::vector<const Value const*>& inputs = n->inValues;
    for (auto& value : inputs)
    {
        result += value->GetValue<T>();
    }
    Value* r = new Value("result");
    r->SetValue<T>(result);
    n->outValues.push_back(r);
}

int main()
{
    Node additionNode;
    additionNode.callback = Addition<int>;

    Value* v1 = new Value("Value 1");
    v1->SetValue<int>(5);
    Value* v2 = new Value("Value 2");
    v2->SetValue<int>(2);

    additionNode.inValues.push_back(v1);
    additionNode.inValues.push_back(v2);

    additionNode.Run();

    int result = additionNode.outValues[0]->GetValue<int>();
    std::cout << "Result: " << result << std::endl;

    return 0;
}