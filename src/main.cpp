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

template <typename T>
void Multiply(Node* n)
{
    T result;
    result = 1;
    const std::vector<const Value const*>& inputs = n->inValues;
    for (auto& value : inputs)
    {
        result *= value->GetValue<T>();
    }
    Value* r = new Value("result");
    r->SetValue<T>(result);
    n->outValues.push_back(r);
}

int main()
{
    Node additionNode;
    additionNode.callback = Multiply<int>;

    additionNode.inValues.push_back(new Value("Value 1")->SetValue<int>(6));
    additionNode.inValues.push_back(new Value("Value 2")->SetValue<int>(2));

    additionNode.Run();

    int result = additionNode.outValues[0]->GetValue<int>();
    std::cout << "Result: " << result << std::endl;

    return 0;
}