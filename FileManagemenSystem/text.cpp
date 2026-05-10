#include"text.h"
#include<iostream>
#include<string>



textFile::textFile(std::string name, Node* parentNode): Node(name,parentNode) {

	maxLines = 100;
	lineCount = 0;
	cursor = 0;

	lines = new std::string[maxLines];
}

void textFile::open() {


	std::cout << "===================================================================================== " << name << " =====================================================================================\n\n\n";
	std::cin.ignore();



	while (true) {

		std::string command;
		std::string newText;

		system("cls");

		for (int i = 0; i < lineCount; i++) {
			if (i == cursor) {
				std::cout << "->";
			}
			else {
				std::cout << "  ";
			}

			std::cout << lines[i];

		}

		std::cout << "===================== COMMANDS FOR TEXT EDITOR ======================\n";
		std::cout << "[W] -> Move UP the editor\n";
		std::cout << "[S] -> Move DOWN the editor\n";
		std::cout << "[Q] -> SAVE AND QUIT the editor\n";
		std::cout << "[E] -> edit the current line\n";
		std::cout << "[C] -> ADD NEW line\n";

		std::cin.ignore();
		getline(std::cin, command);

		if (command == "w" || command == "W") {

			if (cursor != 0) {
				cursor--;
			}
		}
		else if (command == "S" || command == "s") {

			if (cursor < lineCount - 1) {
				cursor++;
			}
		}
		else if (command == "E" || command == "e") { // commans to edit the current text line
			std::cout << "->" << std::endl;
			std::string temp;

			std::getline(std::cin, temp);

			lines[cursor] = temp;

		}
		else if (command == "Q" || command == "q") {

			std::cout << "Saving Data....\n";
			std::cout << "Exiting...\n";
			break;

		}
		else if (command == "C" || command == "c") { // adds a new line in middle of lines

			std::string temp;
			std::cout << "Input the new line you want to enter: \n";
			std::cin.ignore();
			std::getline(std::cin, temp);
			for (int i = lineCount; i > cursor + 1; i--) {
				lines[i] = lines[i - 1];
			}
			lines[cursor + 1] = temp;

			lineCount++;
			cursor++;

		}

	}

}

void textFile::deleteNode() {

	std::cout << "Are you sure You want to delete? ('y' for yes , 'n' for no\n";
	char confirm;
	std::cin >> confirm;
	if (confirm == 'Y' || confirm == 'y') {

		parent->removeChild(this);
		delete this;
	}
	else {
		std::cout << "Deletion cencelled";
	}
}

textFile::~textFile() {

	delete[] lines;

}

bool textFile::isFolder() {
	return false;
}
