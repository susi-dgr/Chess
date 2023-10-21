#include "chessboard.hpp"

using namespace std;

//rules
bool chessboard::is_in_check(int r, int c) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (is_enemy(i, j)) {
				if (can_move_figure(i, j, r, c)) {
					return true;
				}
			}
		}
	}
	return false;
}

bool chessboard::puts_in_check(int r, int c, int r1, int c1) {
	vector<vector<chessman>> tmp2 = board; //tmp2, so it doesn't overwrite tmp
	
	//making move and then checking if the king would be in check
	board[r1][c1] = board[r][c];
	fill_board(r, c);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (player && board[i][j].get_figure() == 'K') {
				if (is_in_check(i, j)) {
					board = tmp2;
					return true;
				}
			}
			else if (!player && board[i][j].get_figure() == 'k') {
				if (is_in_check(i, j)) {
					board = tmp2;
					return true;
				}
			}
		}
	}
	board = tmp2;
	return false;
}

bool chessboard::castling(int r, int c, int r1, int c1) {
	if ((board[r][c].get_figure() == 'K' 
	  || board[r][c].get_figure() == 'k') 
	  && !board[r][c].moved) {
		if ((board[r][c - 4].get_figure() == 'R' 
		  || board[r][c - 4].get_figure() == 'r') 
		  && !board[r][c - 4].moved) {
			if (is_free(r, c - 1) && is_free(r, c - 2) && is_free(r, c - 3)) {
				return true;
			}
		}
		else if ((board[r][c + 3].get_figure() == 'R' 
			   || board[r][c + 3].get_figure() == 'r') 
			   && !board[r][c + 3].moved) {
			if (is_free(r, c + 1) && is_free(r, c + 2)) {
				return true;
			}
		}
	}
	return false;
}

bool chessboard::en_passant(int r, int c, int r1, int c1) {
	if ((abs(c1 - c) == 1 && abs(r1 - r) == 1)) {
		if (board[r][c].get_figure() == 'P') {
			if (board[r1 - 1][c1].moved_two && (board[r1 - 1][c1].get_figure() == 'p')) {
				return true;
			}
		}
		else if (board[r][c].get_figure() == 'p') {
			if (board[r1 + 1][c1].moved_two && (board[r1 + 1][c1].get_figure() == 'P')) {
				return true;
			}
		}
	}
	return false;
}

void chessboard::promotion(int r, int c) {
	if (board[r][c].get_figure() == 'P' && r == size - 1) {
		char figure = ' ';
		while (figure != 'Q' && figure != 'R' && figure != 'B' && figure != 'N') {
			cout << "Choose a figure: Q, R, B, N" << endl;
			if (auto_promotion) {
				figure = "QRBN"[rand() % 4];
			}
			else {
				cin >> figure;
			}
		}
		board[r][c] = chessman(figure, r, c);
	}
	else if (board[r][c].get_figure() == 'p' && r == 0) {
		char figure = ' ';
		while (figure != 'q' && figure != 'r' && figure != 'b' && figure != 'n') {
			cout << "Choose a figure: q, r, b, n" << endl;
			if (auto_promotion) {
				figure = "qrbn"[rand() % 4];
			}
			else {
				cin >> figure;
			}
		}
		board[r][c] = chessman(figure, r, c);
	}
}

bool chessboard::draw() {
	bool other_figure = false; //other than bishop, knight, king
	
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (!is_free(i, j) &&
				board[i][j].get_figure() != 'B' && board[i][j].get_figure() != 'b' &&
				board[i][j].get_figure() != 'N' && board[i][j].get_figure() != 'n' &&
				board[i][j].get_figure() != 'K' && board[i][j].get_figure() != 'k') {
				return false;
			}
		}
	}
	cout << "Draw!" << endl;
	return true;
}

bool chessboard::checkmate() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if ((player && isupper(board[i][j].get_figure())) 
			|| (!player && islower(board[i][j].get_figure()))) {
				for (int k = 0; k < size; k++) {
					for (int l = 0; l < size; l++) {
						if (can_move(i, j, k, l)) {
							return false;
						}
					}
				}
			}
		}
	}
	cout << "Checkmate!" << endl;
	if (!player) {
		cout << "White wins!" << endl;
	}
	else {
		cout << "Black wins!" << endl;
	}
	return true;
}

