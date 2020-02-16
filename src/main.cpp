#include "core/prefix.h"
#include <iostream>

using namespace NodeCode;

template <typename T>
void Addition(Node* n) 
{
    T result;
    result = 0;
    const std::vector<Value*>& inputs = n->inValues;
    for (auto& value : inputs)
    {
        result += value->GetValue<T>();
    }
    n->outValues[0]->SetValue<T>(result);
}

template <typename T>
void Multiply(Node* n)
{
    T result;
    result = 1;
    const std::vector<Value*>& inputs = n->inValues;
    for (auto& value : inputs)
    {
        result *= value->GetValue<T>();
    }
    n->outValues[0]->SetValue<T>(result);
}

void LogicAnd(Node* n)
{
    bool result;
    result = true;
    const std::vector<Value*>& inputs = n->inValues;
    for (auto& value : inputs)
    {
        result = result && value->GetValue<bool>();
    }
    n->outValues[0]->SetValue<bool>(result);
}

int main()
{
    Node additionNode;
    additionNode.callback = LogicAnd;

    additionNode.inValues.push_back((new Value("Value 1"))->SetValue<bool>(true));
    additionNode.inValues.push_back((new Value("Value 2"))->SetValue<bool>(true));
    additionNode.outValues.push_back((new Value("Result")));

    additionNode.Run();

    bool result = additionNode.outValues[0]->GetValue<bool>();
    std::cout << "Result: " << result << std::endl;

    return 0;
}