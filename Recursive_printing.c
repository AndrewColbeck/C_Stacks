// The Purpose of this Program is to recursively
// call a function which prints a list in reverse order
// By Andrew Colbeck

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//---------------------------------
//			** STRUCTURES **
//---------------------------------

struct sample {
	int letter;
	struct sample *next;
};

//---------------------------------
//			** PROTOTYPES **
//---------------------------------

void printList (struct sample* list1);
void printReverse(struct sample* list1);


//---------------------------------
//			** MAIN PROGRAM **
//---------------------------------

int main(){
	struct sample *list1, *head;
	int i;

	head=NULL;

		for (i = 68; i >= 65; i--)
	{
		//This loop creates a small set of letters in
		//a Linked list, ASCII values 68(D)->67(C)->66(B)->65(A) 
		list1 = malloc(sizeof(struct sample));
		list1->letter = i;
		list1->next = head;
		head = list1;
	}

	printf("List 1 is:\n");
	printList(list1);

	printf("List in reverse order:\n");
	printReverse(list1);
	printf("NULL\n");
}

//---------------------------------
//			** FUNCTIONS **
//---------------------------------

void printList (struct sample* list1)
{
	//Function to print a passed list
	while (list1 != NULL){
		printf("%c->", list1->letter);
		list1=list1->next;
	}
	printf("NULL\n");
}

void printReverse(struct sample* list1)
{
	//Function to recursively print a list
	if (list1 == NULL)
		//When NULL is reached, exit current recurrence
		return;

	printReverse(list1->next);
		//Only when NULL causes the above recurrence to return,
		//The function can reach the next step:
	printf("%c->", list1->letter);
		//All recurrences will print the character from the top
		//of the stack, i.e. list1->letter "D" will release first
}

