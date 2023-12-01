#include "serialCommandsSystem.h"
#ifdef SERIALCOMMANDSSYSTEM_H // only include this file if serialCommandsSystem.h is included
#include <vector>

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
        std::vector<String> argv;
        if (hasArgs) { // Split the string into arguments, if it has any
            Serial.println("Splitting string");
            splitString(command.substring(spaceIndex), &argv);
            Serial.print("Split Complete");
            delay(100);
        }
        Serial.println("Running command");
        this->commandsList[commandName](this, &argv);
        Serial.println("Command complete");
    }
    else {
        this->print("Command not found");
    }
}
#endif
