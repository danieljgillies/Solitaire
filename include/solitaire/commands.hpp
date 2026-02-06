#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <map>
#include <string>


enum COMMANDS {
    UNRECOGNISED, NEWGAME, DISPLAY, HELP, QUIT, MOVE, SEARCH
};

static std::map<std::string, COMMANDS> MAP_COMMANDS =
{
    { "newgame", NEWGAME }, { "d", DISPLAY }, { "help", HELP }, { "quit", QUIT }, { "move", MOVE }, { "search", SEARCH }
};

#endif