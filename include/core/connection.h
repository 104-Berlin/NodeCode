#pragma once

namespace NodeCode {
class NodeInstance;

class Connection {
 private:
  NodeInstance* fOrigin;
  std::vector<NodeInstance*> fEndpoints;
  std::string fVarName;

  static size_t cIndex;

 public:
  bool fHasVal;
  Connection();
  Connection(NodeInstance* origin);
  bool addEndpoint(NodeInstance* endpoint);
  std::string getVarName();
};
}  // namespace NodeCode