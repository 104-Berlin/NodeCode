#pragma once

namespace NodeCode 
{
  struct Node 
  {
    std::vector<const Value const*> inValues;
    std::vector<const Value const*> outValues;
  };
}
