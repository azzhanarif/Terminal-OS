#pragma once
#include<string>

class Node {
protected:
	std::string name;
	Node* parent;
public:

	Node(std::string n, Node* parentNode);
	std::string getName();

	virtual void open() = 0;
	virtual void deleteNode() = 0;
	void setName(std::string newName);
	virtual bool isFolder() = 0;
	virtual ~Node();
	virtual void removeChild(Node* childToRemove);

};