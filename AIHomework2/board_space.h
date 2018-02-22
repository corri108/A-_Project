#pragma once
#include "map_space.h"
#include <stdio.h>

class board_space
{
public:
	board_space(int n);
	~board_space();
	void init_board();
	void fill_board();
	void print_board();
private:
	map_space ***board;
	int n;
};