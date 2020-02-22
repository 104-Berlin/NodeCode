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

template <typename T>
void Subtract(Node* n) 
{
    T result;
    result = n->inValues[0]->GetValue<T>() - n->inValues[1]->GetValue<T>();
    n->outValues[0]->SetValue<T>(result);
}

template <typename T>
void Divide(Node* n) 
{
    T result;
    result = n->inValues[0]->GetValue<T>() / n->inValues[1]->GetValue<T>();
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

template <typename T>
void SelectNode(Node* n) 
{
    int selectedIndex = n->inValues[0]->GetValue<int>();

    const std::vector<Value*>& inputs = n->inValues;
    if (selectedIndex > inputs.size() - 2) {
        n->outValues.push_back((new Value("Out value"))->SetValue<T>(0));
        return;
    }
    n->outValues[0]->SetValue<T>(n->inValues[selectedIndex + 1]->GetValue<T>());
}

int main()
{
    Node selectNode;
    selectNode.callback = SelectNode<float>;
    selectNode.inValues.push_back((new Value("In Value 1"))->SetValue<int>(0));
    selectNode.inValues.push_back((new Value("In Value 1"))->SetValue<float>(3.234));
    selectNode.inValues.push_back((new Value("In Value 1"))->SetValue<float>(1.32));
    selectNode.outValues.push_back(new Value("Out Value"));


    Node secondNode;
    secondNode.callback = Addition<float>;
    secondNode.inValues.push_back((new Value("Addition value"))->SetValue<float>(4));
    secondNode.inValues.push_back(selectNode.outValues[0]);
    secondNode.outValues.push_back(new Value("Out value"));

    Node minusNode;
    minusNode.callback = Subtract<float>;
    minusNode.inValues.push_back(secondNode.outValues[0]);
    minusNode.inValues.push_back((new Value("First in"))->SetValue<float>(4));
    minusNode.outValues.push_back(new Value("Out value"));
    
    selectNode.Run();
    secondNode.Run();
    minusNode.Run();

    float result = minusNode.outValues[0]->GetValue<float>();
    std::cout << "Result: " << result << std::endl;

    GarbageCollector::CleanUp();

    return 0;
}
