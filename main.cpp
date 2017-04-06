#include <iostream>
#include "Tokenizer.h"
#include "Evaluator.h"
using namespace std;

int main() {

	Tokenizer tokes;
	Evaluator Albert;

	while (true) {
		Albert.reset();
		tokes.reset();
		tokes.prompt();
		tokes.nextnoignore();
		if (tokes.type() == END) break;
		while (!tokes.end_of_stream() && tokes.type() != ERR && !Albert.problem()) {
			tokes.next();
			if (Albert.problem())
				break;
			switch (tokes.type()) {
			case NUM: {
				Albert.num(tokes.num_read());
				break;
			}
			case OP: {
				Albert.op(tokes.op_read());
				break;
			}
			case ERR: {
				cout << "Invalid input. Aborting." << endl;
				break;
			}
			case END: {
				double result = Albert.finish();
				if (Albert.problem())
					break;
				cout << "    Result: " << result << endl;
				break;
			}
			}
			if (Albert.problem())
				break;
		}
		if (Albert.problem()) {
			cout << "Invalid input. Aborting." << endl;
		}
	}
}
