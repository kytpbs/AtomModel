/**
 * @file serialCommandsSystem.h
 * @brief A library for creating commands for serial communication using ArduinoIoTCloud.
 * uses the "messaging" widget from ArduinoIoTCloud. and the "String" object from Arduino.h.
*/

#ifndef SERIALCOMMANDSSYSTEM_H
#define SERIALCOMMANDSSYSTEM_H

#include <Arduino.h>
#include <map>
// #include <WString.h>

class CloudSerialSystem {
    private:
        String* cloudSerialObject;
        std::map<String, void (*)(CloudSerialSystem*)> commandsList;
    public:
    CloudSerialSystem(String* cloudSerialObject);
    void addCommand(String command, void (*function)(CloudSerialSystem*));
    void checkForCommands(String command);
    void checkForCommands() { this->checkForCommands(*this->cloudSerialObject); };
    void print(String message);
};
#endif
