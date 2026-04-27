#include<iostream>
#include"Folder.h"

Folder::Folder(std::string folderName, Node* parentNode): Node(folderName,parentNode) {
	maxCapacity = 50;
	childCount = 0;
	childeren = new Node * [100]; // max 100 nodes (files or folders) inside a folder
}


void Folder::addNode(Node* ptr) { // used when Mkdir/touch
	childeren[childCount] = ptr;
	childCount++;
}

void Folder::open() { // used when ls
	for (int i = 0; i < childCount;i++) {
		std::cout << childeren[i]->getName() << std::endl;
	}
}

void Folder::deleteNode() { // used when rm
	for (int i = 0; i < childCount; i++) {
		delete childeren[i];
	}
}

Folder :: ~Folder(){
	deleteNode();
	delete[] childeren;
}


void Folder::renameNode(std::string oldName, std::string newName) {
	bool found = false;
	for (int i = 0; i < childCount; i++) {
		if (oldName == childeren[i]->getName()) {
			childeren[i]->setName(newName);
			found = true;
			break;
		}
	}
	if (!found) {
		std::cout << "No node with the name " << oldName << " found in this directory" << std::endl;
	}
	else {
		std::cout << "Name of the node changed from " << oldName << " to " << newName << std::endl;
	}
}

Node* Folder::findChild(std::string target) {

	for (int i = 0; i < childCount; i++) {
		if (target == childeren[i]->getName()) {
			return childeren[i];
		}
	}

	return nullptr;
}

bool Folder::isFolder() {
	return true;
}