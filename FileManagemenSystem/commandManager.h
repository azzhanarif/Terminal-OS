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
	void executeRename(std::string oldName, std::string newName); // DONE
	void executeTouch(std::string fileName); // DONE
	void executeRm(std::string nodeName);
	void executeCd(std::string nodeName); // DONE

};

