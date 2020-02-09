#pragma once

namespace NodeCode 
{
  struct Node 
  {
    ~Node();
    std::vector<Value*> inValues;
    std::vector<Value*> outValues;
    std::function<void(Node*)> callback;

    void Run() { if (callback) { callback(this); } }
  };
}
