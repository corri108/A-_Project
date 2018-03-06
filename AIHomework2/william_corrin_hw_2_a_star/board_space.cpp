#include "board_space.h"

//constructor and destructor
board_space::board_space(int n, std::vector<char> board_chars)
{
	this->n = n;
	init_board(board_chars);
}

board_space::~board_space()
{

}

/////////////////////////////////////////////
//PUBLIC FUNCS
/////////////////////////////////////////////

//initializes the board given a vector of characters from the input file
void board_space::init_board(std::vector<char> board_chars)
{
	//initialize the array that we need to represent the board
	board = new map_space**[n];

	//init the width arrays
	for (int i = 0; i < n; ++i)
	{
		board[i] = new map_space*[n];
	}

	//fill the 2D array with the board characters
	for (int col = 0; col < n; ++col)
	{
		for (int row = 0; row < n; ++row)
		{
			board[col][row] = new map_space(board_chars[col * n + row], row, col);

			//if we just filled the goal
			if (board[col][row]->space_type == GOAL)
			{
				this->goal = board[col][row];
				this->goal->is_destination = true;
			}
			else if (board[col][row]->space_type == INITIAL)//if we just filled the initial spot
			{
				this->start = board[col][row];
				this->current = this->start;
			}
		}
	}
}

//generates manhattan values for the board
void board_space::generate_manhattan_values()
{
	generate_manhattan_recursive(this->goal->loc->x, this->goal->loc->y, 0);
}

//generates euclidian values for the board
void board_space::generate_euclidian_values()
{
	printf("Current euclidian values:\n");

	for (int col = 0; col < n; ++col)
	{
		for (int row = 0; row < n; ++row)
		{
			board[col][row]->euclidian_value = sqrtf(((board[col][row]->loc->x - this->goal->loc->x) * (board[col][row]->loc->x - this->goal->loc->x) +
				(board[col][row]->loc->y - this->goal->loc->y) * (board[col][row]->loc->y - this->goal->loc->y)));

			printf("%.2f ", board[col][row]->euclidian_value);
		}

		printf("\n");
	}
}

//main handler method for solving any kind of algorithm
void board_space::solve_board(eval_type t)
{
	switch (t)
	{
	case MANHATTAN:
		solve_manhattan();
		break;
	case EUCLIDIAN:
		solve_euclidian();
		break;
	case A_STAR_MANHATTAN:
		solve_a_star_manhattan();
		break;
	case A_STAR_EUCLIDIAN:
		solve_a_star_euclidian();
		break;
	}
}

//prints the board to the console for viewing
void board_space::print_board()
{
	printf("Current board:\n");

	for (int col = 0; col < n; ++col)
	{
		for (int row = 0; row < n; ++row)
		{
			printf("%c ", board[col][row]->board_char);
		}

		printf("\n");
	}
}

//prints the board's manhattan values
void board_space::print_board_manhattan()
{
	printf("\nCurrent manhattan values:\n");

	for (int col = 0; col < n; ++col)
	{
		for (int row = 0; row < n; ++row)
		{
			if (board[col][row]->board_char != '+')
				printf("%d ", board[col][row]->manhattan_value);
			else
				printf("+ ");
		}

		printf("\n");
	}
}

//resets the board to no traveled spots after its been solved by a certain method
void board_space::reset_board()
{
	for (int col = 0; col < n; ++col)
	{
		for (int row = 0; row < n; ++row)
		{
			if (board[col][row]->space_type == TRAVELED)
			{
				board[col][row]->board_char = '.';
				board[col][row]->space_type = EMPTY;
				board[col][row]->move_value = 0;
			}
		}
	}
}

///////////////////////////////////////////////
//PRIVATE FUNCS
///////////////////////////////////////////////

//recursive function to generate manhattan values
void board_space::generate_manhattan_recursive(int x, int y, int value)
{
	if (board[y][x]->traveled && board[y][x]->manhattan_value < value)
		return;

	board[y][x]->traveled = true;
	board[y][x]->manhattan_value = value;

	if (x - 1 >= 0)
	{
		generate_manhattan_recursive(x - 1, y, value + 1);
	}

	if (x + 1 < this->n)
	{
		generate_manhattan_recursive(x + 1, y, value + 1);
	}

	if (y - 1 >= 0)
	{
		generate_manhattan_recursive(x, y - 1, value + 1);
	}

	if (y + 1 < this->n)
	{
		generate_manhattan_recursive(x, y + 1, value + 1);
	}
}

