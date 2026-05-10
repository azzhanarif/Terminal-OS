#include<iostream>
#include"commandManager.h"
#include"Node.h"
#include"Folder.h"
#include"text.h"
#include"mp3.h"
#include "privateFile.h"
#include "ZipFile.h"
#include<sstream>

Commands::Commands() {
	rootFolder = new Folder("root", nullptr);
	currentFolder = rootFolder;
}
void Commands::executeMkdir(std::string dirName) {
	Node* newFolder = new Folder(dirName, currentFolder);
	currentFolder->addNode(newFolder);
}

void Commands::executeNew() {

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
				std::cin.ignore();
				std::getline(std::cin, name);

				std::cout << "Creating text file...\n";

				Node* newText = new textFile(name + ".txt", currentFolder);
				currentFolder->addNode(newText);

				break;
			}
			else if (choice == 2) {
				std::cout << "Creating Zip file...\n";
				std::string word;

				std::cout << "Enter the name of the zip file you want to make: ";
				std::cin.ignore();
				getline(std::cin, word);

				Node* tempZip = new ZipFile(word + ".zip", currentFolder);
				currentFolder->addNode(tempZip);

				break;
			}
			else if (choice == 3) {
				std::cout << "Creating Private file...\n";

				std::string name;
				std::string password;

				std::cout << "Enter the name of file you want to create: ";
				std::cin.ignore();
				getline(std::cin, name);
				std::cout << "Set you password (dont do \"yourName123\" !): ";
				std::cin.ignore();
				getline(std::cin, password);

				Node* newPrivtFile = new privateFile(name + ".pvt", currentFolder, password);
				currentFolder->addNode(newPrivtFile);

				break;
			}
			else if (choice == 4) {
				std::string name;
				std::cout << "Enter the name of the audio file: ";
				std::cin.ignore();
				std::getline(std::cin, name);
				Node* mp3File = new audioFile(name + ".mp3", currentFolder);
			}

		}

	}

}

void Commands::executeRename(std::string oldName) {
	std::string newName;
	std::cout << "Enter the new name you want: ";
	getline(std::cin, newName);
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
	if (target != nullptr) {
		target->deleteNode();
	}
	else {
		std::cout << "File not found!" << std::endl;
	}
}

void Commands::executeCommandManager(std::string input) {

	std::stringstream ss(input);

	std::string command;
	std::string nodeName;

	ss >> command;
	ss >> nodeName;

	if (command == "mkdir") {

		if (nodeName.empty()) {
			std::cout << "Error: File/folder name missing\n";
			return;
		}

		executeMkdir(nodeName);
		std::cout << "Folder created: " << nodeName << "\n";
	}
	else if (command == "Ls") {
		executeLs();
	}
	else if (command == "cd") {

		if (nodeName.empty()) {
			std::cout << "Error: file/folder name missing\n";
			return;
		}

		executeCd(nodeName);
	}
	else if (command == "New") {
		executeNew();
	}
	else if (command == "Rm") {
		if (nodeName.empty()) {
			std::cout << "Error: file/folder name missing\n";
			return;
		}
		executeRm(nodeName);
	}
	else if (command == "Rename") {

		if (nodeName.empty()) {
			std::cout << "Error: file/folder name missing\n";
			return;
		}
		executeRename(nodeName);
	}
	else {
		std::cout << "Command " << command << " Not found! \n"
			<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		return;
	}

	return;

}


void Commands::runTerminal() {

	std::cout << "=========== Welcome To File Mangement System ======== \n";
	std::cout << "                                                      Bajwa union pvt ltd\n\n\n";

	while (true) {

		std::string userInput;
		std::cout << ">";
		getline(std::cin, userInput);
		executeCommandManager(userInput);

	}
}