//helpers
bool chessboard::is_free(int r, int c) {
	if (board[r][c].get_figure() == '.' || board[r][c].get_figure() == '*') {
		return true;
	}
	else {
		return false;
	}
}

bool chessboard::is_enemy(int r, int c) {
	if (is_free(r, c)) return false;
	if (player) {
		return islower(board[r][c].get_figure());
	}
	else if (!player) {
		return isupper(board[r][c].get_figure());
	}
	return false;
}

bool chessboard::diff_team(int r, int c, int r1, int c1) {
	if (is_free(r, c) || is_free(r1, c1)) return false;
	if (isupper(board[r][c].get_figure()) && islower(board[r1][c1].get_figure())) return true;
	if (islower(board[r][c].get_figure()) && isupper(board[r1][c1].get_figure())) return true;
	return false;
}

bool chessboard::is_valid(int r, int c) {
	return is_free(r, c) || is_enemy(r, c);
}

bool chessboard::can_reach(int r, int c, int r1, int c1) {
	//checking horizontally & vertically
	if (r1 == r) {
		for (int i = min(c, c1) + 1; i < max(c, c1); i++) {
			if (!is_free(r, i)) {
				return false;
			}
		}
	}
	else if (c1 == c) {
		for (int i = min(r, r1) + 1; i < max(r, r1); i++) {
			if (!is_free(i, c)) {
				return false;
			}
		}
	}

	//checking diagonally
	else if (abs(r1 - r) == abs(c1 - c)) {
		int i = r;
		int j = c;
		while (i != r1 && j != c1) {
			if (i < r1) {
				i++;
			}
			else {
				i--;
			}
			if (j < c1) {
				j++;
			}
			else {
				j--;
			}
			if (i != r1 && j != c1 && !is_free(i, j)) {
				return false;
			}
		}
	}
	else {
		return false;
	}
	return true;
}

chessman chessboard::get_figure(int r, int c) {
	return board[r][c];
}

//for output
void chessboard::fill_board(int r, int c) {
	if ((r + c) % 2 == 0) {
		board[r][c] = chessman('.', r, c);
	}
	else {
		board[r][c] = chessman('*', r, c);
	}
}

void chessboard::print(vector<vector<chessman>> board) {
	for (int i = size - 1; i >= 0; i--) {
		if (i == size - 1) {
			cout << "   |";
			for (char ch = 'a'; ch < char('a' + size); ch++) {
				cout << " " << ch << " ";
			}
			cout << "|   \n";
			cout << " --+";
			for (int i = 0; i < size; i++) cout << "---";
			cout << "+-- \n";
		}
		for (int j = 0; j < size; j++) {

			if (j == 0) {
				cout << i + 1 << "  |";
			}
			if (board[i][j].in_hand) {
				cout << "(" << board[i][j].get_figure() << ")";
			}
			else if (board[i][j].active) {
				cout << "[" << board[i][j].get_figure() << "]";
			}
			else {
				cout << " " << board[i][j].get_figure() << " ";
			}
			if (j == size - 1) {
				cout << "| " << i + 1 << endl;
			}
		}
		if (i == 0) {
			cout << " --+";
			for (int i = 0; i < size; i++) cout << "---";
			cout << "+-- \n";
			cout << "   |";
			for (char ch = 'a'; ch < char('a' + size); ch++) {
				cout << " " << ch << " ";
			}
			cout << "|   \n";
		}
	}
	cout << " \n";
}

chessboard::chessboard(int size) {
	string figures = "RNBQKBNRrnbqkbnr";
	this->size = size;
	player = true;
	board = vector<vector<chessman>>(size, vector<chessman>(size));
	tmp = vector<vector<chessman>>(size, vector<chessman>(size));
	auto_promotion = false;
	
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			fill_board(i, j);
		}
	}
	
	for (int i = 0; i < size; i++) {
		board[1][i] = chessman('P', 1, i);
		board[size - 2][i] = chessman('p', size - 2, i);
	}

	for (int i = 0; i < (figures.length() / 2); i++) {
		board[0][i] = chessman(figures[i], 0, i);
		board[size - 1][i] = chessman(figures[i + (figures.length() / 2)], size - 1, i);
	}
	tmp = board;
}

bool chessboard::check_rules() {
	return draw() || checkmate();
}

