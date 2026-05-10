#include<iostream>
#include"Folder.h"
#include"Node.h"

Folder::Folder(std::string folderName, Node* parentNode) : Node(folderName, parentNode) {
	maxCapacity = 50;
	childCount = 0;
	children = new Node * [100]; // max 100 nodes (files or folders) inside a folder
}


void Folder::addNode(Node* ptr) { // used when mkdir or new
	if (childCount >= maxCapacity) {
		std::cout << "Folder is full!\n";
		return;
	}
	children[childCount] = ptr;
	childCount++;
}

void Folder::open() { // used when ls
	for (int i = 0; i < childCount; i++) {
		std::cout << children[i]->getName() << std::endl;
	}
}

void Folder::deleteNode() {
	for (int i = 0; i < childCount; i++) {
		delete children[i];
		children[i] = nullptr;
	}
	childCount = 0;
}

void Folder :: removeChild(Node* childToRemove) {
	for (int i = 0; i < childCount;i++) {
		if (children[i] == childToRemove) {

			for (int j = i; j < childCount - 1; j++)
			{
				children[j] = children[j + 1];
			}

			children[childCount - 1] = nullptr;
			childCount--;
			break;
		}
	}
}

Folder::~Folder() {
	for (int i = 0; i < childCount; i++) {
		delete children[i];
		children[i] = nullptr;
	}
	delete[] children;
	children = nullptr;
}


void Folder::renameNode(std::string oldName, std::string newName) {
	bool found = false;
	for (int i = 0; i < childCount; i++) {
		if (oldName == children[i]->getName()) {
			children[i]->setName(newName);
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
		if (target == children[i]->getName()) {
			return children[i];
		}
	}

	return nullptr;
}

bool Folder::isFolder() {
	return true;
}

void Folder::transferAllTo(Folder* destination) {
	for (int i = 0; i < childCount; i++) {
		destination->addNode(children[i]);
		children[i]->setParent(destination);
	}
	childCount = 0;
}

bool Folder::checkSameName(std::string name) {
	for (int i = 0; i < childCount; i++) {
		if (children[i]->getName() == name) {
			std::cout << "Name: " << name << " already exists ! try something else <3" << std::endl;
			return true;
		}
	}
	return false;
}