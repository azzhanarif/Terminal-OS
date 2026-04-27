#include "Node.h"


Node::Node(std::string nodeName = "New Item", Node* parentNode = nullptr)  {
    name = nodeName;
    parent = parentNode;
}

Node::Node() {
    name = "NULL";
    parent = nullptr;
}

std::string Node::getName() {
    return name;
}

void Node::setName(std::string newName) {
    this->name = newName;
}

Node::~Node(){
    delete[] parent;
    parent = nullptr;
}