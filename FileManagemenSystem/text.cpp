#include"text.h"

textFile::textFile(std::string name, Node* parentNode): Node(name,parentNode) {

	maxLines = 100;
	lineCount = 0;
	cursor = 0;

	lines = new std::string[maxLines];
}

void textFile::open() {
	// currently AZHAN IS WORKING ON THIS
}

void textFile::deleteNode() {

	// AZHAN WORKING ON TS

}

textFile::~textFile() {

	//AZHAN WORKKING ON TS

}

bool textFile::isFolder() {
	return false;
}