//GameBase.cpp -- GameBase class sourse file
//
//wustl key: jinjinqin  chengzhen t.yin
//
//Define gamebase class functions
//
//2016.3.29

#include "stdafx.h"
#include "status.h"
#include "GameBase.h"
#include "TicTacToe.h"
#include "GoMoKu.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

//game_piece structure: store X or O for TicTacToe game, and W or B for Gomoku game
game_piece::game_piece(){
	letter = None;
	display = " ";
}
//set new letter 
game_piece::game_piece(piece_letter letter, string display, int position)
: letter(letter), display(display){}

//find out the longest string and set longest_length as the longest 
void GameBase::setLongestLength(){
	for (game_piece piece : gameboard){
		if (piece.display.length() > longest_length){
			longest_length = piece.display.length();
		}
	}
}
//prompt call validcommand to see if the command is valid
bool GameBase::validcommand(string & command, gametype gamename){
	bool judge = false;
	//quit is valid
	if (command == "quit")
		return true;
	//for TicTacToe game, find comma first and extract x and y, then check if x and y are in the right range:[1,3]
	if (gamename == TTT){
		istringstream istr;
		if (command.length() != 3)
			return judge;
		for (int i = 0; i < command.length(); ++i){
			if (command[i] == ','){
				command[i] = ' ';
				istr.str(command);
				int x, y;
				if (istr >> x){
					if (istr >> y){
						if (x >= TTT_Lower_Bound && x <= TTT_Upper_Bound && y >= TTT_Lower_Bound && y <= TTT_Upper_Bound)
							judge = true;
					}
				}
			}
		}
	}
	else{
		istringstream istr;
		//for Gomoku game, find comma first, and extract x and y, then check if x and y are in the right range [1,9]
		for (int i = 0; i < command.length(); ++i){
			if (command.length()<3 || command.length()>5)
				return judge;

			if (command[i] == ','){
				command[i] = ' ';
				istr.str(command);
				int x, y;
				if (istr >> x && istr >> y)
				if (x >= GMK_Lower_Bound && x <= GMK_Upper_Bound && y >= GMK_Lower_Bound && y <= GMK_Upper_Bound)
					judge = true;
			}
		}
	}
	return judge;
}

//prompt the user to enter command
int GameBase::prompt(unsigned & x, unsigned & y){
	//prompt the user to enter quit(throw an exception) or a string of cordinates
	string command;
	bool comma = false;
	cout << "Enter the cordinate: <x,y> or <quit>" << endl;
	//if the command is not valid, repeat to remind the user to enter new command.
	while (!(cin >> command) || !validcommand(command, game_name)){
		cin.clear();                   //reset input 
		while (cin.get() != '\n')
			continue;                  //get rid of bad input
		cout << "Enter the cordinate: <x,y> or <quit>" << endl;	
	}
	//if user enter quit, throw quit_game, catch it in play(), and throw quit_game in play(), catch it in main 
	//then cout a remind message to indicate the user quit the game
	if (command == "quit"){
		throw quit_game;
	}
	else{
		//extract x and y, return differnt status to indicate success or failure.
			istringstream istr;
			istr.str(command);
			if (istr >> x){
				if (istr >> y)
					return success_extract_x_y;
				else
					return extract_y_failure;
			}
			else
				return extract_x_failure;
		}
}

//game object call play()
int GameBase::play(){
	try{
		
		while (true){

			turn();
			//done()=true means someone win the game
			if (done()){
				//TicTacToe game, export X or O win the game
				if (game_name == TTT){
					if (winner == 'X')
						cout << "Player X win the game!\n";
					else
						cout << "Player O win the game!\n";
				}
				if (game_name == GMK){
					//Gomoku game, export B or W win the game
					if (winner == 'B')
						cout << "Player B win the game!\n";
					else
						cout << "Player W win the game!\n";

				}
				return success_game;
			}
			//draw game, indicate how many turns were played, and it's a draw.
			if (draw()){
				cout << turns << " turns were played, it's a draw\n";
				return draw_game;
			}
		}
	}
	//catch quit_game thrown out in prompt(), cout a remind message, and throw out quit_game again
	catch (indicator n){
		if (n == quit_game){
			cout << "The user quits the game\n " << turns << " turns were played.\n";
			throw quit_game;
		}
	}
}
//a static method, pass argc and argv 
GameBase * GameBase::argCheck(int argNum, char* argName[]){
	//check if argc ==2, throw invalid_argc_number and catch it in main
	if (argNum != valid_argc)
		throw invalid_argc_number;
	else{
		//if argc==2, check if the second command is right: TicTacToe or Gomoku
		if (strcmp(argName[game_index], "TicTacToe") == 0){
			//instantiate a new TicTacToe and return the address of the pointer
			TicTacToe * address = new TicTacToe();
			return address;
		}
		else if (strcmp(argName[game_index], "Gomoku") == 0){
			//instantiate a new Gomoku and return the address of the pointer
			GoMoKu * address = new GoMoKu();
			return address;
		}
		else{
			//if not, return an empty pointer
			GameBase * nptr = nullptr;
			return nptr;
		}
	}
}

//main call this function if it catch a invalid_argc_number in argCheck
//provide a remind message of the right format
int usage_message(char * name)
{
	cout << "Usage: " << name << " TicTacToe or " << name << " Gomoku"<< endl;
	return invalid_argc_number;
}

