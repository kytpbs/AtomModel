#include "serialCommandsSystem.h"

CloudSerialSystem::CloudSerialSystem(String* cloudSerialObject) {
    this->cloudSerialObject = cloudSerialObject;
}

void CloudSerialSystem::addCommand(String command, void (*function)(CloudSerialSystem*)) {
    this->commandsList[command] = function;
}

void CloudSerialSystem::print(String message) {
    this->cloudSerialObject->operator= (message);
}

void CloudSerialSystem::checkForCommands(String command) {
    if (this->commandsList.find(command) != this->commandsList.end()) {
        this->commandsList[command](this);
    }
    else {
        this->print("Command not found");
    }
}
