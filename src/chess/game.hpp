#include "chessboard.hpp"

class game {
public:
	game();
	
	void player_game(int size);
	void generated_game(int size);
	void castling(int size);
	void en_passant(int size);
	void promotion(int size);
};