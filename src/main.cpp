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

    const std::vector<Value*>& inputs = n->inValues;
    if (selectedIndex > inputs.size() - 2) {
        n->outValues.push_back((new Value("Out value"))->SetValue<int>(0));
        return;
    }
    n->outValues[0] = n->inValues[selectedIndex + 1];
}

int main()
{
    Node selectNode;
    selectNode.callback = SelectNode;
    selectNode.inValues.push_back((new Value("In Value 1"))->SetValue<int>(0));
    selectNode.inValues.push_back((new Value("In Value 1"))->SetValue<int>(3));
    selectNode.inValues.push_back((new Value("In Value 1"))->SetValue<int>(1));
    selectNode.outValues.push_back(nullptr);

    selectNode.Run();

    Node secondNode;
    secondNode.callback = Addition<int>;
    secondNode.inValues.push_back((new Value("Addition value"))->SetValue<int>(4));
    secondNode.inValues.push_back(selectNode.outValues[0]);
    secondNode.outValues.push_back(new Value("Out value"));

    secondNode.Run();

    int result = secondNode.outValues[0]->GetValue<int>();
    std::cout << "Result: " << result << std::endl;

    GarbageCollector::CleanUp();

    return 0;
}