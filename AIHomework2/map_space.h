#pragma once

enum map_space_enum
{
	UNINITIALIZED = -1,
	EMPTY = 0,
	INITIAL = 1,
	GOAL = 2,
	OBSTACLE = 3,
	TRAVELED = 4
};

class map_space
{
public:
	map_space(map_space_enum type);
	~map_space();
	map_space_enum space_type;
	char board_char;
};