#include <core/prefix.h>

using namespace NodeCode;

void CLI::addType() {
  while (true) {
    string typeName;
    while (true) {
      putLine("Enter Typename");
      typeName = getName();
      if (fTypes.find(typeName) == fTypes.end())
        break;
      else
        putLine("Type: " + typeName + " exists already!");
    }

    while (true) {
      putLine("Enter C Type");
      string type = getLine();
      if (type == "int") {
        fTypes[typeName] = new PrimitiveType(Int);
        return;
      } else if (type == "float") {
        fTypes[typeName] = new PrimitiveType(Float);
        return;
      } else if (type == "double") {
        fTypes[typeName] = new PrimitiveType(Double);
        return;
      } else if (type == "long") {
        fTypes[typeName] = new PrimitiveType(Long);
        return;
      } else if (type == "char") {
        fTypes[typeName] = new PrimitiveType(Char);
        return;
      } else if (type == "bool") {
        fTypes[typeName] = new PrimitiveType(Bool);
        return;
      }
    }
  }
}

void CLI::add() {
  while (true) {
    putLine("add > type q");
    string action = getLine();
    if (action == "type") {
      addType();
    } else if (action == "q") {
      return;
    }
  }
}

void CLI::putLine(string line) { std::cout << line << std::endl; }

string CLI::getName() {
  return getLine();
}

string CLI::getLine() {
  string in;
  while (true) {
    std::getline(std::cin, in);
    size_t spaceIndex = in.find_first_of(' ');
    if(spaceIndex > 0){
      putLine("-----------------------------------");
      return in.substr(0,spaceIndex);
    }
  }
}

void CLI::getTypes() {
  for (pair<string, Type*> p : fTypes) {
    putLine(p.first+" : "+ p.second->getCType());
  }
}

void CLI::get() {
  while (true) {
    putLine("get > types q");
    string action = getLine();
    if (action == "types") {
      getTypes();
    } else if (action == "q") {
      return;
    }
  }
}

void CLI::run() {
  while (true) {
    putLine("add get q");
    string action = getLine();
    if (action == "add") {
      add();
    } else if (action == "get") {
      get();
    } else if (action == "q") {
      return;
    }
  }
}
