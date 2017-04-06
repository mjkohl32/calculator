#include "Evaluator.h"
#include <cmath>
#include <iostream>

// Constructor. Set error flag to false.
Evaluator::Evaluator() {
	error = false;
}

// Push a number onto the num stack.
void Evaluator::num(double number) 
{
	nums.push(number);
}

// Evaluate an operator - do it.
void Evaluator::op(int oper)
{
	if (ops.empty())
		ops.push(oper);
	else if (push_op(oper, ops.top()))
	{
		ops.push(oper);
	}
	else
	{
		if (oper == RPN) {
			while (ops.top() == RPN) {
				execute_op();
				if (problem()) break;
			}
			while (ops.top() != LPN) {
				execute_op();
				if (problem()) break;
			}
		}
		if (!problem()) {
			execute_op();
			if (!ops.empty() && !problem()) {
				while (ops.top() == EXP || ops.top() >= SIN) {
					execute_op();
					if (ops.empty() || problem()) break;
				}
			}
			if (oper != RPN && oper != UNK)
				ops.push(oper);
		}
	}
}

// Finish remaining ops, return result.
double Evaluator::finish() //!
{
	if (nums.empty()) {
		error = true;
		return -1;
	}
	while (!ops.empty())
		execute_op();
	double ret = nums.top();
	nums.pop();
	if (!nums.empty())
	{
		error = true;
	}
	return ret;
}

// Reset stacks, error.
void Evaluator::reset() //!
{
	while (!nums.empty())
		nums.pop();
	while (!ops.empty())
		ops.pop();
	error = false;
}

// Returns current value of error
bool Evaluator::problem() //!
{
	return error;
}

// Compare top op to incoming op, if incoming op is of higher
// precedence (check prec[inc][top] of table), return true, otherwise
// return false.
bool Evaluator::push_op(int inc, int top) //~?
{
	return prec[inc][top]; //is 1 == true? 
}

// Execute the top operator on the op stack, set error to true if
// necessary.
void Evaluator::execute_op() //x what does this do?
{
	if (ops.empty() || nums.empty()) {
		error = true;
	}
	else if (ops.top() < 0) {
		error = true;
	}
	else {
		double t1, t2;

		switch (ops.top())
		{
		case 0: { // Addition
			t1 = nums.top();
			nums.pop();
			if (nums.empty()) {
				error = true;
				break;
			}
			t2 = nums.top();
			nums.pop();
			nums.push(t1 + t2);
			ops.pop();
			break;
		}
		case 1: {// Subtraction
			t1 = nums.top();
			nums.pop();
			if (nums.empty()) {
				error = true;
				break;
			}
			t2 = nums.top();
			nums.pop();
			nums.push(t2 - t1);
			ops.pop();
			break;
		}
		case 2: {// Multiplies
			t1 = nums.top();
			nums.pop();
			if (nums.empty()) {
				error = true;
				break;
			}
			t2 = nums.top();
			nums.pop();
			nums.push(t1 * t2);
			ops.pop();
			break;
		}
		case 3: {// Divides
			t1 = nums.top();
			nums.pop();
			if (nums.empty()) {
				error = true;
				break;
			}
			t2 = nums.top();
			nums.pop();
			nums.push(t2 / t1);
			if (t1 == 0) {
				cout << "Error divided by 0" << endl;
				error = true;
			}
			ops.pop();
			break;
		}
		case 4: // Make minus
		{
			t1 = nums.top();
			nums.pop();
			nums.push(-t1);
			ops.pop();
			break;
		}
		case 5: // Left parenthese
		{
			ops.pop();
			if (!ops.empty()) {
				if (ops.top() == RPN) {
					error = true;
					break;
				}
				if (ops.top() == 4 || ops.top() > 6)
				{
					execute_op();
				}
			}
			break;
		}
		case 6: // Right parenthese
		{
			ops.pop();
			if (ops.empty()) {
				error = true;
				break;
			}
			execute_op();
			break;
		}
		case 7: // Exponent
		{
			t1 = nums.top();
			nums.pop();
			if (nums.empty()) {
				error = true;
				break;
			}
			t2 = nums.top();
			nums.pop();
			nums.push(pow(t2, t1));
			ops.pop();
			break;
		}
		case 8: // Gamma
		{
			t1 = nums.top();
			nums.pop();
			double aval = abs(t1);

			if (!(aval == floor(aval)))
			{
				std::cout << "Warning: Using gamma instead of factorial\n" << t1 << endl;
			}
			nums.push(tgamma(t1 + 1));
			ops.pop();
			break;
		}
		case 9: // SIN
		{
			t1 = nums.top();
			nums.pop();
			nums.push(sin(t1));
			ops.pop();
			break;
		}
		case 10: // COS
		{
			t1 = nums.top();
			nums.pop();
			nums.push(cos(t1));
			ops.pop();
			break;
		}
		case 11: // TAN
		{
			t1 = nums.top();
			nums.pop();
			nums.push(tan(t1));
			ops.pop();
			break;
		}
		case 12: // CSC
		{
			t1 = nums.top();
			nums.pop();
			nums.push(1.0 / sin(t1));
			ops.pop();
			break;
		}
		case 13: // SEC
		{
			t1 = nums.top();
			nums.pop();
			nums.push(1.0 / cos(t1));
			ops.pop();
			break;
		}
		case 14: // COT
		{
			t1 = nums.top();
			nums.pop();
			nums.push(1.0 / tan(t1));
			ops.pop();
			break;
		}
		}
	}
}


