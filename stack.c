/*
 * stack.c
 * (©) 2018 Brandon Doyle <bjd2385@aperiodicity.com>
 *
 * Distributed under terms of the MIT license.
 *
 * A stack for single characters or bytes.
 */

#include "stack.h"

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>


Stack* 
createStack(unsigned size)
{
    Stack *stck;
    stck = malloc(sizeof(Stack));
    stck->count = 0;

    // If `size` is not a power of 2, round down to the nearest power of two
    //if ((size & (size - 1)) != 0) {
    //    // -mlzcnt
    //    //size = __builtin_ia32_lzcnt_u32(size);
    //    size 
    //}

    stck->size = size;
    stck->contents = malloc(size * sizeof(char));
    memset(stck->contents, 0, size);
    return stck;
}

Stack*
createEmptyStack(void)
{
    // Initialize a stack of size 0 (for dynamic allocation)
    return createStack(0);
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
        if (stack->size == 0) {
            char* new_heap = malloc(sizeof(char));
            free(stack->contents);
            stack->contents = new_heap;
            stack->size = 1;
        } else {
            char* new_heap = malloc(stack->size * 2 * sizeof(char));
            memcpy(new_heap, stack->contents, stack->size * sizeof(char));
            free(stack->contents);
            stack->contents = new_heap;
            stack->size <<= 1;
        }   
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

char
retractPop(Stack* stack)
{
    // If the stack's size is less than 1/4 of the allocated heap, realloc
    // to consume less resources
    if (stack->count < stack->size / 4 + 1) {
        unsigned new_size = stack->size / 4 * sizeof(char) + 1;
        char* new_heap = malloc(new_size);
        memcpy(new_heap, stack->contents, new_size);
        free(stack->contents);
        stack->contents = new_heap;
        stack->size = new_size;
    }
    return pop(stack);
}

int
main(int argc, char** argv)
{
    Stack* stack = createEmptyStack();
    destroyStack(stack);

    return 0;
}

//int
//main(int argc, char **argv)
//{
//    Stack* stack = createEmptyStack();
//    printf("Size: %d, Count: %d\n", stack->size, stack->count);
//    int i;
//    //char character;
//
//    for (i = 0; i < 12345; ++i) 
//        safeExpandPush(stack, 'a');
//    printf("Size: %d, Count: %d\n", stack->size, stack->count);
//
//    for (i = 0; i < stack->size; ++i) {
//        stack->contents[i];
//        //if (character == 0)
//        //    printf("Em ");
//        //else
//        //    printf("%c ", character);
//    }
//
//    printf("\n");
//    for (i = 0; i < 12345; ++i) {
//        retractPop(stack);
//    }
//    printf("Size: %d, Count: %d\n", stack->size, stack->count);
//
//    for (i = 0; i < 3; ++i)
//        safeExpandPush(stack, 'a');
//    printf("Size: %d, Count: %d\n", stack->size, stack->count);
//
//
//    destroyStack(stack);
//    return 0;
//}
