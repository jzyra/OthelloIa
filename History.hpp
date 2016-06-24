/*!
	* \file History.hpp
	* \brief Class header for represent the game with history of returned pieces by depth.
	* \author Jeremy ZYRA
	* \version 1.0
*/
#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>
#include "Game.hpp"

using namespace std;

class History {
	public :
		History(const Game &game);
		~History();
		void play(int player, int cell_id, int depth);
		int get_depth_by_cell(int cell_id) const;
		int get_cell_state(int cell_id) const;
		int get_size_width() const;
		int get_size_height() const;
		int count_cells_by_state(int state) const;
		int count_possible_moves(int player, vector<int> *list_moves=NULL) const;
		void print_game() const;
		History &operator=(const History &history);

	private :
		Game _game;
		int *_pawns_captured_by_depth;
};

#endif
