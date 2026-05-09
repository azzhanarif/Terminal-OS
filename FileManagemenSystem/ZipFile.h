#pragma once
#include"Node.h"
#include"Folder.h"
class ZipFile: public Node{
private:
	int maxNodes;
	int nodeCount;
	Folder* insideZip;
	bool isZipped;
public:

	ZipFile(std::string name , Node* parentNode);

	virtual void open() override;
	virtual void deleteNode() override;
	virtual bool isFolder() override;
	~ZipFile();


};