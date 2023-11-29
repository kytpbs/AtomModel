#include <vector>

void splitString(String string, std::vector<String>* argv) {
    int spaceIndex = string.indexOf(" ");
    
    if (spaceIndex == -1) {
        return; // If there are no spaces, there are no arguments so we can return
    }

    String args = string.substring(spaceIndex + 1); // Removing the command name from the string
    int lastSpaceIndex = 0;
    
    while (args.indexOf(" ") != -1) {
        spaceIndex = args.indexOf(" ");
        argv->push_back(args.substring(spaceIndex));
        args = args.substring(spaceIndex + 1);
        lastSpaceIndex = spaceIndex + 1;
    }
    argv->push_back(args);
}

/**
 * Splits a string into a vector of strings, each string being an argument.
 * @warning Will remove the command name from the string!
 * @param string The string to split.
 * @return A vector of strings, each string being an argument.
 * may return an empty vector if there are no arguments.
*/
std::vector<String> splitString(String string) {
    std::vector<String> argv = std::vector<String>();
    splitString(string, &argv);
    return argv;
}

String joinString(std::vector<String>* argv, String separator) {
    String string = "";
    for (int i = 0; i < argv->size(); i++) {
        string += argv->at(i);
        if (i != argv->size() - 1) {
            string += separator;
        }
    }
    return string;
}

String joinString(std::vector<String>* argv) {
    joinString(argv, " ");
}


