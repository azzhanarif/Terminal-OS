#pragma once
#include "Node.h"
#include <string>

class privateFile : public Node {
private:
    std::string passkey;
    std::string* lines;
    int lineCount;
    int maxLines;

public:
    privateFile(std::string name, Node* parent, std::string pw);
    void open() override;
    void deleteNode() override;
    bool isFolder() override;
    ~privateFile() override;
};