//gets a neighbor if it exits. otherwise returns null
map_space* board_space::get_neighbor(map_space* current, cardinal_direction d)
{
	int x = current->loc->x;
	int y = current->loc->y;

	//is our left neighbor valid, and is it NOT an obstacle?
	if (d == LEFT)
	{
		if (x - 1 >= 0)// && this->board[y][x - 1]->space_type != OBSTACLE)
			return this->board[y][x - 1];
		else
			return NULL;
	}

	//is our left neighbor valid, and is it NOT an obstacle?
	else if (d == RIGHT)
	{
		if (x + 1 < this->n)//&& this->board[y][x + 1]->space_type != OBSTACLE)
			return this->board[y][x + 1];
		else
			return NULL;
	}

	//is our left neighbor valid, and is it NOT an obstacle?
	else if (d == UP)
	{
		if (y - 1 >= 0)//&& this->board[y - 1][x]->space_type != OBSTACLE)
			return this->board[y - 1][x];
		else
			return NULL;
	}

	//is our left neighbor valid, and is it NOT an obstacle?
	else if (d == DOWN)
	{
		if (y + 1 < this->n)//&& this->board[y + 1][x]->space_type != OBSTACLE)
			return this->board[y + 1][x];
		else
			return NULL;
	}

	return NULL;
}

//returns true if they are neighbors and if they are not obstacles
bool board_space::are_neighbors(map_space* current, map_space* other)
{
	int x1 = current->loc->x;
	int y1 = current->loc->y;
	int x2 = other->loc->x;
	int y2 = other->loc->y;

	if (x1 - 1 == x2 && y1 == y2)
		return true;

	else if (x1 + 1 == x2 && y1 == y2)
		return true;

	else if (x1 == x2 && y1 + 1 == y2)
		return true;

	else if (x1 == x2 && y1 - 1 == y2)
		return true;

	return false;
}

//adds neighbors of the space to the given list if they havent been added already
void board_space::add_neighbors(std::vector<map_space*> &open_list, std::vector<map_space*> &closed_list, map_space *current)
{
	//add UP if it passes and isnt already inn list
	map_space *up = get_neighbor(current, UP);

	if (up != NULL && up->space_type != OBSTACLE &&
		std::find(open_list.begin(), open_list.end(), up) == open_list.end() &&
		std::find(closed_list.begin(), closed_list.end(), up) == closed_list.end())
	{
		up->parent = current;
		up->move_value = current->move_value + 1;
		open_list.push_back(up);
	}

	//add RIGHT if it passes and isnt already inn list
	map_space *right = get_neighbor(current, RIGHT);

	if (right != NULL && right->space_type != OBSTACLE &&
		std::find(open_list.begin(), open_list.end(), right) == open_list.end() &&
		std::find(closed_list.begin(), closed_list.end(), right) == closed_list.end())
	{
		right->parent = current;
		right->move_value = current->move_value + 1;
		open_list.push_back(right);
	}

	//add DOWN if it passes and isnt already inn list
	map_space *down = get_neighbor(current, DOWN);

	if (down != NULL && down->space_type != OBSTACLE &&
		std::find(open_list.begin(), open_list.end(), down) == open_list.end() &&
		std::find(closed_list.begin(), closed_list.end(), down) == closed_list.end())
	{
		down->parent = current;
		down->move_value = current->move_value + 1;
		open_list.push_back(down);
	}

	//add LEFT if it passes and isnt already inn list
	map_space *left = get_neighbor(current, LEFT);

	if (left != NULL && left->space_type != OBSTACLE &&
		std::find(open_list.begin(), open_list.end(), left) == open_list.end() &&
		std::find(closed_list.begin(), closed_list.end(), left) == closed_list.end())
	{
		left->parent = current;
		left->move_value = current->move_value + 1;
		open_list.push_back(left);
	}
}

