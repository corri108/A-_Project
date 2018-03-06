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

int main(int argc, char **argv)
{
	//make sure user puts in a text file for arg
	if(argc == 1)
	{
		printf("You need to supply a command line argument of the text file to read in.");
		return -1;
	}
	
	int n;
	//std::vector<char> board_chars = get_file_input("board.txt", &n);
	std::vector<char> board_chars = get_file_input(argv[1], &n);

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
	
	printf("\nCheck for output files. They will be in the folder.");

	return 0;
}