#include "core/prefix.h"
#include <iostream>

using namespace NodeCode;

template <typename T>
void Addition(NodeInstance* n) 
{
    T result;
    result = 0;
    const std::vector<const Connection*>& inputs = n->inValues;
    for (auto& value : inputs)
    {
        result += value->GetValue<T>();
    }
    n->outValues[0].SetValue<T>(result);
}

template <typename T>
void Multiply(NodeInstance* n)
{
    T result;
    result = 1;
    const std::vector<const Connection*>& inputs = n->inValues;
    for (auto& value : inputs)
    {
        result *= value->GetValue<T>();
    }
    n->outValues[0].SetValue<T>(result);
}

template <typename T>
void Subtract(NodeInstance* n) 
{
    T result;
    result = n->inValues[0]->GetValue<T>() - n->inValues[1]->GetValue<T>();
    n->outValues[0].SetValue<T>(result);
}

template <typename T>
void Divide(NodeInstance* n) 
{
    T result;
    result = n->inValues[0]->GetValue<T>() / n->inValues[1]->GetValue<T>();
    n->outValues[0].SetValue<T>(result);
}

void LogicAnd(NodeInstance* n)
{
    bool result;
    result = true;
    const std::vector<const Connection*>& inputs = n->inValues;
    for (auto& value : inputs)
    {
        result = result && value->GetValue<bool>();
    }
    n->outValues[0].SetValue<bool>(result);
}

template <typename T>
void SelectNode(NodeInstance* n) 
{
    int selectedIndex = n->inValues[0]->GetValue<int>();

    const std::vector<const Connection*>& inputs = n->inValues;
    if (selectedIndex > inputs.size() - 2) {
        n->outValues[0].SetValue<T>(0);
        return;
    }
    n->outValues[0].SetValue<T>(n->inValues[selectedIndex + 1]->GetValue<T>());
}

int main()
{
    NodeDescription additionNode;
    additionNode.Callback = Addition<int>;
    additionNode.Inputs.push_back({"Input 1", EType::Int});
    additionNode.Inputs.push_back({"Input 2", EType::Int});
    additionNode.Outputs.push_back({"Output", EType::Int});

    NodeDescription constantInt;
    constantInt.Outputs.push_back({"Value", EType::Int});

    NodeInstance additionInstance(&additionNode);

    NodeInstance in1(&constantInt);
    in1.outValues[0].SetValue<int>(2);

    NodeInstance in2(&constantInt);
    in2.outValues[0].SetValue<int>(8);

    additionInstance.inValues.push_back(&in1.outValues[0]);
    additionInstance.inValues.push_back(&in2.outValues[0]);


    additionInstance.Run();

    int result = additionInstance.outValues[0].GetValue<int>();
    std::cout << "Result: " << result << std::endl;

    return 0;
}
