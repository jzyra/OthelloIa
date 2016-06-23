/*!
  * \file Referee.hpp
  * \brief Referee class header for manage game.
  * \author Jeremy ZYRA
  * \version 1.0
*/
#ifndef REFEREE_H
#define REFEREE_H

#include <iostream>
#include "Game.hpp"
#include "Ia.hpp"

class Referee {
	public :
		Referee(bool round);
		void play();

	private :
		bool _round;
		Game _game;
		void print_possible_moves(const vector<int> &possible_moves);
		void print_score();
};

#endif
