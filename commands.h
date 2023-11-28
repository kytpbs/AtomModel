#ifndef COMMANDS_H
#define COMMANDS_H
#include "serialCommandsSystem.h"
#include <vector>

void ping(CloudSerialSystem* cloudSerialSystem, std::vector<String>* argv) {
    cloudSerialSystem->print("pong");
}

void setupCommands(CloudSerialSystem* cloudSerialSystem) {
    cloudSerialSystem->addCommand("ping", ping);
}

#endif
