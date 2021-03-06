// AIHomework2.cpp : Defines the entry point for the console application.
#include "board_space.h"
#include <iostream>
#include <fstream>

std::vector<char> get_file_input(const char *file_path, int *n)
{
	std::vector<char> list = std::vector<char>();

	std::ifstream infile(file_path);
	infile >> *n;

	for (int j = 0; j < *n; ++j)
	{
		for (int i = 0; i < *n; ++i)
		{
			char c;
			infile >> c;
			list.push_back(c);
		}
	}

	return list;
}

int main()
{
	int n;
	std::vector<char> board_chars = get_file_input("board.txt", &n);
	//std::vector<char> board_chars = get_file_input(argc[0], &n);

	board_space board = board_space(n, board_chars);
	board.print_board();
	board.generate_manhattan_values();
	board.generate_euclidian_values();
	board.print_board_manhattan();

	//euclidian
	board.solve_board(EUCLIDIAN);
	board.reset_board();
	//manhattan
	board.solve_board(MANHATTAN);
	board.reset_board();
	//a star euclidian
	board.solve_board(A_STAR_EUCLIDIAN);
	board.reset_board();
	//a star manhattan
	board.solve_board(A_STAR_MANHATTAN);

	//map_space m = map_space(EMPTY);

	//absorb input
	char buffer[200];
	scanf("%s", buffer);

	return 0;
}