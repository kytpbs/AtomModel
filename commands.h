#ifndef COMMANDS_H
#define COMMANDS_H
#include "serialCommandsSystem.h"

void ping(CloudSerialSystem* cloudSerialSystem) {
    cloudSerialSystem->print("pong");
}

void setupCommands(CloudSerialSystem* cloudSerialSystem) {
    cloudSerialSystem->addCommand("ping", ping);
}

#endif
