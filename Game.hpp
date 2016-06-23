/*!
  * \file Game.hpp
  * \brief Class header for represent Othello game.
  * \author Jeremy ZYRA
  * \version 1.0
*/
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
#include "Cell_id.hpp"

#define SIZE_WIDTH 8
#define SIZE_HEIGHT 8

using namespace std;

class Game {
	public :
		Game();
		Game(int size_width, int size_height);
		~Game();
		void print_game() const;
		int play(int player, int cell_id);
		int get_cell_state(int cell_id) const;
		int get_size_width() const;
		int get_size_height() const;
		int count_cells_by_state(int state) const;
		int count_possible_moves(int player, vector<int> *list_moves=NULL) const;
		void init_matrice();
		void set_init_cells();
		int get_rival(int player) const;
		Game &operator=(const Game &game);

	private :
		unsigned char **_matrice;
		int _size_width;
		int _size_height;
		void print_line() const;
		int return_pawns_one_axe(int player, int cell_id, int inc_x, int inc_y, bool sim=false) const;
		int return_pawns(int player, int cell_id, bool sim=false) const;
};

#endif
