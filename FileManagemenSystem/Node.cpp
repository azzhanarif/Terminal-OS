#include "Node.h"


Node::Node(std::string nodeName = "New Item", Node* parentNode = nullptr)  {
    name = nodeName;
    parent = parentNode;
}

std::string Node::getName() {
    return name;
}

void Node::setName(std::string newName) {
    this->name = newName;
}

void Node::setParent(Node* newParent) {
    parent = newParent;
}

Node::~Node(){
    delete[] parent;
    parent = nullptr;
}
