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
#include "stack.h"

extern int yylex();
extern int yylineno;
extern char* yytext;

extern Stack* createStack(int size);
extern void destroyStack(Stack* stack);
extern bool isEmpty(Stack* stack);
extern bool isFull(Stack* stack);
extern void safeExpandPush(Stack* stack, char character);
extern char retractPop(Stack* stack);
extern char pop(Stack* stack);

// This is how you define a list of (lists of characters, a.k.a.) strings
char* names[] = { 
    NULL, "RCARROT", "LCARROT", "INC", "DEC", "LBRACKET", "RBRACKET", 
    "INPUT", "OUTPUT"
};

// Convert a token number (as defined in the header file) to a token name
char*
getName(int tokenNumber, char** names)
{
    return names[tokenNumber];
}

// Parser
int 
main(int argc, char *argv[])
{
    int nametoken, valuetoken;
    nametoken = yylex();
    Stack* brackets = createStack(10);

    while (nametoken)
    {
        char* token = getName(nametoken, names);
        printf("%s\n", token);

        // Using a stack datastructure, ensure there is a closing bracket
        // for every opening bracket.
        if (nametoken == LBRACKET) {
            safeExpandPush(brackets, '[');

        } else if (nametoken == RBRACKET) {
            pop(brackets);
        }

        nametoken = yylex();    // get next token
    }

    return 0;
}
