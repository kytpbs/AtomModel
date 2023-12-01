#if !defined(COMMANDS_H) && (defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266)) // STD does not exist on Arduino
#define COMMANDS_H
#include "serialCommandsSystem.h"
#include "stringTools.h"
#include <vector>

void ping(CloudSerialSystem* cloudSerialSystem, std::vector<String>* argv);

void echo(CloudSerialSystem* cloudSerialSystem, std::vector<String>* argv);

void setupCommands(CloudSerialSystem* cloudSerialSystem);

#endif
