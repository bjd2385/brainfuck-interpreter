/*
 * bf.c
 * © 2018 Brandon Doyle <bjd2385@aperiodicity.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

#include "bf.h"


extern int yylex();
extern int yylineno;
extern char *yytext;


// Stack structure for keeping track of open brackets
typedef struct BracketStack
{
    int top;
    unsigned size;
    int *brackets;
};


BracketStack *
createStack(void)
{
    BracketStack *stack = malloc(sizeof(BracketStack));
    stack->top = -1;
    stack->size = MEMORY_SIZE; 
    stack->brackets = malloc(stack->size * sizeof(BracketStack));
    return stack;
}


bool
isFull(BracketStack *stack)
{
    return stack->top == stack->size - 1;
}


bool
isEmpty(BracketStack *stack)
{
    return stack->top == -1;
}


int
retToken(int num)
{
    return *names[num];
}


// Parser
int 
main(int argc, char *argv[])
{
    int nametoken, valuetoken;
    nametoken = yylex();
    BracketStack *brackets = createStack();

    char *names[] = { 
        NULL, "RCARROT", "LCARROT", "INC", "DEC", "LBRACKET", "RBRACKET", 
        "INPUT", "OUTPUT"
    };

    while (nametoken)
    {
        printf("%d\n", nametoken);

        // Using a stack datastructure, ensure there is a closing bracket
        // for every opening bracket.
        if (nametoken == LBRACKET) {
            brackets.push(nametoken);

        } else if (nametoken == RBRACKET) {
            brackets.pop(nametoken);
        }

        nametoken = yylex();    // get next token
    }

    return 0;
}
