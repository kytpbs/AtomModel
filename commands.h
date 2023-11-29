#ifndef COMMANDS_H
#define COMMANDS_H
#include "serialCommandsSystem.h"
#include "stringTools.h"
#include <vector>

void ping(CloudSerialSystem* cloudSerialSystem, std::vector<String>* argv) {
    cloudSerialSystem->print("pong");
}

void echo(CloudSerialSystem* cloudSerialSystem, std::vector<String>* argv) {
    if (argv->size() == 0) {
        cloudSerialSystem->print("No arguments provided!");
        return;
    }
    cloudSerialSystem->print(joinString(argv));
}

void setupCommands(CloudSerialSystem* cloudSerialSystem) {
    cloudSerialSystem->addCommand("ping", ping);
    cloudSerialSystem->addCommand("echo", echo);
}

#endif
