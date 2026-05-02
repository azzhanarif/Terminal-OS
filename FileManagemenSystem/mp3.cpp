#include "mp3.h"
#include <iostream>
#include <string>
#include <cstdlib>

audioFile::audioFile(std::string name, Node* parent) : Node(name, parent) {
    filePath = "root\\" + name + ".mp3";
    std::cout << "The recording has started pls speak!\n";
    std::string recordCmd = "ffmpeg -f dshow -i audio=\"Microphone Array (Intel® Smart Sound Technology for Digital Microphones)\" -t 5 " + filePath;
    system(recordCmd.c_str());   //System will run My command in CMD from here in c++
    std::cout << "Recording is completed your File is saved as: " << name << ".mp3\n";
}

void audioFile::open() {
    std::cout << "Playing: " << name << "\n";
    std::string playCmd = "start " + filePath;
    system(playCmd.c_str());
}

void audioFile::deleteNode() {
    std::string deleteCmd = "del " + filePath;   //Here del is like CMD ccommand to permenant delete
    system(deleteCmd.c_str());
    std::cout << name << " deleted.\n";
}
 
bool audioFile::isFolder() {  //its a audio file thus terminates node here
    return false;
}

audioFile::~audioFile() { //already handled in deleteNodec
}