// AIHomework2.cpp : Defines the entry point for the console application.
#include "board_space.h"
#include <iostream>

int main()
{
	board_space board = board_space(10);
	board.print_board();

	map_space m = map_space(EMPTY);

	//absorb input
	char buffer[200];
	scanf("%s", buffer);

	return 0;
}