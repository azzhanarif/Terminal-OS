#include<iostream>
#include"commandManager.h"
#include"Node.h"
#include"Folder.h"
#include"text.h"

Commands::Commands() {
    rootFolder = new Folder("root", nullptr);
    currentFolder = rootFolder;
}
void Commands::executeMkdir(std::string dirName) {
	Node* newFolder = new Folder(dirName, currentFolder);
	currentFolder->addNode(newFolder);
}

void Commands::executeTouch(std::string textName) {

	Node* newFile = new textFile(textName, currentFolder);
	currentFolder->addNode(newFile);
}

void Commands::executeRename(std::string oldName, std::string newName) {
	currentFolder->renameNode(oldName,newName);
}

void Commands::executeLs() {
	currentFolder->open();
}

void Commands::executeCd(std::string NodeName) {
	
	// root> cd folder will bring user inside folder which means the only chang will be currentFolder
	if (NodeName == "..") {
		currentFolder = rootFolder;
	}

	Node* target = currentFolder->findChild(NodeName);

	if (target != nullptr) {

		if (target->isFolder()) {
			currentFolder = (Folder*)currentFolder->findChild(NodeName);
		}
		else {
			std:: cout << "There is no directory names as " << NodeName << " Instead its a file " << std::endl;
		}

	}
	else {
		std :: cout << "Error: " << NodeName << " directory not found!" << std :: endl;
	}


}