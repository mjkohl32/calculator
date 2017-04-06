#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <stack>
#include "Tokenizer.h"

using namespace std;

// Global precedence const array, uses op defines in Tokenizer.h
// Set this to the total number of operators.
#define PREC_DIM 15
static const bool prec[PREC_DIM][PREC_DIM] =
{          /* ADD SUB MLT DIV UNM LPN RPN EXP FAC    TRIG*/ 
	/* ADD */{ 0,  0,  0,  0,  0,  1,  0 , 0,  0, 0,0,0,0,0,0},
	/* SUB */{ 0,  0,  0,  0,  0,  1,  0 , 0,  0, 0,0,0,0,0,0},
	/* MLT */{ 1,  1,  0,  0,  0,  1,  0 , 0,  0, 0,0,0,0,0,0},
	/* DIV */{ 1,  1,  0,  0,  0,  1,  0 , 0,  0, 0,0,0,0,0,0},
	/* UNM */{ 1,  1,  1,  1,  1,  1,  0 , 1,  1, 1,1,1,1,1,1},
	/* LPN */{ 1,  1,  1,  1,  1,  1,  0 , 1,  1, 1,1,1,1,1,1},
	/* RPN */{ 0,  0,  0,  0,  0,  1,  0 , 0,  0, 0,0,0,0,0,0},
	/* EXP */{ 1,  1,  1,  1,  1,  1,  0 , 0,  0, 0,0,0,0,0,0},
	/* FAC */{ 1,  1,  1,  1,  1,  1,  0 , 1,  0, 0,0,0,0,0,0},
	/* SIN */{ 0,  1,  1,  1,  1,  1,  0 , 1,  1, 0,0,0,0,0,0},
	/* COS */{ 1,  1,  1,  1,  1,  1,  0 , 1,  1, 0,0,0,0,0,0},
	/* TAN */{ 1,  1,  1,  1,  1,  1,  0 , 1,  1, 0,0,0,0,0,0},
	/* CSC */{ 1,  1,  1,  1,  1,  1,  0 , 1,  1, 0,0,0,0,0,0},
	/* SEC */{ 1,  1,  1,  1,  1,  1,  0 , 1,  1, 0,0,0,0,0,0},
	/* COT */{ 1,  1,  1,  1,  1,  1,  0 , 1,  1, 0,0,0,0,0,0}
};

class Evaluator {
public:
	// Constructor. Set error flag to false.
	Evaluator();

	// Push a number onto the num stack.
	void num(double);

	// Evaluate an operator.
	void op(int);

	// Finish remaining ops, return result.
	double finish();

	// Reset stacks, error.
	void reset();

	// Returns current value of error
	bool problem();

private:
	// Error flag.
	bool error;
	// Compare top op to incoming op, if incoming op is of higher
	// precedence (check prec[inc][top] of table), return true, otherwise
	// return false.
	bool push_op(int inc, int top);
	// Execute the top operator on the op stack, set error to true if
	// necessary.
	void execute_op();
	// Op stack
	stack<int> ops;
	// Num stack
	stack<double> nums;
};

#endif