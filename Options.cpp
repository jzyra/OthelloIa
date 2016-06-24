/*!
	* \file Options.cpp
	* \brief This file contain functions for options and usage program.
	* \author Jeremy ZYRA
	* \version 1.0
*/
#include "Options.hpp"

/*!
	* \brief Function for parse options.
	Function for parse and get options.
	* \param argc : argc param of main function.
	* \param argv : argv pointer param of main function.
	* \param round : pointer for indicate if human begin game.
	* \return Return true or false if user want display help.
*/
bool get_options(const int argc, const char* argv[], bool &round) {
	int idx_round_opt = -1;
	round = true;
	for (int i=1; i < argc; ++i) {
		if (!strcmp("-r", argv[i]) || !strcmp("--round", argv[i])) {
			idx_round_opt = i;
		}
		if (!strcmp("-h", argv[i]) || !strcmp("--help", argv[i])) {
			return true;
		}
	}
	if (idx_round_opt < argc-1) {
		int val_round = atoi(argv[idx_round_opt+1]);
		if (val_round > 0 && val_round < 3) {
			switch (val_round) {
				case 1 : 
					round=true;
					break;
				case 2 : 
					round=false;
					break;
			}
		}
	}
	return false;
}

/*!
	* \brief Function for print usage.
	Function for print usage.
	* \param name : name of program.
*/
void print_help(const char *name) {
	cout << "NAME" << endl;
	cout << "\t" << name << " - IA for play to othello game." << endl << endl;
	cout << "SYNOPSIS" << endl;
	cout << "\t" << name << " [OPTION]" << endl << endl;
	cout << "DESCRIPTION" << endl;
	cout << "\tThis is an artificial intelligence for play to othello game." << endl << endl;
	cout << "\t-r, --round NUMBER" << endl;
	cout << "\tProcise who begin the game. Put 1 for human, or 2 for IA." << endl << endl;
	cout << "\t-h, --help - Display this help and exit." << endl << endl;
	cout << "AUTHOR" << endl;
	cout << "\tJeremy ZYRA" << endl;
}
