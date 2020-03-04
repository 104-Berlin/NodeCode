#pragma once

namespace NodeCode 
{
  class NodeInstance;

  struct NodeDescription
  {
    std::vector<ValueDescription> Inputs;
    std::vector<ValueDescription> Outputs;
    std::function<void(NodeInstance*)> Callback;

    void Run(NodeInstance* instance) { if (Callback) { Callback(instance); } }
  };
  class NodeInstance
  {
    public:
    NodeInstance(NodeDescription* nodeDsc);
    ~NodeInstance();

    void Run() { if (fNodeDsc)fNodeDsc->Run(this); }

    std::vector<const Connection*> inValues;
    std::vector<Connection> outValues;
    private:
    NodeDescription* fNodeDsc;
  };

}
