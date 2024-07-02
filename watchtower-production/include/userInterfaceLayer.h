/*
-----------------------------------

Header file for handling user input / output

Contributors: Arturo, Arkadiusz, Kyril, Hans
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

#ifndef USER_INTERFACE_LAYER_H
#define USER_INTERFACE_LAYER_H

#include <string>

// Class for handling user input / output from the terminal
class TerminalInterface {
public:
    static std::string getInput(const std::string& prompt);
};

#endif // USER_INTERFACE_LAYER_H