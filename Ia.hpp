/*!
  * \file Ia.cpp
  * \brief IA class header for Othello game.
  * \author Jeremy ZYRA
  * \version 1.0
*/
#ifndef IA_H
#define IA_H

#include <iostream>
#include <cmath>
#include <ctime>
#include <limits>
#include "Game.hpp"
#include "History.hpp"
#include "Cell_id.hpp"

#define DEPTH 6

using namespace std;

class Ia {
  public :
    Ia(const Game &game, int player);
    int play();

  private :
    Game _game;
    int _depth;
    int _player;
    int _rival;
    int get_min(const History &hist, int alpha, int beta, int depth);
    int get_max(const History &hist, int alpha, int beta, int depth);
    int evaluate(const History &hist);
    int eval_mobility(const History &hist);
    int eval_neighborhood(const History &hist, int cell_id);
    int eval_end_game(const History &hist);
    int eval_corners(const History &hist);
    void sort_moves_list(const History &hist, vector <int> &list_moves);
};

#endif
