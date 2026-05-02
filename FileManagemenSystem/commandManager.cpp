#include<iostream>
#include"commandManager.h"
#include"Node.h"
#include"Folder.h"
#include"text.h"
#include"mp3.h"
#include "privateFile.h"

Commands::Commands() {
	rootFolder = new Folder("root", nullptr);
	currentFolder = rootFolder;
}
void Commands::executeMkdir(std::string dirName) {
	Node* newFolder = new Folder(dirName, currentFolder);
	currentFolder->addNode(newFolder);
}

void Commands::executeTouch(std::string fileType,std::string textName) {
	if (fileType=="txt")
	{
		Node* newFile = new textFile(textName, currentFolder);
		currentFolder->addNode(newFile);
	}
	else if (fileType == "audio") {
		Node* newFile = new audioFile(textName, currentFolder);
		currentFolder->addNode(newFile);
		std::cout << "Audio File is Created bro: " << textName << "\n";
	}
	else if (fileType == "private" || "Private")
	{
		std::string passkey;
		std::cout << "Enter passkey for this file: ";
		std::getline(std::cin, passkey);
		Node* newFile = new privateFile(textName, currentFolder, passkey);
		currentFolder->addNode(newFile);
		std::cout << "Youre new Private File has been Created!" << "\n";
	}
	else {
		std::cout << "Unknown file type: " << fileType << "\n";
		std::cout << "Valid types are: txt, audio, private only !\n";
	}
}

void Commands::executeRename(std::string oldName, std::string newName) {
	currentFolder->renameNode(oldName, newName);
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
			std::cout << "There is no directory names as " << NodeName << " Instead its a file " << std::endl;
		}

	}
	else {
		std::cout << "Error: " << NodeName << " directory not found!" << std::endl;
	}


}
