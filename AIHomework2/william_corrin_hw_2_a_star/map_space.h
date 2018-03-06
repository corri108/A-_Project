#pragma once

#include "location.h"

enum map_space_enum
{
	UNINITIALIZED = -1,
	EMPTY = 0,
	INITIAL = 1,
	GOAL = 2,
	OBSTACLE = 3,
	TRAVELED = 4
};

enum cardinal_direction
{
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3
};

class map_space
{
public:
	map_space(char c, int x, int y);
	~map_space();
	map_space_enum space_type;
	map_space *parent;
	char board_char;
	location *loc;
	int manhattan_value = -1;
	float euclidian_value = -1;
	int move_value = 1;
	bool traveled = false;
	bool is_destination = false;
};