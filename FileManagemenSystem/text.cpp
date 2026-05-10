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
    std::cout << "============================ " << name << " ============================\n";
   

    while (true) {
        system("cls");

        std::cout << "============================ " << name << " ============================\n\n";

      
        if (lineCount == 0) {
            std::cout << "File is empty! Press C to add data\n";
        }
        else {
            for (int i = 0; i < lineCount; i++) {
                if (i == cursor) {
                    std::cout << "-> " << lines[i] << "\n"; 
                }
                else {
                    std::cout << "   " << lines[i] << "\n"; 
                }
            }
        }

        std::cout << "\n===================== COMMANDS ======================\n";
        std::cout << "[W] Move UP  [S] Move DOWN  [E] Edit line\n";
        std::cout << "[C] Add line  [Q] Save & Quit\n";
        std::cout << ">> ";

        std::string command;
        getline(std::cin, command);

        if (command == "W" || command == "w") {
            if (lineCount == 0) {
                std::cout << "No lines to navigate!\n";
            }
            else if (cursor > 0) {
                cursor--;
            }
            else {
                std::cout << "Already at top!\n";
            }
        }
        else if (command == "S" || command == "s") {
            if (lineCount == 0) {
                std::cout << "No lines to navigate!\n";
            }
            else if (cursor < lineCount - 1) {
                cursor++;
            }
            else {
                std::cout << "Already at bottom!\n";
            }
        }
        else if (command == "E" || command == "e") {
            if (lineCount == 0) {
                std::cout << "No lines to edit! Press C to add a line first.\n";
            }
            else {
                std::cout << "Edit line " << cursor << ": ";
                std::string temp;
                std::getline(std::cin, temp);
                lines[cursor] = temp;
            }
        }
        else if (command == "C" || command == "c") {
            if (lineCount >= maxLines) {
                std::cout << "File is full!\n";
            }
            else {
                std::cout << "Enter new line: ";
                std::string temp;
                std::getline(std::cin, temp);

                
                for (int i = lineCount; i > cursor + 1; i--) {
                    lines[i] = lines[i - 1];
                }

                if (lineCount == 0) {
                    lines[0] = temp;  
                }
                else {
                    lines[cursor + 1] = temp;
                    cursor++;
                }
                lineCount++;
            }
        }
        else if (command == "Q" || command == "q") {
            std::cout << "Saving...\nExiting...\n";
            break;
        }
        else {
            std::cout << "Unknown command!\n";
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