//method for solving standard manhattan
void board_space::solve_manhattan()
{
	//start at initial state
	map_space* current = this->start;
	this->start->move_value = 0;

	std::vector<map_space*> closed = std::vector<map_space*>();
	std::vector<map_space*> open = std::vector<map_space*>();

	//add initial state to the closed list
	closed.push_back(this->current);
	bool solution = false;

	//beginning part of the algorithm - add neighbors of goal to the open list
	add_neighbors(open, closed, current);

	bool solution_done = false;
	map_space *solved = NULL;

	while (!solution_done)
	{
		//now find out which has lowest h score
		map_space* best_space = NULL;
		int lowest_score = INT_MAX;
		int best_space_index = -1;

		for (int i = 0; i < open.size(); ++i)
		{
			if (open[i]->manhattan_value < lowest_score)
			{
				lowest_score = open[i]->manhattan_value;
				best_space = open[i];
				best_space_index = i;
			}
		}

		//add this to the closed list and remove it from the open list.
		closed.push_back(best_space);
		open.erase(open.begin() + best_space_index);

		if (best_space->is_destination)
		{
			solved = best_space;
			break;
		}

		//add any potential NEW adjacent tiles to the open list
		add_neighbors(open, closed, best_space);
	}

	printf("\nManhattan - Solved!\n");
	int num_steps = 1;
	int num_nodes = open.size();// +closed.size();

	while (solved != NULL)
	{
		//update path char if it isnt goal or init
		if (solved->space_type != GOAL && solved->space_type != INITIAL)
		{
			solved->board_char = 'o';
			solved->space_type = TRAVELED;
			num_steps++;
		}

		solved = solved->parent;
	}

	print_board();
	printf("Number of steps: %d\nNumber of nodes: %d\n----------------------------------------\n", num_steps, num_nodes);

	//write to file
	write_file("standard_manhattan_output.txt", "Manhattan Solution\n", num_steps, num_nodes);
}

//method for solving standard euclidian
void board_space::solve_euclidian()
{
	//start at initial state
	map_space* current = this->start;
	this->start->move_value = 0;

	std::vector<map_space*> closed = std::vector<map_space*>();
	std::vector<map_space*> open = std::vector<map_space*>();

	//add initial state to the closed list
	closed.push_back(this->current);
	bool solution = false;

	//beginning part of the algorithm - add neighbors of goal to the open list
	add_neighbors(open, closed, current);

	bool solution_done = false;
	map_space *solved = NULL;

	while (!solution_done)
	{
		//now find out which has lowest h score
		map_space* best_space = NULL;
		int lowest_score = INT_MAX;
		int best_space_index = -1;

		for (int i = 0; i < open.size(); ++i)
		{
			if (open[i]->euclidian_value < lowest_score)
			{
				lowest_score = open[i]->euclidian_value;
				best_space = open[i];
				best_space_index = i;
			}
		}

		//add this to the closed list and remove it from the open list.
		closed.push_back(best_space);
		open.erase(open.begin() + best_space_index);

		if (best_space->is_destination)
		{
			solved = best_space;
			break;
		}

		//add any potential NEW adjacent tiles to the open list
		add_neighbors(open, closed, best_space);
	}

	printf("\nEuclidian - Solved!\n");
	int num_steps = 1;
	int num_nodes = open.size();// +closed.size();

	while (solved != NULL)
	{
		//update path char if it isnt goal or init
		if (solved->space_type != GOAL && solved->space_type != INITIAL)
		{
			solved->board_char = 'o';
			solved->space_type = TRAVELED;
			num_steps++;
		}

		solved = solved->parent;
	}

	print_board();
	printf("Number of steps: %d\nNumber of nodes: %d\n----------------------------------------\n", num_steps, num_nodes);

	//write to file
	write_file("standard_euclidian_output.txt", "Euclidian Solution\n", num_steps, num_nodes);
}

