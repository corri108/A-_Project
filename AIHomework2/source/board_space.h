#pragma once
#include "map_space.h"
#include "eval_type.h"
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <climits>
#include <vector>
#include <map>

class board_space
{
public:
	board_space(int n, std::vector<char> board_chars);
	~board_space();
	void init_board(std::vector<char> board_chars);
	void print_board();
	void print_board_manhattan();
	void generate_manhattan_values();
	void generate_euclidian_values();
	void solve_board(eval_type t);
	void reset_board();
	map_space *get_neighbor(map_space* current, cardinal_direction d);
	void add_neighbors(std::vector<map_space*> &open_list, std::vector<map_space*> &closed_list, map_space *current);
	bool are_neighbors(map_space* current, map_space* other);
	void write_file(const char* file_name, char* header, int num_steps, int num_nodes);
	map_space *goal;
	map_space *start;
	map_space *current;
private:
	map_space ***board;
	void solve_euclidian();
	void solve_a_star_euclidian();
	void solve_manhattan();
	void solve_a_star_manhattan();
	void generate_manhattan_recursive(int x, int y, int value);
	int n;
};