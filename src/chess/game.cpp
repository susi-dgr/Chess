#include <ctime>
#include <cstdlib>
#include <locale>
#include "game.hpp"

game::game() {
	cout << "      _  \n";
	cout << "     | | \n";
	cout << "  ___| |__   ___  ___ ___  \n";
	cout << " / __|  _ \\ / _ \\/ __/ __| \n";
	cout << "| (__| | | |  __/\__ \\__ \\ \n";
	cout << " \\___|_| |_|\\___||___/___/ \n\n";
	cout << "Choose game mode: \n";
	cout << "(1) Player vs Player \n";
	cout << "(2) Computer vs Computer \n";
	cout << "(3) Castling Demo\n";
	cout << "(4) En Passant Demo\n";
	cout << "(5) Promotion Demo\n";
	
	cout << "Game mode: ";
	char game_mode = ' ';
	cin >> game_mode;
	while (game_mode > '5' || game_mode < '1') {
		cout << "Invalid input. Try again: ";
		cin >> game_mode;
	}

	cout << "Choose a size >= 8 for your gameboard \n";
	cout << "Size: ";
	int size = 0;
	cin >> size;
	while (size < 8) {
		cout << "Invalid input. Try again: ";
		cin >> size;
	}

	if (game_mode == '1') {
		player_game(size);
	}
	else if (game_mode == '2') {
		generated_game(size);
	}
	else if (game_mode == '3') {
		castling(size);
	}
	else if (game_mode == '4') {
		en_passant(size);
	}
	else if (game_mode == '5') {
		promotion(size);
	}
	
}

void game::player_game(int size) {
	chessboard board(size);
	board.print();
	bool over = false;
	string coo;
	int r, c, r1, c1;
	bool valid_turn;
	while (!over) {
		valid_turn = false;
		while (!over) {
			board.active_player();
			cout << "Enter coordinates of the figure you want to move: ";
			cin >> coo;
			while (!(isalpha(coo[0]) && isdigit(coo[1]) && 
					 coo[0] >= 'a' && coo[0] < 'a' + size)) {
				cout << "Input should look like this 'a1'. Try again: ";
				cin >> coo;
			}
			r = board.get_coordinate_num(coo[1]);
			c = board.get_coordinate_char(coo[0]);
			if (board.can_take_figure(r, c) && board.take_figure(r, c)) {
				cout << "Enter coordinates of the field you want to move to: ";
				cin >> coo;
				while (!(isalpha(coo[0]) && isdigit(coo[1]) &&
					coo[0] >= 'a' && coo[0] < 'a' + size)) {
					cout << "Input should look like this 'a1'. Try again: ";
					cin >> coo;
				}
				r1 = board.get_coordinate_num(coo[1]);
				c1 = board.get_coordinate_char(coo[0]);
				if (board.can_move(r, c, r1, c1)) {
					board.move_figure(r, c, r1, c1);
					if (board.check_rules()) {
						over = true;
					}
					valid_turn = true;
				}
				else {
					cout << "Invalid move!\n";
				}
			}
			else
			{
				cout << "You can't take this figure!\n";
			}
			board.print();
		}
	}
}

void game::generated_game(int size) {
	chessboard board(size);
	board.auto_promotion = true;
	board.print();
	bool over = false;
	string coo;
	int r, c, r1, c1;
	bool valid_turn;
	valid_turn = false;
	srand(time(NULL));
	while (!over) {
		board.active_player();
		r = rand() % size;
		c = rand() % size;
		while (!(board.can_take_figure(r, c) && board.take_figure(r, c))) {
			r = rand() % size;
			c = rand() % size;
		}
		r1 = rand() % size;
		c1 = rand() % size;
		while (!board.can_move(r, c, r1, c1)) {
			r1 = rand() % size;
			c1 = rand() % size;
		}
		board.move_figure(r, c, r1, c1);
		board.print();
		if (board.check_rules()) {
			over = true;
		}
		valid_turn = true;
	}
}

void game::castling(int size) {
	chessboard board(size);
	board.print();
	board.active_player();
	board.take_figure(1, 3);
	board.move_figure(1, 3, 2, 3);
	board.print();
	board.active_player();
	board.take_figure(6, 0);
	board.move_figure(6, 0, 5, 0);
	board.print();
	board.active_player();
	board.take_figure(0, 2);
	board.move_figure(0, 2, 2, 4);
	board.print();
	board.active_player();
	board.take_figure(6, 1);
	board.move_figure(6, 1, 5, 1);
	board.print();
	board.active_player();
	board.take_figure(0, 3);
	board.move_figure(0, 3, 1, 3);
	board.print();
	board.active_player();
	board.take_figure(6, 2);
	board.move_figure(6, 2, 5, 2);
	board.print();
	board.active_player();
	board.take_figure(0, 1);
	board.move_figure(0, 1, 2, 0);
	board.print();
	board.active_player();
	board.take_figure(6, 3);
	board.move_figure(6, 3, 5, 3);
	board.print();
	board.active_player();
	board.take_figure(0, 4);
	board.move_figure(0, 4, 0, 2);
	board.print();
}

void game::en_passant(int size) {
	chessboard board(size);
	board.print();
	board.active_player();
	board.take_figure(1, 3);
	board.move_figure(1, 3, 3, 3);
	board.print();
	board.active_player();
	board.take_figure(6, 4);
	board.move_figure(6, 4, 4, 4);
	board.print();
	board.active_player();
	board.take_figure(3, 3);
	board.move_figure(3, 3, 4, 3);
	board.print();
	board.active_player();
	board.take_figure(6, 1);
	board.move_figure(6, 1, 5, 1);
	board.print();
	board.active_player();
	board.take_figure(4, 3);
	board.move_figure(4, 3, 5, 4);
	board.print();
}

void game::promotion(int size) {
	chessboard board(size);
	board.print();
	board.active_player();
	board.take_figure(1, 2);
	board.move_figure(1, 2, 3, 2);
	board.print();
	board.active_player();
	board.take_figure(7, 6);
	board.move_figure(7, 6, 5, 5);
	board.print();
	board.active_player();
	board.take_figure(3, 2);
	board.move_figure(3, 2, 4, 2);
	board.print();
	board.active_player();
	board.take_figure(5, 5);
	board.move_figure(5, 5, 7, 6);
	board.print();
	board.active_player();
	board.take_figure(4, 2);
	board.move_figure(4, 2, 5, 2);
	board.print();
	board.active_player();
	board.take_figure(7, 6);
	board.move_figure(7, 6, 5, 5);
	board.print();
	board.take_figure(5, 2);
	board.move_figure(5, 2, 6, 1);
	board.print();
	board.active_player();
	board.take_figure(5, 5);
	board.move_figure(5, 5, 7, 6);
	board.print();
	board.active_player();
	board.take_figure(6, 1);
	board.move_figure(6, 1, 7, 0);
	board.print();	
}