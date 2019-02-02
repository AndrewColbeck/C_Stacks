// (Reversing the Words of a Sentence) 
//This program takes text input 
//and uses a stack to print the input back out reversed

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//--------------------------//
//		**STRUCTURES**		//
//--------------------------//


struct stack
{
	//Self-referencial Structure
	char letter; 
	struct stack *next; 
};
typedef struct stack stack; 
typedef stack *stackPtr;

//--------------------------//
//		**PROTOTYPES**		//
//--------------------------//
void push_pop(stackPtr startPtr, char *a, int len);


//--------------------------//
//		**MAIN PROGRAM**	//
//--------------------------//
int main()
{

	stackPtr stackPtr = NULL;
	char str[20];
	int len=0;

	printf("Please enter a sentence:\n");
	gets(str);
		//gets() function (found in string.h header),
		//reads in a string

	len = strlen(str);
		//strlen() function calculates the length of a string,
		//also found in string.h header

    push_pop(stackPtr, &str[0], len);
    	//push_pop function will push an array into a stack
}


//--------------------------//
//		**FUNCTIONS**		//
//--------------------------//

void push_pop(stackPtr startPtr, char *a, int len)
{
	//Function to push a string array into a stack,
	//Then pops the elements while printing the stored values

	stackPtr newPtr;
	stackPtr tempPtr;

	char popvalue;

	while (len > 0)
	{
		//while loop to create a new stack element
		newPtr = malloc(sizeof(stack));
		newPtr->letter = *a;
		newPtr->next = startPtr;
			//If startPtr = NULL, end of list (else see below)
		startPtr = newPtr;
			//This element becomes the start element of the list
		a++;
			//Array pointer is incremented
		len--;
			//Len (denoting the length of the string) is decremented
	}

	printf("The sentence in reverse order is:\n");

	while (startPtr != NULL)
	{
		tempPtr = startPtr;
		popvalue = startPtr->letter;
		printf("%c", popvalue);
		startPtr = startPtr->next;
			//If startPtr becomes NULL, list is over
		free(tempPtr);
			//Pops the stored memmory allocation for re-use by compiler
	}

	printf("\n");
}
