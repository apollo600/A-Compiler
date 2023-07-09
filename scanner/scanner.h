#ifndef _SCANNER_H_
#define _SCANNER_H_

typedef enum {
    AND, OR,
    EQ, NE, LE, GE,
    VOID, INT,
    IF, ELSE, WHILE, BREAK, CONTINUE, RETURN,
    NUMBER, IDENT
} TokenType;

#endif