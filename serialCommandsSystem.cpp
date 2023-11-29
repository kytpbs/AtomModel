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
