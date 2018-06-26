/*
 * stack.c
 * (©) 2018 Brandon Doyle <bjd2385@aperiodicity.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "stack.h"

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>

Stack* 
createStack(int size)
{
    Stack *stck;
    stck = malloc(sizeof(Stack));
    stck->count = 0;
    stck->size = size;
    stck->contents = malloc(size * sizeof(char));
    memset(stck->contents, 0, size);
    return stck;
}

void
destroyStack(Stack* stack)
{
    free(stack->contents);
    free(stack);
}

bool
isEmpty(Stack* stack)
{
    return stack->count == 0;
}

bool
isFull(Stack* stack)
{
    return stack->count == stack->size;
}

void
push(Stack* stack, char character)
{
    // Push a character onto the stack
    stack->contents[stack->count] = character;
    stack->count++;
}

bool
safepush(Stack* stack, char character)
{
    // If the stack is full, return false; else, return true
    if (isFull(stack)) {
        return false;
    } else {
        push(stack, character);
        return true;
    }
}

void
safeExpandPush(Stack* stack, char character)
{
    // If the stack is full, double the usable heap
    if (isFull(stack)) {
        char* new_heap = malloc(stack->size * 2 * sizeof(char));
        int i;
        for (i = 0; i < stack->size; ++i)
            new_heap[i] = stack->contents[i];
        free(stack->contents);
        stack->contents = new_heap;
        stack->size <<= 1;
    }
    push(stack, character);
}

char
pop(Stack* stack)
{
    // Pop a value off the stack.
    char value = stack->contents[stack->count];
    stack->contents[stack->count] = 0;  // overwrite data (optional)
    stack->count--;
    return value;
}

int
main(int argc, char **argv)
{
    Stack* stack = createStack(5);
    printf("Size: %d\n", stack->size);
    int i, current_size = stack->size;
    for (i = 0; i < current_size + (current_size / 2); ++i) 
        safeExpandPush(stack, 'a');
    printf("Size: %d\n", stack->size);
    for (i = 0; i < stack->size; ++i) {
        char character = stack->contents[i];
        if (character == 0)
            printf("Em ");
        else
            printf("%c ", character);
    }
    printf("\n");
    destroyStack(stack);
    return 0;
}
