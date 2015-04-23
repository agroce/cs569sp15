

#include <stdio.h>
#include <string.h>  /* for strlen() */
#include <assert.h>
#include "stack.h"


int nondet_int();
unsigned int nondet_unsigned_int();
char nondet_char();


int main(void)
{
   // int size;
    //__CPROVER_assume(size = 10);
    
 //  __CPROVER_assume (SIZE == 10);
   int i;
   char v;
    stackT stack;    /* A stack to hold characters. */
    char str[SIZE];   /* String entered by user. */
    char *traverse;  /* Pointer used to traverse the string. */
    
    unsigned int s = nondet_unsigned_int();
    __CPROVER_assume (s <= SIZE);
    
    
    for(i = 0; i <= s; i++)
    {
        v = nondet_char();
        printf("LOG: str[%d] = %c \n", i, str[i]);
        str[i] = v;
    }
    
     
    /*
     * Initialize the stack.  Make it at least
     * big enough to hold the string we read in.
     */
    StackInit(&stack, strlen(str));
    
    /*
     * Traverse the string and put each
     * character on the stack.
     */
    

    
    for (traverse = str; *traverse != '\0'; traverse++) {
     printf("LOG: str after calling StackInit = %c\n", str);
     printf("traverse = %c", traverse);
    
        StackPush(&stack, *traverse);
    }
   
    /*
     * Pop each of the characters off of
     * the stack and print them out.
     */
    
    //printf("\nLOG: Popped characters are: \n");
    
    while (!StackIsEmpty(&stack)) {
         printf("\nLOG: Popped characters are: \n");
        printf("%c", StackPop(&stack));
    }
    
    printf("\n");
    
    StackDestroy(&stack);

     if (StackIsEmpty(&stack)== 1) // checks whether the stack is empty or not 
        {
            assert(StackPop(&stack) == NULL); // if yes, do not allow pop
        }
    
   
}
