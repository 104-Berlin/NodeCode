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
    Value* r = new Value("result");
    r->SetValue<T>(result);
    n->outValues.push_back(r);
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
    Value* r = new Value("result");
    r->SetValue<T>(result);
    n->outValues.push_back(r);
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
    Value* r = new Value("result");
    r->SetValue<bool>(result);
    n->outValues.push_back(r);
}

int main()
{
    Node additionNode;
    additionNode.callback = LogicAnd;

    additionNode.inValues.push_back((new Value("Value 1"))->SetValue<bool>(true));
    additionNode.inValues.push_back((new Value("Value 2"))->SetValue<bool>(true));

    additionNode.Run();

    bool result = additionNode.outValues[0]->GetValue<bool>();
    std::cout << "Result: " << result << std::endl;

    return 0;
}