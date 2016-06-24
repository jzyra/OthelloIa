/*!
	* \file Referee.cpp
	* \brief Referee class for manage game.
	* \author Jeremy ZYRA
	* \version 1.0
*/
#include "Referee.hpp"

/*!
	* \brief Referee Constructor.
	Referee class's constructor.
	* \param round : Bool for indicate if human begin the game..
*/
Referee::Referee(bool round) {
	_round = round;
	_game = Game(SIZE_WIDTH, SIZE_HEIGHT);
}

/*!
	* \brief Function for print possible moves.
	Function for print possible moves.
	* \param possible_moves : List of possible moves for print this.
*/
void Referee::print_possible_moves(const vector<int> &possible_moves) {
	cout << "[ ";
	for (int i=0; i < (int)possible_moves.size(); ++i) {
		cout << possible_moves[i] << " ";
	}
	cout << "]";
}

/*!
	* \brief Function for print the score.
	This function print the score of the IA and HUMAN player at the end of game.
*/
void Referee::print_score() {
	int count_human = _game.count_cells_by_state(HUMAN);
	int count_ia = _game.count_cells_by_state(IA);
	cout << endl << "Score :" << endl;
	#ifdef UNIX_COLORS
	cout << "\E[32;1m";
	#endif
	cout << "O";
	#ifdef UNIX_COLORS
	cout << "\E[m";
	#endif
	cout << " - " << count_human << endl;
	#ifdef UNIX_COLORS
	cout << "\E[31;1m";
	#endif
	cout << "@";
	#ifdef UNIX_COLORS
	cout << "\E[m";
	#endif
	cout << " - " << count_ia << endl;
}

/*!
	* \brief This function launch the game.
	This function launch the game.
*/
void Referee::play() {
	_game.print_game();
	while (!(_game.count_possible_moves(IA) == 0 && _game.count_possible_moves(HUMAN) == 0)) {
		//If round is at true, human begin.
		if (_round) {
			vector<int> list_moves_human;
			//If human can play.
			if (_game.count_possible_moves(HUMAN, &list_moves_human) > 0) {
				int cell = -1;
				while (_game.play(HUMAN, cell) == 0) {
					//Human put cell id to play.
					cout << "Enter cell number ";
					print_possible_moves(list_moves_human);
					cout << " : ";
					cin >> cell;
					cout << endl;
				}
				_game.print_game();
			} 
		} else {
			vector<int> list_moves_ia;
			//If IA can play.
			if (_game.count_possible_moves(IA, &list_moves_ia) > 0) {
				Ia ia = Ia(_game, IA);
				//Generate IA move.
				int ia_pos = ia.play();
				_game.play(IA, ia_pos);
				cout << "IA play in : " << ia_pos << endl << endl;
				_game.print_game();
			}
		}
		_round = !_round;
	}
	//Print score at the end of game.
	print_score();
}
