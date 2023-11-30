#ifndef COMMANDS_H
#define COMMANDS_H
#include "serialCommandsSystem.h"
#include "stringTools.h"
#include <vector>

void ping(CloudSerialSystem* cloudSerialSystem, std::vector<String>* argv);

void echo(CloudSerialSystem* cloudSerialSystem, std::vector<String>* argv);

void setupCommands(CloudSerialSystem* cloudSerialSystem);

#endif
