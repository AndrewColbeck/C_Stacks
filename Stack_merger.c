//This program will merge two ordered stacks of integers
//into a single stack, by Andrew Colbeck


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//--------------------------//
//		**STRUCTURES**		//
//--------------------------//
struct stack
{
	//Self referential Structure
	int value; 
	struct stack *next; 
};
typedef struct stack stack;
typedef stack *stackPtr;


//--------------------------//
//		**PROTOTYPES**		//
//--------------------------//

stackPtr push(stackPtr topPtr, int *a, int len);
stackPtr merge(stackPtr stackAPtr, stackPtr stackBPtr);
void print_stack(stackPtr startPtr);
void pop(stackPtr StackPtr);


//--------------------------//
//		**MAIN PROGRAM**	//
//--------------------------//

int main()
{

	stackPtr stackAPtr = NULL;
	stackPtr stackBPtr = NULL; 
	stackPtr stackCPtr = NULL;
	//3 stack pointers, 
	//stackC will be the merged list

	int a[5]={0}, i, j, hold;

	printf("\n\nThis Program will merge two lists of integers stored in stacks.\n");
	printf("Please enter 5 random numbers separated by the enter key:\n");

	for (i = 0; i < 5; i++)
		scanf("%i", &a[i]);
		//Read integers into an array

	for (i = 0; i < 5; i++)
	{
		//Simple for loop to order the list in ascending
		for (j = 0; j < 5; j++)
			if (a[i]<a[j])
			{
				hold = a[i];
				a[i] = a[j];
				a[j] = hold;
			}
	}

	stackAPtr = push(stackAPtr, &a[0], 5);
		//Calls a function to push each value in the array
		//into a newly created stack

	printf("Great!\nNow enter 5 more random numbers:\n");

	for (i = 0; i < 5; i++)
		scanf("%i", &a[i]);
		//Read in Integers into an Array

	for (i = 0; i < 5; i++)
	{
		//Simple for loop to order the list in ascending
		for (j = 0; j < 5; j++)
			if (a[i]<a[j])
			{
				hold = a[i];
				a[i] = a[j];
				a[j] = hold;
			}
	}

	stackBPtr = push(stackBPtr, &a[0], 5);
	stackCPtr = merge(stackAPtr, stackBPtr);
		//Merge function will combine the (already ordered) stacks

	print_stack(stackCPtr);
	pop(stackCPtr);
		//Pops all stack values in stack C to free memmory
}


//--------------------------//
//		**FUNCTIONS**		//
//--------------------------//

stackPtr push(stackPtr topPtr, int *a, int len)
{
	//This function will push a referenced array 
	//into a newly created stack
	stackPtr newPtr;
	stackPtr tempPtr;
	int i = 0;


	while (len > 0)
	{
		newPtr = malloc(sizeof(stack));
		newPtr->value = *a;
		newPtr->next = topPtr;
		topPtr = newPtr;
		a++;
		//increments the array pointer
		len--;
		//decrements the length of supplied array
	}

	return topPtr;
}

stackPtr merge(stackPtr stackAPtr, stackPtr stackBPtr)
{
	//Function to merge two stacks passed by reference
	stackPtr topPtr = NULL;
	stackPtr newPtr;
	stackPtr tempPtr;


	while (stackAPtr != NULL)
	{
		newPtr = malloc(sizeof(stack));
		newPtr->value = stackAPtr->value;
		//Assign value from Stack A into new Stack slot
		newPtr->next = topPtr;
		//if top is NULL, end of list, else the address of
		//the following slot in Stack A will be stored in 
		//the '->next' element of the newly malloc'd stack
		topPtr = newPtr;
		//Assigns topPtr to final element, when NULL is reached,
		//the stack has been completely copied.
		stackAPtr = stackAPtr->next;

	}

	pop(stackAPtr);
		//Free all Stack A elements from memmory

	while (stackBPtr != NULL)
	{
		//Same as previous while loop but with Stack B
		//topPtr references Stack A, merging the two.
		newPtr = malloc(sizeof(stack));
		newPtr->value = stackBPtr->value;
		newPtr->next = topPtr;
		topPtr = newPtr;
		stackBPtr = stackBPtr->next;

	}

	pop(stackBPtr);
		//Free Stack B from memmory

	return topPtr;
}

void print_stack(stackPtr startPtr)
{
	//Function to print a stack passed by reference
	stackPtr tempPtr;

	printf("The Stack Values are:\n");

	while (startPtr != NULL)
		{
			tempPtr = startPtr;
			printf("%d->", startPtr->value);
			startPtr = startPtr->next;
		}
	printf("NULL\n");
}

void pop(stackPtr startPtr)
{
	stackPtr tempPtr;
	while (startPtr != NULL)
	{
		tempPtr = startPtr;
		startPtr = startPtr->next;
		free(tempPtr);
			//free function (found in stdlib.h)
			//instructs the compiler to release 
			//the referenced memmory slot for re-use.
	}
}