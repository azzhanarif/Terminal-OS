#include"ZipFile.h"
#include"Node.h"              
#include"Folder.h"
#include<iostream>

ZipFile::ZipFile(std::string name, Node* parentNode) : Node(name, parentNode) {
	maxNodes = 100; 
	nodeCount = 0;
	insideZip = new Folder(name, parentNode);
	isZipped = true;

	std::cout << "===== Zip File created! now enter the names of the files you want to add inside it =====" << std::endl;
	int i = 0;
	while (true) {
		std::string word;
		std::cout << "Enter filename or 'exit' to finish: ";
		getline(std::cin, word);

		if (word == "exit") break; 
			Node* target = parent->findChild(word);
			if (target != nullptr) {
				
				parent->removeChild(target); // cutting it from the original folder
				insideZip->addNode(target); // placing inside zip one
			}

		
		else {
			std::cout << "ERROR: File not found, enter the name again\n";
			continue;
		}
		nodeCount++;
		i++;
	}
}

bool ZipFile::isFolder() {
	return false;
}

void ZipFile::open() {
	std::cout << "Zip File cannot be opened!! Extract them first\n";
	std::cout << "Do you want to unzip the files in the same folder ? \n";
	// if user wants to unzip then make a standard folder, which will hold all the unzipped file with + "-unzipped" appended.
	// the folder must appear in the parent folder in which the zip file was originally created

	int choice;

	while (true) {
		std::cout << "Press: \n"
			<< "(1) to unzip this folder\n"
			<< "(2) to leave it as it is\n";
		std::cin >> choice;
		if (choice <= 0 || choice > 2 || std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Invalid choice! Enter again\n";
		}
		else {
			break;
		}
	}

	if (choice == 1) {
		Node* unzippedFolder = new Folder(name + "-unzipped", parent);
		if (parent != nullptr) {
			parent->addNode(unzippedFolder);
		}

		insideZip->transferAllTo((Folder*)unzippedFolder);

		std::cout << "All files successfully extracted to folder " << unzippedFolder->getName() << "." << std::endl;
	}
	else {
		std::cout << "Files not zipped" << std::endl;
	}

}

void ZipFile::deleteNode() {
	std::cout << "Are you sure you want to delete this Zip file?\n"
		<< "(1) Yes\n"
		<< "(2) No I chamged my Mind T><T\n";
	int choice;
	while (true) {
		std::cin >> choice;
		if (choice < 1 || choice > 2 || std::cin.fail()) {
			std::cout << "Error : invalid Input!\n";
			std::cin.clear();
			std::cin.ignore();
		}
		else {
			break;
		}
	}
	
	if (choice == 1) {

		if (parent != nullptr) {
			parent->removeChild(this);
			delete this;
		}
	}
	else {
		std::cout << "OK jesa ap kahen! Deletion cenceled <3" << std::endl;
	}

		
}

ZipFile::~ZipFile() {
	delete insideZip;
	insideZip = nullptr;
}