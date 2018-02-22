#include "map_space.h"

//IMPLEMENTATION STARTS HERE

map_space::map_space(map_space_enum type)
{
	this->space_type = type;

	switch (this->space_type)
	{
	case EMPTY:
		this->board_char = '.';
		break;
	case INITIAL:
		this->board_char = 'i';
		break;
	case GOAL:
		this->board_char = 'g';
		break;
	case OBSTACLE:
		this->board_char = '+';
		break;
	case TRAVELED:
		this->board_char = 'o';
		break;
	case UNINITIALIZED:
		this->board_char = 'X';
		break;
	}
}

map_space::~map_space()
{

}