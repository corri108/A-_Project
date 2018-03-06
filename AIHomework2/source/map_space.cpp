#include "map_space.h"
#include <stdio.h>
//IMPLEMENTATION STARTS HERE

map_space::map_space(char c, int x, int y)
{
	this->board_char = c;
	this->loc = new location(x, y);
	this->manhattan_value = -1;
	this->traveled = false;
	this->parent = NULL;
	this->move_value = -1;
	this->is_destination = false;

	switch (this->board_char)
	{
	case  '.':
		this->space_type = EMPTY;
		break;
	case 'i':
		this->space_type = INITIAL;
		break;
	case 'g':
		this->space_type = GOAL;
		break;
	case '+':
		this->space_type = OBSTACLE;
		break;
	case 'o':
		this->space_type = TRAVELED;
		break;
	case  'X':
		this->space_type = UNINITIALIZED;
		break;
	}
}

map_space::~map_space()
{

}