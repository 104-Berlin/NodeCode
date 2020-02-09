#pragma once

namespace NodeCode 
{
  struct Node 
  {
    std::vector<const Type const*> inValues;
    std::vector<const Type const*> outValues;
    std::function<void()> callback;
  };
}
