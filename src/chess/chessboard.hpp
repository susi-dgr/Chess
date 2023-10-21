#include <vector>
#include <string>
#include <iostream>
#include "chessman.hpp"

using namespace std;

class chessboard {
	int size;
	bool player; //true - white, false - black
	vector<vector<chessman>> board;
	vector<vector<chessman>> tmp; //for showing possible moves
	
	//rules
	bool is_in_check(int r, int c);
	bool puts_in_check(int r, int c, int r1, int c1);
	bool castling(int r, int c, int r1, int c1);
	bool en_passant(int r, int c, int r1, int c1); 
	void promotion(int r, int c); 
	bool draw();
	bool checkmate();

	//helpers
	bool is_free(int r, int c);
	bool is_enemy(int r, int c);
	bool diff_team(int r, int c, int r1, int c1);
	bool is_valid(int r, int c);
	bool can_reach(int r, int c, int r1, int c1);
	chessman get_figure(int r, int c);

	//for output
	void fill_board(int r, int c);
	void print(vector<vector<chessman>> board); //helper to output tmp
	
public:
	//for generated game
	bool auto_promotion; 
	
	chessboard(int size);
	
	bool check_rules();
	void active_player();
	int get_size();

	//field
	bool can_take_figure(int r, int c);
	bool can_move_figure(int r, int c, int r1, int c1); 
	bool can_move(int r, int c, int r1, int c1); 
	bool take_figure(int r, int c);
	void move_figure(int r, int c, int r1, int c1);

	//converting coordinates
	int get_coordinate_char(char c);
	int get_coordinate_num(char c);
	
	void print();
};
