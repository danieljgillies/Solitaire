#include <iostream>
#include <random>
#include <ctime>



#include "types.hpp"
#include "deck.hpp"
#include "gamestate.hpp"
#include "io.hpp"
#include "commands.hpp"


int main() {
    std::srand(unsigned(std::time(NULL)));

    std::cout << "Welcome to Solitaire Klondike." << std::endl;
    std::cout << "Type \"help\" for options." << std::endl;

    //std::cout << suitNames[0] << suitNames[1] << suitNames[2] << suitNames[3] << suitNames[4] << std::endl; 

    Gamestate gamestate;
    bool gamestarted = false;
    bool game = true;
    while (game) {
        std::string input;


        if (!getline(std::cin, input)){
            //continue the loop...
            break;
        }

        if (!input.length()) {
            continue;
        }

        std::vector<std::string> tokens = split_command(input);

        switch (MAP_COMMANDS[tokens[0]]) {
            case (QUIT) :
                {
                    return 0;
                }
            case (HELP) :
                {
                    parse_help(tokens);
                    break;
                }
            case (DISPLAY) :
                {
                    if (gamestarted) {
                        gamestate.printGameState();
                    } else {
                        std::cout << "No game available." << std::endl;
                    }
                    break;
                }
            case (NEWGAME) :
                {
                    gamestate.startGame();
                    gamestarted = true;
                    break;
                }
            case (MOVE) :
                {
                    if (gamestarted) {
                        parse_move(tokens, &gamestate);
                    } else {
                        std::cout << "No game available." << std::endl;
                    }
                    break;
                }
            case (SEARCH) :
                {
                    if (gamestarted) {
                        //parse_search(tokens, &gamestate)
                    } else {
                        std::cout << "No game available." << std::endl;
                    }
                    break;
                }
            case (UNRECOGNISED) :
            {
                std::cout << "Unrecognised Command!" << std::endl;
            }
            default :
            {
                std::cout << "Unrecognised Command!" << std::endl;
            }

        }
    }


    //DEBUG
    // std::cout << STOCK_SIZE << std::endl;

    // Deck deck;
    // deck.fill();
    // deck.print();
    // deck.shuffle();
    // deck.print();

    /*
    Gamestate gamestate;

    gamestate.startGame();

    gamestate.stock.printAllStock();

    while (1) {
        std::getchar();
        gamestate.printGameState();
        gamestate.stockToFoundation();
        gamestate.printGameState();
        gamestate.turnStock();

    }
    */

    return 0;

}