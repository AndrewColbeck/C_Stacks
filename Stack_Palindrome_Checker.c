// This program will store an array characters in a stack
// and use strcmp() function to determine if the stored word
// is a palindrome.
// By Andrew Colbeck

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//--------------------------//
//		**STRUCTURES**		//
//--------------------------//

struct stack
{
	//Self-referencing structure
	char letter; 
	struct stack *next; 
};
typedef struct stack stack;
typedef stack *stackPtr;
char str2[20];
	//Global character array str2

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
	char str1[20];
	int i, len=0;

	printf("\n\nWelcome to the Palindrome checker.\n");
	printf("Please enter a word to check:\n");


	gets(str1);
		//stores entered characters into str1 array
	len = strlen(str1);
		//Calculates the length of the entered string, stores in len
		//This function is part of the string.h header.

    push_pop(stackPtr, &str1[0], len);
    //Calls a function that will push str1 into a stack,
    //see function for detailed notes

	printf("The word is %s\n", str1);

	if (strcmp(str1, str2) == 0)
		// Compare the two strings, respond accordingly
		printf("This is a Palindrome.\n\n");
	else
		printf("It is not a Palindrome.\n\n");
}


//--------------------------//
//		**FUNCTIONS**		//
//--------------------------//

void push_pop(stackPtr startPtr, char *a, int len)
{
	//This function pushes an array into a stack,
	//Copies the stack into a new array (str2),
	//then pops the stack elements to free memmory.

	stackPtr newPtr;
	stackPtr tempPtr;
	int i = 0;
	char popvalue;

	while (len > 0)
	{
		//while loop to store array into stack

		newPtr = malloc(sizeof(stack));
			//Allocate new memmory slot for stack element
		newPtr->letter = *a;
			//stores the value at a[0] into the stack
		newPtr->next = startPtr;
			//if startPtr = NULL, end of list
			//else (see next line)
		startPtr = newPtr;
			//newPtr element becomes start of list (startPtr)
		a++;
			//increment array address by 1*size-of(integer)
		len--;
			//Decrement the value which denotes the length of the array
	}

	while (startPtr != NULL)
	{
		tempPtr = startPtr;
			//assign tempPtr to top/bottom of stack
		popvalue = startPtr->letter;
			//assign variable to value for processing
		str2[i] = popvalue;
			//in this case, the popvalue is copied into str2 array
		i++;
			//i used to reference element number in str2 (see above)
		startPtr = startPtr->next;
			//If startPtr = NULL, list is over, else repeat.
		free(tempPtr);
			//Free the memmory allocation (pop) the element.
	}
}