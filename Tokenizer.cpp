#include "Tokenizer.h"
#include <iostream>
#include <cmath>
using namespace std;

Tokenizer::Tokenizer() {
	token_type = NUM;
	end = false;
	unary_minus = true;

}

void Tokenizer::prompt() const {
	cout << "Expression: ";
}

void Tokenizer::next() {
	eat_spaces();
	char temp = cin.peek();
	if (('0' <= temp && temp <= '9') || temp == '.') {
		double a;
		cin >> a;
		token_type = NUM;
		unary_minus = false;
		num = a;
	}
	else if (temp == 'p')
	{
		cin.ignore();
		if (cin.peek() == 'i')
		{
			cin.ignore();
			token_type = NUM;
			unary_minus = false;
			num = PI;
		}
		else {
			token_type = ERR;
			while (cin.peek() != NEWLINE)
				cin.ignore();
			cin.ignore();
		}
	}
	else {
		token_type = OP;
		op = op_code(temp);
		unary_minus = true;
		if (temp == RPN_CHAR) {
			unary_minus = false;
		}
		else if (temp == NEWLINE) {
			token_type = END;
			end = true;
		}
		else if (op == UNK)
		{
			token_type = ERR;
			while (cin.peek() != NEWLINE)
				cin.ignore();
		}
		cin.ignore();
	}
}

void Tokenizer::nextnoignore() {
	eat_spaces();
	char temp = cin.peek();
	if (temp == NEWLINE) {
		token_type = END;
		end = true;
	}
}

int Tokenizer::type() const {
	return token_type;
}

double Tokenizer::num_read() const {
	return num;
}

int Tokenizer::op_read() const {
	return op;
}

bool Tokenizer::end_of_stream() const {
	return end;
}

void Tokenizer::reset() {
	token_type = NUM;
	end = false;
	unary_minus = true;
}

int Tokenizer::op_code(char oppi) {
	if (oppi == UNM_CHAR && unary_minus) return UNM;
	switch (oppi) {
	case ADD_CHAR: return ADD;
	case SUB_CHAR: return SUB;
	case MLT_CHAR: return MLT;
	case DIV_CHAR: return DIV;
	case LPN_CHAR: return LPN;
	case RPN_CHAR: return RPN;
	case FAC_CHAR: return FAC;
	case EXP_CHAR: return EXP;
	case 's':
	{
		cin.ignore();
		if (cin.peek() == 'i')
		{
			cin.ignore();
			if (cin.peek() == 'n')
			{
				return SIN;
			}
		}
		else if (cin.peek() == 'e')
		{
			cin.ignore();
			if (cin.peek() == 'c')
			{
				return SEC;
			}
		}
		break;
	}
	case 'c':
	{
		cin.ignore();
		if (cin.peek() == 'o')
		{
			cin.ignore();
			if (cin.peek() == 's')
			{
				return COS;
			}
			else if (cin.peek() == 't')
			{
				return COT;
			}
		}
		else if (cin.peek() == 's')
		{
			cin.ignore();
			if (cin.peek() == 'c')
			{
				return CSC;
			}
		}
		break;
	}
	case 't':
	{
		cin.ignore();
		if (cin.peek() == 'a')
		{
			cin.ignore();
			if (cin.peek() == 'n')
			{
				return TAN;
			}
		}
		break;
	}
	}
	return UNK;
}

void Tokenizer::eat_spaces() const {
	while (cin.peek() == SPC) cin.ignore();
}

