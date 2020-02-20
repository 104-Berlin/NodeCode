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

void SelectNode(Node* n) 
{
    int selectedIndex = n->inValues[0]->GetValue<int>();

    std::cout << selectedIndex << std::endl;
    
    const std::vector<Value*>& inputs = n->inValues;
    if (selectedIndex > inputs.size() - 2) {
        n->outValues.push_back((new Value("Out value", EType::Int))->SetValue<int>(0));
        return;
    }
    n->outValues.push_back(n->inValues[selectedIndex + 1]);
}

int main()
{
    Node testNode;
    testNode.callback = Addition<int>;
    testNode.inValues.push_back((new Value("In Value 1", EType::Int))->SetValue<int>(3));
    testNode.inValues.push_back((new Value("In Value 1", EType::Int))->SetValue<int>(3));
    testNode.outValues.push_back(new Value("Out value", EType::Int));

    testNode.Run();

    int result = testNode.outValues[0]->GetValue<int>();
    std::cout << "Result: " << result << std::endl;

    return 0;
}