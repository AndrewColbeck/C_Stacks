// The Purpose of this Program is to recursively
// search a list for a value.
// By Andrew Colbeck


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//---------------------------------
//			** STRUCTURES **
//---------------------------------

struct sample {
	int value;
	struct sample *next;
};

//---------------------------------
//			** PROTOTYPES **
//---------------------------------

void printList (struct sample *list1);
struct sample* searchList(struct sample* list1, int find);

//---------------------------------
//			** MAIN PROGRAM **
//---------------------------------

int main(){
	struct sample *list1 = NULL, *head = NULL, *result = NULL;
	int i;
	int find;
	srand(time(NULL));

	for (i = 0; i < 10; i++)
	{
		//This loop creates a random set of integers in
		//a Linked list >1 & <100 
		list1 = malloc(sizeof(struct sample));
		list1->value = rand()%100+1;
		list1->next = head;
		head = list1;
	}

	printf("List 1 is:\n");
	printList(list1);

	printf("Enter a number to search for:\n");
	scanf("%i", &find);

	result = searchList(list1, find);


	if (result != NULL)
		printf("match found: %i\n\n", result->value);

	if (result == NULL)
		printf("No Match found.\n\n");
}

//---------------------------------
//			** FUNCTIONS **
//---------------------------------

void printList (struct sample *list1)
{
	//Function to print a passed list
	while (list1 != NULL){
		printf("%i->", list1->value);
		list1=list1->next;
	}
	printf("NULL\n");

}

struct sample* searchList(struct sample* linkAddress, int find)
{
	//Function to recursively search a list
	struct sample* result = NULL;
	
	if (linkAddress == NULL)
		return NULL;
		//When NULL is reached, exit current recurrence,
		//and begin executing:

	if (linkAddress->value == find)
		return linkAddress;
		//If values match, *result becomes *list address

	result = searchList(linkAddress->next, find);
		//Function recursively launches
	return result;
		//If a match was found, it was stored in result.
		//If no match is found, result returns a NULL,
		//recursively until all recurrences have executed.
}

