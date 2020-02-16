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
    //Define first node
    Node additionNode;
    additionNode.callback = Addition<int>;
    additionNode.inValues.push_back((new Value("Value 1"))->SetValue<int>(2));
    additionNode.inValues.push_back((new Value("Value 2"))->SetValue<int>(2));
    additionNode.outValues.push_back((new Value("Addition Result")));

    //Define second node
    Node multiplyNode;
    multiplyNode.callback = Multiply<int>;
    multiplyNode.inValues.push_back(additionNode.outValues[0]);
    multiplyNode.inValues.push_back((new Value("Input 2"))->SetValue<int>(4));
    multiplyNode.outValues.push_back(new Value("MulResult"));

    multiplyNode.Run();
    additionNode.Run();

    int result = multiplyNode.outValues[0]->GetValue<int>();
    std::cout << "Result: " << result << std::endl;

    return 0;
}