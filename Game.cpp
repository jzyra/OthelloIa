/*!
	* \file Game.cpp
	* \brief Class for represent Othello game.
	* \author Jeremy ZYRA
	* \version 1.0
*/
#include "Game.hpp"

/*!
	* \brief Game Constructor.
	Game class's constructor.
*/
Game::Game() {
	//Init width and height of board (8x8).
	_size_width = SIZE_WIDTH;
	_size_height = SIZE_HEIGHT;
	//Set initial game and put the first four pieces.
	init_matrice();
	set_init_cells();
}

/*!
	* \brief Game Constructor.
	Game class's constructor.
	* \param width : Width size of the board
	* \param height : Height size of the board
*/
Game::Game(int size_width, int size_height) {
	//Check size of the board, for print board, cell id must be smaller than 1000.
	assert(size_width*size_height < 1000);
	//Init width and height of board.
	_size_width = size_width;
	_size_height = size_height;
	//Set initial game and put the first four pieces.
	init_matrice();
	set_init_cells();
}

/*!
	* \brief Game Destructor.
	Game class's destructor.
*/
Game::~Game() {
	//Free matrice allocation.
	for (int x=0; x < _size_width; ++x) {
		delete[] _matrice[x];
	}
	delete[] _matrice;
}

/*!
	* \brief Count cells by state.
	Count cells by state (Can count player's pieces)
	* \param state : The state of the cell (HUMAN, IA, or 0)
	* \return Return the number of cell.
*/
int Game::count_cells_by_state(int state) const {
	int count = 0;
	for (int i=0; i < _size_width*_size_height; ++i) {
		int x, y;
		y = (x = CELL_COORD(i, _size_width));
		if (_matrice[x][y] == state) {
			++count;
		}
	}
	return count;
}

/*!
	* \brief Init board game.
	Allocate pointer for store board game.
*/
void Game::init_matrice() {
	_matrice = new unsigned char*[_size_width];
	for (int x=0; x < _size_width; ++x) {
		_matrice[x] = new unsigned char[_size_height];
		//Put 0 in all cells.
		memset(_matrice[x], 0x00, sizeof(unsigned char)*_size_height);
	}
}

/*!
	* \brief = Operator.
	= Operator
	* \param game : Game class
	* \return Return copy of this class.
*/
Game &Game::operator=(const Game &game) {
	_size_width = game._size_width;
	_size_height = game._size_height;
	_matrice = new unsigned char*[_size_width];
	for (int x=0; x < _size_width; ++x) {
		_matrice[x] = new unsigned char[_size_height];
		memset(_matrice[x], 0x00, sizeof(unsigned char)*_size_height);
	}
	for (int x=0; x < _size_width; ++x) {
		for (int y=0; y < _size_height; ++y) {
			_matrice[x][y] = game._matrice[x][y];
		}
	}
	return *this;
}

/*!
	* \brief List all possible moves for one player
	Count and return all possible moves for one player given in parameter.
	* \param player : player id.
	* \param list_moves : pointer on vector for list all possible moves.
	* \return Return number of possible moves.
*/
int Game::count_possible_moves(int player, vector<int> *list_moves) const {
	int res = 0;
	//Browse all cell in board.
	for (int x=0; x < _size_width; ++x) {
		for (int y=0; y < _size_height; ++y) {
			if (_matrice[x][y] == 0) {
				//Try to return current piece.
				int count = return_pawns(player, CELL_ID(x, y, _size_width), true);
				//If more than 1 piece can be returned, it's one possible move.
				if (count > 0) {
					++res;
					if (list_moves != NULL) {
						list_moves->push_back(CELL_ID(x, y, _size_width));
					}
				}
			}
		}
	}
	return res;
}

/*!
	* \brief Set init pieces for begin game.
	Set the four first piece in board.
*/
void Game::set_init_cells() {
	const int x = _size_width >> 1;
	const int y = _size_height >> 1;
	//Set this piece in the middle of board.
	_matrice[x][y] = HUMAN;
	_matrice[x-1][y-1] = HUMAN;
	_matrice[x][y-1] = IA;
	_matrice[x-1][y] = IA;
}

/*!
	* \brief Print line.
	This function is used in print_game for draw horizontal line in terminal.
*/
void Game::print_line() const {
	for (int i=0; i < _size_width; ++i) {
		cout << "+---";
	}
	cout << "+" << endl;
}

