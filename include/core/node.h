#pragma once

namespace NodeCode 
{
  struct Node 
  {
    std::vector<const Value const*> inValues;
    std::vector<const Value const*> outValues;
    std::function<void(Node*)> callback;

    void Run() { if (callback) { callback(this); } }
  };
}
