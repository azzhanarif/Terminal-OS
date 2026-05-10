#pragma once
#include<string>
#include"Folder.h"


class Commands {
protected:

	Folder* currentFolder;
	Folder* rootFolder;

public:

	Commands();

	void executeLs(); // DONE
	void executeMkdir(std::string dirName); // DONE
	void executeRename(std::string oldName); // DONE
	void executeNew(); // DONE
	void executeRm(std::string nodeName); // DONE
	void executeCd(std::string nodeName); // DONE
	void executeSearch(std::string nodeName); 
	void runTerminal();
	void executeCommandManager(std::string input);
	bool hasSpace(std::string name);

};

