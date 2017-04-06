#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
// MODIFY FOR NEW OP
// Operator codes.
#define ADD 0
#define SUB 1
#define MLT 2
#define DIV 3
#define UNM 4
#define LPN 5
#define RPN 6
#define EXP 7
#define FAC 8
#define SIN 9
#define COS 10
#define TAN 11
#define CSC 12
#define SEC 13
#define COT 14
#define UNK -1

// MODIFY FOR NEW OP CHARS
// Operator chars.
#define ADD_CHAR '+'
#define SUB_CHAR '-'
#define MLT_CHAR '*'
#define DIV_CHAR '/'
#define UNM_CHAR '-'
#define LPN_CHAR '('
#define RPN_CHAR ')'
#define EXP_CHAR '^'
#define FAC_CHAR '!'

// Other useful char defines.
// Space character
#define SPC ' '
// Newline character
#define NEWLINE '\n'
#define PI 3.14159265358979323846264338327950288419716939937510582097494459230781640628

// MODIFY FOR NEW TOKEN TYPE
#define OP 0
#define NUM 1
#define ERR 2
#define END 3 



class Tokenizer {
  public:
    // Constructor. Set token_type to NUM, end to false, unary_minus to
    // true.
    Tokenizer();

    // Prompt for expression.
    void prompt() const;

    // Get next token from input stream.
    void next();

	void nextnoignore();

    // Return token type of most recently read token. NUM - number, OP -
    // operator, ERR - error, END - end of input, use define token type
    // codes at top of this file
    int type() const;

    // Return most recently read number.
    double num_read() const;

    // Return most recently read op code. Return op code as defined at top
    // of this file.
    int op_read() const;

    // Return true if end of input encountered.
    bool end_of_stream() const;
    
    // Reset get token to initial conditions.
    void reset();

  private:

    // Set to:  NUM - number, OP - operator, ERR - error, END - end of
    // input, for most recently read token, uses define token type codes at
    // top of this file
    char token_type;

    // Contains the op code of the most recent operator read from stream.
    // Negative if unrecognized.
    int op;

    // Contains the most recent number read from stream.
    double num;

    // True if new line encountered indicating end of stream.
    bool end;

    // True if next '-' character should be treated as a unary minus.
    bool unary_minus;

    // Return op code of operator starting with char, negative if
    // unrecognized operator.  Must be consistent with OP codes at top of
    // this file.
    int op_code(char); 

    // Eat whitespaces. Cleans the expression string of leading spaces.
    void eat_spaces() const;
    
};


#endif