void chessboard::active_player() {
	if (player) {
		cout << "White's turn! (upper case)\n";
	}
	else {
		cout << "Black's turn! (lower case)\n";
	}
}

int chessboard::get_size() {
	return size;
}

//field
bool chessboard::can_take_figure(int r, int c) {
	return (!is_valid(r, c));
}

bool chessboard::can_move_figure(int r, int c, int r1, int c1) {
	chessman figure = board[r][c];
	if (figure.get_figure() == 'K' || figure.get_figure() == 'k') {
		king king(figure.get_figure(), r, c);
		if (r1 == r && abs(c1 - c) == 2) {
			return castling(r, c, r1, c1);
		}
		return king.is_valid_move(r1, c1);

		//something wrong here
	}
	else if (figure.get_figure() == 'Q' || figure.get_figure() == 'q') {
		queen queen(figure.get_figure(), r, c);
		return queen.is_valid_move(r1, c1) && can_reach(r, c, r1, c1);
	}
	else if (figure.get_figure() == 'R' || figure.get_figure() == 'r') {
		rook rook(figure.get_figure(), r, c);
		return rook.is_valid_move(r1, c1) && can_reach(r, c, r1, c1);
	}
	else if (figure.get_figure() == 'B' || figure.get_figure() == 'b') {
		bishop bishop(figure.get_figure(), r, c);
		return bishop.is_valid_move(r1, c1) && can_reach(r, c, r1, c1);
	}
	else if (figure.get_figure() == 'N' || figure.get_figure() == 'n') {
		knight knight(figure.get_figure(), r, c);
		return knight.is_valid_move(r1, c1);
	}
	else if (figure.get_figure() == 'P' || figure.get_figure() == 'p') {
		pawn pawn(board[r][c].get_figure(), r, c);
		if (!figure.moved) {
			if (player) {
				return (c1 == c && (r1 - r == 2 || r1 - r == 1)) 
					&& can_reach(r, c, r1, c1) && is_free(r1, c1);
			}
			else if (!player) {
				return (c1 == c && (r - r1 == 2 || r - r1 == 1)) 
					&& can_reach(r, c, r1, c1) && is_free(r1, c1);
			}
		}
		else if (diff_team(r, c, r1, c1) && (abs(c1 - c) == 1 && abs(r1 - r) == 1)) {
			return true;
		}
		else if (en_passant(r, c, r1, c1)) {
			return true;
		}
		else {
			return pawn.is_valid_move(r1, c1) && is_free(r1, c1);
		}
	}
	return false;
}

bool chessboard::can_move(int r, int c, int r1, int c1) {
	return can_move_figure(r, c, r1, c1) && is_valid(r1, c1) 
		&& !(r == r1 && c == c1) && !puts_in_check(r, c, r1, c1);
}

bool chessboard::take_figure(int r, int c) {
	bool result = false;
	tmp = board;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (can_move(r, c, i, j)) {
				tmp[i][j].active = true;
				result = true;
			}
		}
	}
	if (result) {
		tmp[r][c].in_hand = true;
		print(tmp);
		return true;
	}
	else {
		return false;
	}
}

void chessboard::move_figure(int r, int c, int r1, int c1) {
	//checking if a pawn will move two for en_passant
	if (board[r][c].get_figure() == 'P' && r1 == r + 2) {
		board[r][c].moved_two = true;
	}
	else if (board[r][c].get_figure() == 'p' && r1 == r - 2) {
		board[r][c].moved_two = true;
	}
	else {
		board[r][c].moved_two = false;
	}

	if (en_passant(r, c, r1, c1)) {
		if (player) {
			fill_board(r1 - 1, c1);
		}
		else {
			fill_board(r1 + 1, c1);
		}
	}
	
	if (castling(r, c, r1, c1)) {
		if (c1 == 2) {
			board[r1][3] = board[r1][0];
			fill_board(r1, 0);
		}
		else {
			board[r1][5] = board[r1][size - 1];
			fill_board(r1, size - 1);
		}
	}
	
	board[r1][c1] = board[r][c];
	fill_board(r, c);
	board[r1][c1].moved = true;

	promotion(r1, c1);
	
	player = !player;
}

//converting coordinates
int chessboard::get_coordinate_char(char c) {
	return c - 'a';
}

int chessboard::get_coordinate_num(char c) {
	return int(c - '0') - 1;
}

void chessboard::print() {
	print(board);
}