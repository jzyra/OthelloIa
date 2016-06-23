/*!
  * \file Ia.cpp
  * \brief IA class for Othello game.
  * \author Jeremy ZYRA
  * \version 1.0
*/
#include "Ia.hpp"

/*!
  * \brief Ia Constructor.
  Ia class's constructor.
  * \param game : Game with othello board.
  * \param player : Player id associed at IA.
*/
Ia::Ia(const Game &game, int player) {
  //Create new game object for modified this.
  _game = Game(game.get_size_width(), game.get_size_height());
  _game = game;
  //Init Ia depth for IA.
  _depth = DEPTH;
  //Set IA id and rival id.
  _player = player;
  _rival = _game.get_rival(player);
}

/*!
  * \brief Generate IA move.
  This function is called for generate IA move.
  * \return Return the best cell id calculated by IA.
*/
int Ia::play() {
  //Create history by game class.
  History hist = History(_game);
  History tmp = History(_game);
  //Get all possible moves for IA and sort this list.
  vector<int> list_possible_moves;
  int count_moves = _game.count_possible_moves(_player, &list_possible_moves);
  sort_moves_list(hist, list_possible_moves);
  int best_move = list_possible_moves.at(0);
  int max_val = 0;
  int alpha = -1000000;
  int beta = 1000000;
  tmp.play(_player, best_move, _depth);
  max_val = get_min(tmp, alpha, beta, _depth-1);
  tmp = hist;
  //For each possible moves.
  for (int i=1; i < count_moves; ++i) {
    //Simulate to play this position.
    tmp.play(_player, list_possible_moves[i], _depth);
    //Eval this position.
    int tmp_val = get_min(tmp, alpha, beta, _depth-1);
    tmp = hist;
    if (tmp_val > max_val) {
      max_val = tmp_val;
      best_move = list_possible_moves.at(i);
    }
  }
  return best_move;
}

/*!
  * \brief Sort possible moves list.
  Sort possible moves list for put corners moves at the beginning.
  * \param hist : History with game object.
  * \param list_moves : List of possible moves to sort.
*/
void Ia::sort_moves_list(const History &hist, vector <int> &list_moves) {
  //Get cell id for all corners.
  int corner1 = 0;
  int corner2 = hist.get_size_width()-1;
  int corner3 = hist.get_size_width()*(hist.get_size_height()-1);
  int corner4 = hist.get_size_width()*hist.get_size_height()-1;
  int idx_swap=0;
  //For each possible moves.
  for (int i=0; i < (int)list_moves.size(); ++i) {
    if (list_moves.at(i) == corner1
    || list_moves.at(i) == corner2
    || list_moves.at(i) == corner3
    || list_moves.at(i) == corner4) {
      if (i != idx_swap) {
        //Swap if move is a corner.
        list_moves[idx_swap] = list_moves[idx_swap] ^ list_moves[i];
        list_moves[i] = list_moves[idx_swap] ^ list_moves[i];
        list_moves[idx_swap] = list_moves[idx_swap] ^ list_moves[i];
      }
      ++idx_swap;
    }
  }
}

/*!
  * \brief Function for get min game value in minimax algorithm.
  Function for get min game value in minimax algorithm. (Represent human node in game three)
  * \param hist : History with game object.
  * \param alpha : Alpha value in alpha/beta pruning.
  * \param beta :  Beta value in alpha/beta pruning.
  * \param depth : Depth value for stop algorithm.
  * \return game value of the min node.
*/
int Ia::get_min(const History &hist, int alpha, int beta, int depth) { 
  History tmp = History(_game);
  tmp = hist;
  vector<int> list_possible_moves;
  //Get possible moves list of human and IA player.
  int count_moves = hist.count_possible_moves(_rival, &list_possible_moves);
  int count_moves_ia = hist.count_possible_moves(_player);
  sort_moves_list(hist, list_possible_moves);
  //If is end game.
  if (depth == 0 || (count_moves == 0 && count_moves_ia == 0)) {
    int ret = evaluate(hist);
    return ret;
  //If human can't play.
  } else if (count_moves == 0) {
    return get_max(tmp, alpha, beta, depth-1);
  }
  //For each human possible moves.
  for (int i=0; i < count_moves; ++i) {
    tmp.play(_rival, list_possible_moves.at(i), depth);
    int tmp_val = get_max(tmp, alpha, beta, depth-1);
    tmp = hist;
    beta = (beta > tmp_val) ? tmp_val : beta;
    if (beta <= alpha)
      return beta;
  }
  return beta;
}

/*!
  * \brief Function for get max game value in minimax algorithm.
  Function for get max game value in minimax algorithm. (Represent IA node in game three)
  * \param hist : History with game object.
  * \param alpha : Alpha value in alpha/beta pruning.
  * \param beta :  Beta value in alpha/beta pruning.
  * \param depth : Depth value for stop algorithm.
  * \return game value of the max node.
*/
int Ia::get_max(const History &hist, int alpha, int beta, int depth) {
  History tmp = History(_game);
  tmp = hist;
  vector<int> list_possible_moves;
  //Get possible moves list of human and IA player.
  int count_moves = hist.count_possible_moves(_player, &list_possible_moves);
  int count_moves_human = hist.count_possible_moves(_rival);
  sort_moves_list(hist, list_possible_moves);
  //If is end game.
  if (depth == 0 || (count_moves == 0 && count_moves_human == 0)) {
    return evaluate(hist);
  //If IA can't play.
  } else if (count_moves == 0) {
    return get_min(tmp, alpha, beta, depth-1);
  }
  //For each IA possible moves.
  for (int i=0; i < count_moves; ++i) {
    tmp.play(_player, list_possible_moves.at(i), depth);
    int tmp_val = get_min(tmp, alpha, beta, depth-1);
    tmp = hist;
    alpha = (alpha > tmp_val) ? alpha : tmp_val;
    if(beta <= alpha)
      return alpha;
  }
  return alpha;
}

