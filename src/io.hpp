#ifndef IO_HPP
#define IO_HPP

#include <vector>
#include <string>
#include <sstream>

#include "commands.hpp"



std::vector<std::string> split_command(const std::string& command) {
    std::stringstream stream(command);
    std::string intermediate;
    std::vector<std::string> tokens;


    while (std::getline(stream, intermediate, ' ')) {
        tokens.push_back(intermediate);
    }

    return tokens;
}



static void parse_help(std::vector<std::string> tokens) {
	if (tokens.size() == 1) {
		std::cout << "\nCommands:\n\"help\":      Provides help information for commands.\n\"newgame\":   Starts a new Klondike game.\n\"d\":         Prints current game state.\n\"quit\":      Closes game client.\n\"move\":      Move card location.\n\n";
		return;
	}
	switch (MAP_COMMANDS[tokens[1]])
	{
	case (QUIT):
	{
		std::cout << "Closes game client.\n\nquit\n\n";
		break;
	}
	case (HELP):
	{
		std::cout << "Provides help information for commands.\n\nhelp command\n\n	command - displays help information on that command.\n\n";
		break;
	}
	case (DISPLAY):
	{
		std::cout << "Prints current game state.\n\nd\n\n";
		break;
	}
	case (NEWGAME):
	{
		std::cout << "Starts a new Klondike game.\n\nnewgame\n\n";
		break;
	}
	case (MOVE):
	{
		std::cout << "Move card location.\n\nmove operation [source] [destination]\n\n";
		std::cout << "	operation - type of move to be performed\n";
		std::cout << "		 T	move the stock card to the waste pile or turning over the stock.\n\n";
		std::cout << "		pp	move a partial pile or card from one pile to another.\n";
		std::cout << "			-[source]	location and number of partial pile to move.\n					(Ex: 23, move 3 cards from the top of pile 2)\n";
		std::cout << "			-[destination]	location of pile to move to.\n\n";
		std::cout << "		sp	move a card from the stock to a pile, only destination is needed to be specified.\n";
		std::cout << "			-[destination]	location of pile to move to.\n\n";
		std::cout << "		sf	move a card from the stock to a foundation.\n\n";
		std::cout << "		pf	move a card from a pile to a foundation.\n";
		std::cout << "			-[source]	location of pile to move the card from. (Ex: 2, move a card from the top of pile 2)\n\n";
		std::cout << "		fp	move a card from a foundation to a pile.\n";
		std::cout << "			-[source]	location of foundation to move from.\n\n";
		std::cout << "			-[destination]	location of pile to move to.\n\n";
		std::cout << "		hint	have the computer play a move for you.\n\n";
		break;
	}
	case (UNRECOGNISED):
	{
		std::cout << "Unknown command\n";
		break;
	}
	}
	return;
}


void parse_move(std::vector<std::string> tokens, Gamestate* gamestate) {
	if (tokens.size() == 1) {
		std::cout << "Invalid move command size!\n";
	}
	else if (tokens.at(1) == "T") {
		try {
			if (!(gamestate -> turnStock())) {
				std::cout << "Invalid move!\n";
			}
			else {
				++gamestate->moves;
			}
		}
		catch (...) {
			std::cout << "Formatting error!\n";
		}
	}
	else if (tokens.at(1) == "pp") {
		try {
			int input_index = stoi(tokens.at(2));
			int pileFrom = (input_index / 10) - 1;
			int card_index = input_index % 10;
			int pileTo = stoi(tokens.at(3)) - 1;
			std::cout << "Moving " << card_index << " cards" << std::endl; 
			std::cout << "Moving from pile: " << pileFrom << std::endl; 
			std::cout << "Moving to pile: " << pileTo << std::endl; 


			if (!(gamestate -> pileToPile(pileFrom, pileTo, card_index))) {
				std::cout << "Invalid move!\n";
			}
			else {
				++gamestate->moves;
			}
		}
		catch (...) {
			std::cout << "Formatting error!\n";
		}
	}
	else if (tokens.at(1) == "sp") {
		try {
			int pileTo = stoi(tokens.at(2)) - 1;
			std::cout << "Moving to pile: " << pileTo << std::endl; 
			if (!(gamestate -> stockToPile(pileTo))) {
				std::cout << "Invalid move!\n";
			}
			else {
				++gamestate->moves;
			}
		}
		catch (...) {
			std::cout << "Formatting error!\n";
		}
	}
	else if (tokens.at(1) == "sf") {
		try {
			if (!(gamestate -> stockToFoundation())) {
				std::cout << "Invalid move!\n";
			}
			else {
				++gamestate->moves;
			}
		}
		catch (...) {
			std::cout << "Formatting error!\n";
		}
	}
	else if (tokens.at(1) == "pf") {
		try {
			int pile = stoi(tokens.at(2)) - 1;
			std::cout << "Moving from pile: " << pile << std::endl; 
			if (!(gamestate -> pileToFoundation(pile))) {
				std::cout << "Invalid move!\n";
			}
			else {
				++gamestate->moves;
			}
		}
		catch (...) {
			std::cout << "Formatting error!\n";
		}
	}
	else if (tokens.at(1) == "fp") {
		try {
			int foundation = stoi(tokens.at(2)) - 1;
			int pile = stoi(tokens.at(3)) - 1;
			std::cout << "Moving from foundation: " << foundation << std::endl; 
			std::cout << "Moving to pile: " << pile << std::endl; 
			if (!(gamestate -> foundationToPile(foundation, pile))) {
				std::cout << "Invalid move!\n";
			}
			else {
				++gamestate->moves;
			}
		}

		catch (...) {
			std::cout << "Formatting error!\n";
		}
	}
	/*
	else if (tokens.at(1) == "hint") {
		if (Move_hint(gamestate)) {
			++gamestate->moves;
		}

		else {
			std::cout << "No moves found.\n";
		}
	}*/
	else {
		std::cout << "Invalid Command!\n";
	}

	return;
}



#endif