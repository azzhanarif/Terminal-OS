#include "privateFile.h"
#include <iostream>
#include <string>

privateFile::privateFile(std::string name, Node* parent, std::string pw): Node(name, parent)
{
    passkey = pw;
    lineCount = 0;
    maxLines = 100;
    lines = new std::string[maxLines];
    std::cout << "Private file created: " << name << ".priv\n";
}

void privateFile::open()
{
    std::string userInput;
    std::cout << "Enter passkey: ";
    std::getline(std::cin, userInput);

    if (userInput != passkey) {
        std::cout << "Wrong passkey! Access denied.\n";
        return;
    }
    std::cout << "\n" << name << ".priv\n";
    if (lineCount == 0) {
        std::cout << "(empty file)\n";
    }
    for (int i = 0; i < lineCount; i++) {
        std::cout << "[" << i << "] " << lines[i] << "\n";
    }
    std::cout << "\n(a)add line  (e)edit line  (q)quit\n";
    bool editing = true;
    while (editing) {
        std::cout << "Enter command: ";
        char cmd;
        std::cin >> cmd;
        std::cin.ignore();

        if (cmd == 'a') {
            std::string newLine;
            std::cout << "Enter new line: ";
            std::getline(std::cin, newLine);
            lines[lineCount++] = newLine;
        }
        else if (cmd == 'e') {
            int lineNum;
            std::cout << "Enter line number to edit: ";
            std::cin >> lineNum;
            std::cin.ignore();
            if (lineNum >= 0 && lineNum < lineCount) {
                std::cout << "Enter new text: ";
                std::getline(std::cin, lines[lineNum]);
            }
            else {
                std::cout << "Invalid line number!\n";
            }
        }
        else if (cmd == 'q') {
            editing = false;
            std::cout << "File closed.\n";
        }
    }
}

void privateFile::deleteNode()
{
    std::string userInput;
    std::cout << "Enter passkey to delete: ";
    std::getline(std::cin, userInput);

    if (userInput != passkey)
    {
        std::cout << "Wrong passkey! Deletion cancelled.\n";
        return;
    }
    std::cout << "Are you sure you want to delete " << name << "? (yes/no): ";
    std::string confirm;
    std::getline(std::cin, confirm);

    if (confirm == "yes"||"Yes")
    {
        delete[] lines;
        lines = nullptr;
        std::cout << name << " deleted.\n";
    }
    else {
        std::cout << "Deletion cancelled.\n";
    }
}

bool privateFile::isFolder() {
    return false;
}

privateFile::~privateFile() {
    if (lines != nullptr) {
        delete[] lines;
        lines = nullptr;
    }
}