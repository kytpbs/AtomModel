/**
 * @file serialCommandsSystem.h
 * @brief A library for creating commands for serial communication using ArduinoIoTCloud.
 * uses the "messaging" widget from ArduinoIoTCloud. and the "String" object from Arduino.h.
*/
#if !defined(SERIALCOMMANDSSYSTEM_H) && (defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266)) // STD does not exist on Arduino
#define SERIALCOMMANDSSYSTEM_H

#include <Arduino.h>
#include <map>
#include <vector>

#include "stringTools.h"

class CloudSerialSystem {
    private:
        String* cloudSerialObject;
        std::map<String, void (*)(CloudSerialSystem*, std::vector<String>* /*Argv*/)> commandsList;
    public:
    CloudSerialSystem(String* cloudSerialObject);
    void addCommand(String commandName, void (*function)(CloudSerialSystem*, std::vector<String>*));
    void checkForCommands(String command);
    void checkForCommands() { this->checkForCommands(*this->cloudSerialObject); };
    void print(String message);
    void debugPrint(String message);
};
#endif
