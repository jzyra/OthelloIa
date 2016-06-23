/*!
  * \file History.cpp
  * \brief Class for represent the game with history of returned pieces by depth.
  * \author Jeremy ZYRA
  * \version 1.0
*/
#include "History.hpp"

/*!
  * \brief History Constructor.
  History class's constructor.
  * \param game : Game with othello board for init history object.
*/
History::History(const Game &game) {
  //Copy game class.
	_game = Game(game.get_size_width(), game.get_size_height());
	_game = game;
  //Init array for store depth captured by depth.
	int nb_pawns = _game.get_size_width() * _game.get_size_height();
	_pawns_captured_by_depth = new int[nb_pawns];
  //Init all depth of all pieces at -1.
	for (int i=0; i < nb_pawns; ++i) {
		_pawns_captured_by_depth[i]=-1;
	}
}

/*!
  * \brief History Destructor.
  History class's destructor.
  * \param game : Game with othello board for init history object.
*/
History::~History() {
	delete[] _pawns_captured_by_depth;
}

/*!
  * \brief Function for play and update depth by pieces.
  Function for play and update depth by pieces.
  * \param player : Player id.
  * \param cell_id : ID of cell played.
  * \param depth : depth.
*/
void History::play(int player, int cell_id, int depth) {
	Game tmp = Game(_game.get_size_width(), _game.get_size_height());
	_game.play(player, cell_id);
	for (int i=0; i < (_game.get_size_width() * _game.get_size_height()); ++i) {
		if (_game.get_cell_state(i) != tmp.get_cell_state(i)) {
			_pawns_captured_by_depth[i] = depth;
		}
	}
}

/*!
  * \brief = Operator.
  = Operator
  * \param history : History class
  * \return Return copy of this class.
*/
History &History::operator=(const History &history) {
	_game = history._game;
	int nb_pawns = _game.get_size_width() * _game.get_size_height();
	_pawns_captured_by_depth = new int[nb_pawns];
	for (int i=0; i < nb_pawns; ++i) {
		_pawns_captured_by_depth[i] = history._pawns_captured_by_depth[i];
	}
	return *this;
}

/*!
  * \brief Accessor on count_cells_by_state function in Game class.
  Accessor on count_cells_by_state function in Game class.
*/
void History::print_game() const {
	_game.print_game();
}

/*!
  * \brief Accessor on print_game function in Game class.
  Accessor on print_game function in Game class.
  * \param state : The state of the cell (HUMAN, IA, or 0)
  * \return Return the number of cell.
*/
int History::count_cells_by_state(int state) const {
	return _game.count_cells_by_state(state);
}

/*!
  * \brief Get depth for one piece.
  Get depth for one piece.
  * \param cell_id : ID of cell.
  * \return Return depth for the cell given in parameter.
*/
int History::get_depth_by_cell(int cell_id) const {
	return _pawns_captured_by_depth[cell_id];
}

/*!
  * \brief Accessor on get_cell_state function in Game class.
  Accessor on get_cell_state function in Game class.
  * \param cell_id : cell id.
  * \return State of the cell id in board.
*/
int History::get_cell_state(int cell_id) const {
	return _game.get_cell_state(cell_id);
}

/*!
  * \brief Accessor on count_possible_moves function in Game class.
  Accessor on count_possible_moves function in Game class.
  * \param player : player id.
  * \param list_moves : pointer on vector for list all possible moves.
  * \return Return number of possible moves.
*/
int History::count_possible_moves(int player, vector<int> *list_moves) const {
	return _game.count_possible_moves(player, list_moves);
}

/*!
  * \brief Accessor on get_size_width function in Game class.
  Accessor on get_size_width function in Game class.
  * \return Size in width of board.
*/
int History::get_size_width() const {
	return _game.get_size_width();
}

/*!
  * \brief Accessor on get_size_height function in Game class.
  Accessor on get_size_height function in Game class.
  * \return Size in height of board.
*/
int History::get_size_height() const {
	return _game.get_size_height();
}
