#pragma once
#include"Node.h"
#include<string>

class audioFile :public Node
{
	std::string filePath;
public:
	audioFile(std::string name, Node* parent);

	//Pure virtual class Node's must funcs: 
	void open() override; 
	void deleteNode() override;
	bool isFolder() override;
	~audioFile() override;
};