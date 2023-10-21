#include <iostream>
#include <cctype>
#include <cmath>
#include "chessman.hpp"

//chessman class
chessman::chessman() {
	figure = ' ';
	r = -1;
	c = -1;
	active = false;
	in_hand = false;
	moved = false;
	moved_two = false;
}

chessman::chessman(char figure, int r, int c) {
	this->figure = figure;
	this->r = r;
	this->c = c;
	active = false;
	in_hand = false;
	moved = false;
	moved_two = false;
}

bool chessman::get_color() {
	return isupper(figure);
}

char chessman::get_figure() {
	return figure;
}

bool chessman::is_essential() {
	return figure == 'K' || figure == 'k';
}

bool chessman::is_valid_move(int r1,int c1) {
	return false;
}

//subclasses
bool king::is_valid_move(int r1,int c1) {
	return abs(r1 - r) <= 1 && abs(c1 - c) <= 1;
}

bool queen::is_valid_move(int r1,int c1) {
	return abs(r1 - r) == abs(c1 - c) || r1 == r || c1 == c;
}

bool bishop::is_valid_move(int r1,int c1) {
	return abs(r1 - r) == abs(c1 - c);
}

bool rook::is_valid_move(int r1,int c1) {
	return r1 == r || c1 == c;
}

bool knight::is_valid_move(int r1,int c1) {
	return abs(r1 - r) == 2 && abs(c1 - c) == 1 || abs(r1 - r) == 1 && abs(c1 - c) == 2;
}

bool pawn::is_valid_move(int r1,int c1) {
	if (get_color()) {
		if (!(c1 == c && r1 - r == 1)) {
			return false;
		}
	} 
	else if (!(c1 == c && r1 - r == -1)) {
			return false;
	}
}


