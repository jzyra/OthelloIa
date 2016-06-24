/*!
	* \file main.cpp
	* \brief Program's entry point.
	* \author Jeremy ZYRA
*/
#include <iostream>
#include "Referee.hpp"
#include "Options.hpp"

/*!
	* \brief Program's entry point.
*/
int main(const int argc, const char* argv[]) {
	bool round;
	//Parse options, print usage if necessary and set round player.
	if (get_options(argc, argv, round)) {
		print_help(argv[0]);
	} else {
		//Launch game.
		Referee game = Referee(round);
		game.play();
	}
	return EXIT_SUCCESS;
}
