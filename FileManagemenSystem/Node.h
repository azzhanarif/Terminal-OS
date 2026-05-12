#pragma once
#include<string>

class Node {
protected:
	std::string name;
	Node* parent;
public:

	Node(std::string n, Node* parentNode);
	std::string getName();
	void setName(std::string newName);
	

	virtual void open() = 0;
	virtual void deleteNode() = 0;
	virtual bool isFolder() = 0;
	virtual ~Node();
	virtual void removeChild(Node* childToRemove);
	virtual Node* findChild(std::string target);
	virtual void addNode(Node* newNode);
	void setParent(Node* newParent);
	virtual std::string getPath();

};