//method for solving astar manhattan
void board_space::solve_a_star_manhattan()
{
	//start at initial state
	map_space* current = this->start;
	this->start->move_value = 0;

	std::vector<map_space*> closed = std::vector<map_space*>();
	std::vector<map_space*> open = std::vector<map_space*>();

	//add initial state to the closed list
	closed.push_back(this->current);
	bool solution = false;

	//beginning part of the algorithm - add neighbors of goal to the open list
	add_neighbors(open, closed, current);

	bool solution_done = false;
	map_space *solved = NULL;

	while (!solution_done)
	{
		//now find out which has lowest h score
		map_space* best_space = NULL;
		int lowest_score = INT_MAX;
		int best_space_index = -1;

		for (int i = 0; i < open.size(); ++i)
		{
			if (open[i]->manhattan_value < lowest_score)
			{
				lowest_score = open[i]->manhattan_value;
				best_space = open[i];
				best_space_index = i;
			}
		}

		//add this to the closed list and remove it from the open list.
		closed.push_back(best_space);
		open.erase(open.begin() + best_space_index);

		if (best_space->is_destination)
		{
			solved = best_space;
			break;
		}

		//add any potential NEW adjacent tiles to the open list
		add_neighbors(open, closed, best_space);

		bool should_continue = false;
		//check adjacent tiles of this tile that are already on the open list.
		for (int i = 0; i < open.size(); ++i)
		{
			//they have to be neighbors
			if (are_neighbors(best_space, open[i]))
			{
				//its manhattan heuristic, and no diagonal movement, so the cost to move is always just 1
				if (best_space->move_value + 1 < open[i]->move_value)
				{
					//we need to recalc values for this tile
					open[i]->move_value = best_space->move_value + 1;
					open[i]->parent = best_space;
				}
			}
		}
	}

	printf("\nA* Manhattan - Solved!\n");
	int num_steps = 1;
	int num_nodes = open.size();// +closed.size();
	while (solved != NULL)
	{
		//update path char if it isnt goal or init
		if (solved->space_type != GOAL && solved->space_type != INITIAL)
		{
			solved->board_char = 'o';
			solved->space_type = TRAVELED;
			num_steps++;
		}

		solved = solved->parent;
	}

	print_board();
	printf("Number of steps: %d\nNumber of nodes: %d\n----------------------------------------\n", num_steps, num_nodes);

	//write to file now
	write_file("a_star_manhattan_output.txt", "A* Manhattan Solution\n", num_steps, num_nodes);
}

//method for solving astar euclidian
void board_space::solve_a_star_euclidian()
{
	//start at initial state
	map_space* current = this->start;
	this->start->move_value = 0;

	std::vector<map_space*> closed = std::vector<map_space*>();
	std::vector<map_space*> open = std::vector<map_space*>();

	//add initial state to the closed list
	closed.push_back(this->current);
	bool solution = false;

	//beginning part of the algorithm - add neighbors of goal to the open list
	add_neighbors(open, closed, current);

	bool solution_done = false;
	map_space *solved = NULL;

	while (!solution_done)
	{
		//now find out which has lowest h score
		map_space* best_space = NULL;
		int lowest_score = INT_MAX;
		int best_space_index = -1;

		for (int i = 0; i < open.size(); ++i)
		{
			if (open[i]->euclidian_value < lowest_score)
			{
				lowest_score = open[i]->euclidian_value;
				best_space = open[i];
				best_space_index = i;
			}
		}

		//add this to the closed list and remove it from the open list.
		closed.push_back(best_space);
		open.erase(open.begin() + best_space_index);

		if (best_space->is_destination)
		{
			solved = best_space;
			break;
		}

		//add any potential NEW adjacent tiles to the open list
		add_neighbors(open, closed, best_space);

		bool should_continue = false;
		//check adjacent tiles of this tile that are already on the open list.
		for (int i = 0; i < open.size(); ++i)
		{
			//they have to be neighbors
			if (are_neighbors(best_space, open[i]))
			{
				//its manhattan heuristic, and no diagonal movement, so the cost to move is always just 1
				if (best_space->move_value + 1 < open[i]->move_value)
				{
					//we need to recalc values for this tile
					open[i]->move_value = best_space->move_value + 1;
					open[i]->parent = best_space;
				}
			}
		}
	}

	printf("\nA* Euclidian - Solved!\n");
	int num_steps = 1;
	int num_nodes = open.size();// +closed.size();

	while (solved != NULL)
	{
		//update path char if it isnt goal or init
		if (solved->space_type != GOAL && solved->space_type != INITIAL)
		{
			solved->board_char = 'o';
			solved->space_type = TRAVELED;
			num_steps++;
		}

		solved = solved->parent;
	}

	print_board();
	printf("Number of steps: %d\nNumber of nodes: %d\n----------------------------------------\n", num_steps, num_nodes);

	//write to file
	write_file("a_star_euclidian_output.txt", "A* Euclidian Solution\n", num_steps, num_nodes);
}

//method for writing to file
void board_space::write_file(const char* file_name, char* header, int num_steps, int num_nodes)
{
	std::ofstream outputFile(file_name);
	outputFile << header;

	for (int col = 0; col < n; ++col)
	{
		for (int row = 0; row < n; ++row)
		{
			outputFile << board[col][row]->board_char << " ";
		}

		outputFile << "\n";
	}

	outputFile << "Number of steps: " << num_steps << "\n";
	outputFile << "Number of nodes: " << num_nodes << "\n";

	outputFile.flush();
	outputFile.close();
}