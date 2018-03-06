#include "board_evaluator.h"

board_evaluator::board_evaluator(eval_type evaluation_method)
{
	this->eval_method = evaluation_method;
}

board_evaluator::~board_evaluator()
{

}

void board_evaluator::switch_evaluation_method(eval_type new_method)
{
	this->eval_method = new_method;
}

void board_evaluator::evaluate(board_space board)
{

}