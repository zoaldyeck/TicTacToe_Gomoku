// lab3.cpp : Defines the entry point for the console application.
//
//wustl key: jinjinqin  chengzhen t.yin
//
//2016.3.30

#include "stdafx.h"
#include "GameBase.h"
#include "status.h"
#include "TicTacToe.h"
#include <iostream>
using namespace std;


int main(int argc, char* argv[])
{
	//check argc and argv first, may throw out null_ptr(wrong second command)
	//may throw out invalid_argc_number(argc!=2)
	try{
		GameBase * p = GameBase::argCheck(argc, argv);
		if (p == nullptr)
			throw null_ptr;
		else
			//if p is not null, play
			p->play();
		//safely delete p after play()
		delete p;
	}
	catch (indicator n){
		//if argc!=2, call usage_message to give a correct format
		if (n == invalid_argc_number){
			return usage_message(argv[program_index]);
		}
		//play() or prompt() throw out quit_game, catch it here and return it.
		if (n == quit_game){
			cout << "Warning: You quit the game!" << endl;
			return quit_game;
		}
        //if the second command is wrong, remind the correct format
		if (n == null_ptr){
			cout << "Wrong command, enter TicTacToe or Gomoku next to the program name" << endl;
			return null_ptr;
		}
	}
	//other error
	catch (...){
		cerr << "Unknow error..." << endl;
	}
	return success_game;
}

