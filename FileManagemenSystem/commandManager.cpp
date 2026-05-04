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

void Commands::executeNew(std::string textName) {

	std::cout << "Which type of file do you Want to create: \n"
		<< "(1) Text File\n"
		<< "(2) Zip File\n"
		<< "(3) Private File\n"
		<< "(4) Mp3 File\n";

	int choice;
	while(true){
		std::cout << "Enter Your choice: ";
		std::cin >> choice;
		if (choice <= 0 || choice >= 5) {
			std::cout << "Invalid choice!\n Enter Again: ";
		}
		else {
			if (choice == 1) {

				std:: cout << "Enter the name of the text file: ";
				std::string name;
				std::getline(std::cin, name);

				std::cout << "Creating text file...\n";

				Node* newText = new textFile(name,currentFolder);
				currentFolder->addNode(newText);

				break;
			}
			else if (choice == 2) {
				std::cout << "Creating Zip file...\n";
				// UNDER CONSTRUCTION
				break;
			}
			else if (choice == 3) {
				std::cout << "Creating Private file...\n";
				// UNDR CONSTRUCTION
				break;
			}
			else if (choice == 4) {

				std::cout << "Creating Mp3 file...\n";
				std::string name;
				std::cout << "Enter the name of the audio file you want to create:  " << std::endl;
				Node* mp3File = new audioFile(name, currentFolder);
				currentFolder->addNode(mp3File);
				break;

			}

		}

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
			currentFolder = (Folder*)currentFolder->findChild(NodeName); // for cd folder
		}
		else {
			target->open(); // for cd any type of file
		}

	}
	else {
		std :: cout << "Error: " << NodeName << " Node not found!" << std :: endl;
	}
}

void Commands::executeRm(std::string name) {

	Node* target = currentFolder->findChild(name);
	target->deleteNode();
}