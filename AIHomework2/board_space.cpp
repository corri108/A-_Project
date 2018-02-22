#include "board_space.h"

board_space::board_space(int n)
{
	this->n = n;
	init_board();
}

board_space::~board_space()
{

}

void board_space::init_board()
{
	//initialize the array that we need to represent the board
	board = new map_space**[n];

	for (int i = 0; i < n; ++i)
	{
		board[i] = new map_space*[n];
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			board[i][j] = new map_space(UNINITIALIZED);
		}
	}
}

//prints the board to the console for viewing
void board_space::print_board()
{
	printf("Current board:\n");

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			printf("%c ", board[i][j]->board_char);
		}

		printf("\n");
	}
}