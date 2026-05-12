#include "mp3.h"
#include <iostream>
#include <string>
#include <cstdlib>

#include "mp3.h"
#include <iostream>
#include <string>
#include <cstdlib>

audioFile::audioFile(std::string name, Node* parent) : Node(name, parent) {
    // YE CHAECK KARLAY PAIR IMPORTANT HAI 
    filePath = this->getPath(); 
    
    std::cout << "The recording has started pls speak!\n";
    
    // Wrapped filePath in quotes just in case, Windows command line prefers it
    std::string recordCmd = "ffmpeg -f dshow -i audio=\"Microphone Array (Intel® Smart Sound Technology for Digital Microphones)\" -t 5 \"" + filePath + "\"";
    system(recordCmd.c_str());   
    
    std::cout << "Recording is completed your File is saved as: " << name << "\n";
}

void audioFile::open() {
    std::cout << "Playing: " << name << "\n";
    // Added empty quotes "" to prevent Windows 'start' bugs
    std::string playCmd = "start \"\" \"" + filePath + "\"";
    system(playCmd.c_str());
}

void audioFile::deleteNode() {
    // 1. Delete the physical file from the hard drive via CMD
    std::string deleteCmd = "del \"" + filePath + "\"";
    system(deleteCmd.c_str());

    // 2. Remove the node from your C++ memory tree
    if (parent != nullptr) {
        parent->removeChild(this);
    }

    std::cout << name << " deleted.\n";

    // 3. Free the memory
    delete this;
}
 
bool audioFile::isFolder() {  //its a audio file thus terminates node here
    return false;
}

audioFile::~audioFile() { //already handled in deleteNodec
}

