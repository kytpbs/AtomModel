#include "serialCommandsSystem.h"

CloudSerialSystem::CloudSerialSystem(String* cloudSerialObject) {
    this->cloudSerialObject = cloudSerialObject;
}

void CloudSerialSystem::addCommand(String commandName, void (*function)(CloudSerialSystem*, std::vector<String>*)) {
    this->commandsList[commandName] = function;
}

void CloudSerialSystem::print(String message) {
    this->cloudSerialObject->operator= (message);
}

void splitString(String string, std::vector<String>* argv) {
    int spaceIndex = string.indexOf(" ");
    
    if (spaceIndex == -1) {
        spaceIndex = string.length();
    }

    String commandName = string.substring(0, spaceIndex);
    argv->push_back(commandName);
    String args = string.substring(spaceIndex + 1);
    int lastSpaceIndex = 0;
    
    while (args.indexOf(" ") != -1) {
        spaceIndex = args.indexOf(" ");
        argv->push_back(args.substring(lastSpaceIndex, spaceIndex));
        args = args.substring(spaceIndex + 1);
    }
    argv->push_back(args);
}

void CloudSerialSystem::checkForCommands(String command) {
    int spaceIndex = command.indexOf(" ");
    bool hasArgs = spaceIndex != -1;
    
    if (spaceIndex == -1) {
        spaceIndex = command.length();
    }

    String commandName = command.substring(0, spaceIndex);
    if (this->commandsList.find(commandName) != this->commandsList.end()) {
        std::vector<String> argv = std::vector<String>();
        if (hasArgs) {splitString(command.substring(spaceIndex), &argv);} // Split the string into arguments, if it has any
        this->commandsList[command](this, &argv);
    }
    else {
        this->print("Command not found");
    }
}