/*!
	* \brief Print game board.
	This function print the game.
*/
void Game::print_game() const {
	print_line();
	//Browse all cell in board.
	for (int y=0; y < _size_height; ++y) {
		for (int x=0; x < _size_width; ++x) {
			cout << "|";
			switch (_matrice[x][y]) {
				case IA :
					#ifdef UNIX_COLORS
					cout << "\E[31;1m";
					#endif
					cout << " @ ";
					#ifdef UNIX_COLORS
					cout << "\E[m";
					#endif
					break;
				case HUMAN :
					#ifdef UNIX_COLORS
					cout << "\E[32;1m";
					#endif
					cout << " O ";
					#ifdef UNIX_COLORS
					cout << "\E[m";
					#endif
					break;
				default :
					cout << setw(3) << CELL_ID(x, y, _size_width);
					break;
			}
		}
		cout << "|" << endl;
		print_line();
	}
}

/*!
	* \brief Return the rival of player given in parameter.
	Return the rival id of player given in parameter.
	* \param player : player id.
	* \return Player id of rival given in parameter.
*/
int Game::get_rival(int player) const {
	if (player == HUMAN) {
		return IA;
	} else {
		return HUMAN;
	}
}

/*!
	* \brief This function is an accessor on matrice game.
	This function return the state of cell given in parameter.
	* \param cell_id : cell id.
	* \return State of the cell id in board.
*/
int Game::get_cell_state(int cell_id) const {
	int x, y;
	y = (x = CELL_COORD(cell_id, _size_width));
	return _matrice[x][y];
}

/*!
	* \brief Accessor on width of board.
	This function is used for get size in width of the board.
	* \return Size in width of board.
*/
int Game::get_size_width() const {
	return _size_width;
}

/*!
	* \brief Accessor on height of board.
	This function is used for get size in height of the board.
	* \return Size in height of board.
*/
int Game::get_size_height() const {
	return _size_height;
}

/*!
	* \brief Update the matrice when gamer play.
	Update the matrice when gamer play.
	* \param player : player id.
	* \param cell_id : cell id played.
	* \return The number of pieces returned by this position.
*/
int Game::play(int player, int cell_id) {
	int x, y;
	//Check if cell id is correct.
	if (cell_id < 0 || cell_id > _size_width*_size_height) {
		return 0;
	}
	//Get x and y with cell id.
	y = (x = CELL_COORD(cell_id, _size_width));
	//Play this position.
	int count = return_pawns(player, cell_id);
	//If at least a piece is returned.
	if (count > 0) {
		//Update game.
		_matrice[x][y] = player;
	}
	return count;
}

/*!
	* \brief Return pieces on board on one axe.
	Return pieces on board for one move for one player on one axe.
	* \param player : player id.
	* \param cell_id : cell id played.
	* \param inc_x : value for increment on x-axis.
	* \param inc_y : value for increment on y-axis.
	* \param sim : simulation mode for return or not pieces on board.
	* \return Number of pieces returned.
*/
int Game::return_pawns_one_axe(int player, int cell_id, int inc_x, int inc_y, bool sim) const {
	int id_rival = get_rival(player);
	int count = 0;
	int x, y;
	y = (x = CELL_COORD(cell_id, _size_width));
	if (inc_x == 0 && inc_y == 0) {
		return count;
	} 
	else {
		int i = x;
		int j = y;
		if (i+inc_x < _size_width && j+inc_y < _size_height && i+inc_x > -1 && j+inc_y > -1) {
			while (_matrice[i+inc_x][j+inc_y] == id_rival && i > -1 && j > -1 && i < _size_width && j < _size_height) {
				++count;
				i += inc_x;
				j += inc_y;
				if (i+inc_x > _size_width-1 || j+inc_y > _size_height-1 || i+inc_x < 0 || j+inc_y < 0) {
					return 0;
				}
			}
			if (_matrice[i+inc_x][j+inc_y] != player) {
				count = 0;
			}
			if (sim == false) {
				//Return pieces in matrice.
				for (int k=0; k < count; ++k) {
					_matrice[i+(inc_x*k*-1)][j+(inc_y*k*-1)] = player;
				}
			}
		}
	} 
	return count;
}	

/*!
	* \brief Return pieces on board on all axes.
	Return pieces on board for one move for one player on all axes.
	* \param player : player id.
	* \param cell_id : cell id played.
	* \param sim : simulation mode for return or not pieces on board.
	* \return Number of pieces returned.
*/
int Game::return_pawns(int player, int cell_id, bool sim) const {
	int count = 0;
	count += return_pawns_one_axe(player, cell_id, 0, -1, sim);
	count += return_pawns_one_axe(player, cell_id, 0, 1, sim);
	count += return_pawns_one_axe(player, cell_id, 1, 0, sim);
	count += return_pawns_one_axe(player, cell_id, -1, 0, sim);
	count += return_pawns_one_axe(player, cell_id, 1, 1, sim);
	count += return_pawns_one_axe(player, cell_id, -1, -1, sim);
	count += return_pawns_one_axe(player, cell_id, 1, -1, sim);
	count += return_pawns_one_axe(player, cell_id, -1, 1, sim);
	return count;
}
