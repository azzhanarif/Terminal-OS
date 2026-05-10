#pragma once
#include"Node.h"
#include<string>

class Folder : public Node {
protected:

	Node** children;
	int childCount;
	int maxCapacity;

public:

	Folder(std::string folderName, Node* parentNode);
	void addNode(Node* newNode) override; // adding node to childeren
	void renameNode(std::string oldName, std::string newName);
	void open() override;
	Node* findChild(std::string target) override;
	bool isFolder() override;
	virtual void removeChild(Node* childToRemove) override;
	~Folder() override;
	void deleteNode() override;
	void transferAllTo(Folder* destination);
	bool checkSameName(std::string name);

};
