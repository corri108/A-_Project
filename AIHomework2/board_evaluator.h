#pragma once
#include "board_space.h"
#include "eval_type.h"

class board_evaluator
{
public:
	board_evaluator(eval_type evaluation_method);
	void switch_evaluation_method(eval_type new_method);
	void evaluate(board_space board);
	~board_evaluator();
private:
	eval_type eval_method;
};
