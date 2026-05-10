#include<iostream>
#include<string>
#include"commandManager.h"
#include"Node.h"
#include"Folder.h"
#include"text.h"
#include"mp3.h"
#include "privateFile.h"
#include "ZipFile.h"
#include<sstream>

bool Commands::hasSpace(std::string name) { //helper

	int len = name.length();
	for (int i = 0; i < len;i++) {
		if (name[i] == ' ') {
			return true;
		}
	}
	return false;
}

Commands::Commands() {
	rootFolder = new Folder("root", nullptr);
	currentFolder = rootFolder;
}

void Commands::executeMkdir(std::string dirName) {
	
	if (currentFolder->checkSameName(dirName)) {
		return;
	}

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

		while (true) {
			std::cout << "Enter Your choice: ";
			std::cin >> choice;

			if (std::cin.fail() || choice < 1 || choice > 4) {
				std::cout << "Invalid Input! Enter again\n";
				std::cin.clear();
				std::cin.ignore(1000, '\n');
			}
			else {
				break;
			}
		}

			if (choice == 1) {

				std::cout << "Creating textFile....." << std::endl;

				std::string name;
				std::cout << "Enter the name of the text file: ";
				std::cin.ignore();
				std::getline(std::cin, name);

				if (hasSpace(name)) {
					std::cout << "Space is not allowed while naming!" << std::endl;
					return;
				}

				std::string fullName = name + ".txt";

				if (currentFolder->checkSameName(fullName)) {
					return;
				}

				Node* newText = new textFile(fullName, currentFolder);
				currentFolder->addNode(newText);
				std::cout << "Text File created with name " << fullName << "\n";
				break;
			}
			else if (choice == 2) {
				std::cout << "Creating Zip file...\n";
				std::string word;

				std::cout << "Enter the name of the zip file you want to make: ";
				std::cin.ignore();
				getline(std::cin, word);

				if (hasSpace(word)) {
					std::cout << "Space is not allowed while naming!" << std::endl;
					return;
				}

				if (currentFolder->checkSameName(word + ".zip")) { // same name checker
					return;
				}

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

				if (hasSpace(name)) {
					std::cout << "Space is not allowed while naming!" << std::endl;
					return;
				}

				if (currentFolder->checkSameName(name + ".pvt")) { // same name checker
					return;
				}

				std::cout << "Set you password (dont do \"yourName123\" !): ";
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

				if (hasSpace(name)) {
					std::cout << "Space is not allowed while naming!" << std::endl;
					return;
				}

				if (currentFolder->checkSameName(name + ".mp3")) {
					return;
				}

				std::cout << "Creating Mp3 File...\n";
				Node* mp3File = new audioFile(name + ".mp3", currentFolder);
				currentFolder->addNode(mp3File);  
				std::cout << "Mp3 file created!\n";  
				break;  
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
		std::cout << "Bck to root folder \"" << rootFolder->getName() << "\"\n";
		return;
	}

	Node* target = currentFolder->findChild(NodeName);

	if (target != nullptr) {

		if (target->isFolder()) {
			std::string prevFolder = currentFolder->getName();
			currentFolder = (Folder*)currentFolder->findChild(NodeName); // for cd folder
			std::cout << prevFolder << " >";

		}
		else {
			std::cout << "Inside <<<<<<<" << NodeName << ">>>>>>>\n";
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
	ss >> command;

	std::string nodeName;
	std::getline(ss, nodeName);

	if (!nodeName.empty() && nodeName[0] == ' ') {
		nodeName = nodeName.substr(1);           // substr(1) means "give me a substring starting from index 1 to the end"
	}

	if (hasSpace(nodeName)) { // checkks for the same name
		
		std::cout << "spaces are not allowed in names! try putting \"_\" instead of space\n";
		return;

	}



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

	std::cout << "======================================= Welcome To Azox's Private File Mangement System V 1.0 ================================================== \n";

	while (true) {

		std::string userInput;
		std::cout << currentFolder->getName() << " >";
		getline(std::cin, userInput);
		executeCommandManager(userInput);

	}
}