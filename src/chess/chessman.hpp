class chessman { 
protected:
	char figure;
	int r, c;
public:
	bool active; //[]
	bool in_hand; //()
	bool moved;
	bool moved_two;
	
	chessman();
	chessman(char figure, int r, int c);
	bool get_color();
	char get_figure();
	bool is_essential();
	virtual bool is_valid_move(int r1,int c1);
};

class king : chessman {
public:
	king(char figure, int r, int c) : chessman(figure, r, c) {}
	bool is_valid_move(int r1,int c1);
};

class queen : chessman {
public:
	queen(char figure, int r, int c) : chessman(figure, r, c) {}
	bool is_valid_move(int r1,int c1);
};

class bishop : chessman {
public:
	bishop(char figure, int r, int c) : chessman(figure, r, c) {}
	bool is_valid_move(int r1,int c1);
};

class rook : chessman {	
public:
	rook(char figure, int r, int c) : chessman(figure, r, c) {}
	bool is_valid_move(int r1,int c1);
};

class knight : chessman {
public:
	knight(char figure, int r, int c) : chessman(figure, r, c) {}
	bool is_valid_move(int r1,int c1);
};

class pawn : chessman {
public:
	pawn(char figure, int r, int c) : chessman(figure, r, c) {}
	bool is_valid_move(int r1,int c1);
};

