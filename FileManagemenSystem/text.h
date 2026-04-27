#pragma once
#include"Node.h"

class textFile : public Node{
private:

	std::string* lines;
	int lineCount;
	int maxLines;
	int cursor;

public:

	textFile(std::string name, Node* parentNode);

	void open() override;
	void deleteNode() override;
	bool isFolder() override;
	~textFile() override;
	
};