/*!
  * \brief Function for evaluate corner's neighborhood.
  Function for evaluate corner's neighborhood.
  * \param hist : History with game object.
  * \param cell_id : Cell id of the corner.
  * \return game value.
*/
int Ia::eval_neighborhood(const History &hist, int cell_id) {
  int x, y;
  y = (x = CELL_COORD(cell_id, hist.get_size_width()));
  int middle_x, middle_y;
  middle_x = hist.get_size_width() >> 1;
  middle_y = hist.get_size_height() >> 1;
  int inc_x, inc_y;
  inc_x = (x > middle_x) ? -1 : 1;
  inc_y = (y > middle_y) ? -1 : 1;
  int count = 0;
  if (hist.get_cell_state(CELL_ID(x+inc_x, y+inc_y, hist.get_size_width())) == _rival) {
    count += 2500 * hist.get_depth_by_cell(CELL_ID(x+inc_x, y+inc_y, hist.get_size_width()));
  } else if (hist.get_cell_state(CELL_ID(x+inc_x, y+inc_y, hist.get_size_width())) == _player) {
    count -= 2500 * hist.get_depth_by_cell(CELL_ID(x+inc_x, y+inc_y, hist.get_size_width()));
  }
  if (hist.get_cell_state(CELL_ID(x, y+inc_y, hist.get_size_width())) == _rival) {
    count += 1000 * hist.get_depth_by_cell(CELL_ID(x, y+inc_y, hist.get_size_width()));
  } else if (hist.get_cell_state(CELL_ID(x, y+inc_y, hist.get_size_width())) == _player) {
    count -= 1000 * hist.get_depth_by_cell(CELL_ID(x, y+inc_y, hist.get_size_width()));
  }
  if (hist.get_cell_state(CELL_ID(x+inc_x, y, hist.get_size_width())) == _rival) {
    count += 1000 * hist.get_depth_by_cell(CELL_ID(x+inc_x, y, hist.get_size_width()));
  } else if (hist.get_cell_state(CELL_ID(x+inc_x, y, hist.get_size_width())) == _player) {
    count -= 1000 * hist.get_depth_by_cell(CELL_ID(x+inc_x, y, hist.get_size_width()));
  }
  return count;
}

/*!
  * \brief Function for evaluate the mobility.
  Function for evaluate the mobility.
  * \param hist : History with game object.
  * \return game value.
*/
int Ia::eval_mobility(const History &hist) {
  int res = hist.count_possible_moves(_player) - (hist.count_possible_moves(_rival)*2);
  return res;
}

/*!
  * \brief Function for evaluate corner.
  Function for evaluate corner. (This function call eval_neighborhood)
  * \param hist : History with game object.
  * \return game value.
*/
int Ia::eval_corners(const History &hist) {
  int count = 0;
  int size_width = hist.get_size_width();
  int size_height = hist.get_size_height();
  if (hist.get_cell_state(0) == _player) {
    count += 7000 * hist.get_depth_by_cell(0);
  } else if (hist.get_cell_state(0) == _rival) {
    count -= 7000 * hist.get_depth_by_cell(0);
  } else {
    count += eval_neighborhood(hist, 0);
  }
  if (hist.get_cell_state(size_width-1) == _player) {
    count += 7000 * hist.get_depth_by_cell(size_width-1);
  } else if (hist.get_cell_state(size_width-1) == _rival) {
    count -= 7000 * hist.get_depth_by_cell(size_width-1);
  } else {
    count += eval_neighborhood(hist, size_width-1);
  }
  if (hist.get_cell_state(size_width*(size_height-1)) == _player) {
    count += 7000 * hist.get_depth_by_cell(size_width*(size_height-1));
  } else if (hist.get_cell_state(size_width*(size_height-1)) == _rival) {
    count -= 7000 * hist.get_depth_by_cell(size_width*(size_height-1));
  } else {
    count += eval_neighborhood(hist, size_width*(size_height-1));
  }
  if (hist.get_cell_state(size_width*size_height-1) == _player) {
    count += 7000 * hist.get_depth_by_cell(size_width*size_height-1);
  } else if (hist.get_cell_state(size_width*size_height-1) == _rival) {
    count -= 7000 * hist.get_depth_by_cell(size_width*size_height-1);
  } else {
    count += eval_neighborhood(hist, size_width*size_height-1);
  }
  return count;
}

/*!
  * \brief Function for evaluate the end game.
  Function for evaluate the end game. (return game value only if the two players can't played)
  * \param hist : History with game object.
  * \return game value.
*/
int Ia::eval_end_game(const History &hist) {
  int res = 0;
  if (hist.count_possible_moves(_player) == 0 && hist.count_possible_moves(_rival) == 0) {
    if (hist.count_cells_by_state(_player) > hist.count_cells_by_state(_rival)) {
      res = 1000000 * hist.count_cells_by_state(_player);
    } else if (hist.count_cells_by_state(_player) < hist.count_cells_by_state(_rival)) {
      res = 1000000 * hist.count_cells_by_state(_rival) * -1;
    }
  }
  return res;
}

/*!
  * \brief Function for evaluate node.
  Function for evaluate node. (return the sum of all eval function)
  * \param hist : History with game object.
  * \return game value.
*/
int Ia::evaluate(const History &hist) {
  return eval_corners(hist)+eval_mobility(hist)+eval_end_game(hist);
}
