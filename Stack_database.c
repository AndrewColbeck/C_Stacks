// This Program allows the user to edit and store
// records in a database, as an example of Stack logic
// By Andrew Colbeck 2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#define recordsfile "records.txt"
#define records_sorted "records_sorted.txt"
#define records_stack "records_stack.txt"
#define SIZE 3

bool sorted = false;

//---------------------------------------------------
//					**** STRUCTURES ****
//---------------------------------------------------
typedef struct record
{
  char name[20];
  int id;
  float num;
}record;


typedef struct stackNode
{
	char name[20];
	int id;
	float num;
	struct stackNode *nextPtr;
}stackNode;
typedef stackNode *stackNodePtr;


typedef struct linkedList
{
	char name[20];
  	int id;
  	float num;
  	struct linkedList *next;
}linkedList;
typedef linkedList *linkedListPtr;


//---------------------------------------------------
//					**** PROTOTYPES ****
//---------------------------------------------------

// RECORD KEEPING
int displayMenu();
void getDetail(record *records, int size);
void printDetail(record *records, int size);
FILE *copyToTextFile(record *records, FILE *fp1);
void readFromTextFile(FILE *fp1, record *records);
void printFromTextFile(FILE *fp1);

// SORTING AND SEARCHING
void bubbleSort(record *a, int array_size, int flow, int elementType);
void selectionSort(record *a, int array_size, int flow, int elementType);
void sort(FILE *fp1, FILE *fp2);
int linearSearch(FILE *fp1, int key);
int binarySearch(FILE *fp1, int searchKey, int low, int high);
void search(FILE *fp1, FILE *fp2);	

// STACK AND LINKEDLIST FUNCTIONS
void push(stackNodePtr *topPtr, char *name, int id, float num);
void printStack(stackNodePtr currentPtr);
int isEmpty(stackNodePtr topPtr);
void searchStack(stackNodePtr currentPtr, int key, char *name, int option);
void copyStackToFile(stackNodePtr currentPtr, FILE *fp1);
void copyFileToStack(FILE *fp1, stackNodePtr currentPtr);
stackNodePtr reverse(stackNodePtr *topPtr);
void stackInsert(FILE *fp1, FILE *fp2);
void printList (linkedListPtr list1);
linkedListPtr insertLink(linkedListPtr *startPtr, char *name, int id, float num);
linkedListPtr listInsert(FILE *fp1);




//---------------------------------------------------
//					**** MAIN PROGRAM ****
//---------------------------------------------------
int main()
{
	int i = 1, answer, option, key;
	record records[SIZE];
	FILE *fp1;
	FILE *fp2;
	FILE *fp3;
	linkedListPtr list = NULL;

	printf("\nWelcome to the Record Keeping Program.\n");
	printf("Enter -1 to quit.\n\n");

	// GET RECORD DETAILS:
	getDetail(records, SIZE);
	fp1 = fopen (recordsfile, "w");
	fp1 = copyToTextFile(records, fp1);
	fclose(fp1);

	// DISPLAY MENU:
	do
	{
		option = displayMenu();
		switch (option)
		{
			case 1: // SORT THE ARRAY
				fp1 = fopen (recordsfile, "r");
				fp2 = fopen (records_sorted, "w");
				fp3 = fopen (records_stack, "w");
	 			sort(fp1, fp2);
	 			fclose(fp1);
	 			fclose(fp2);
	 			sorted = true;
	 			option = 0;
	 			break;
			case 2: // SEARCH FOR INT
				fp1 = fopen (recordsfile, "r");
				fp2 = fopen (records_sorted, "w");
				search(fp1, fp2);
				fclose(fp1);
				fclose(fp2);
	 			option = 0;
	 			break;
	 		case 3: // INSERT ARRAY INTO A STACK
				fp1 = fopen (recordsfile, "r");
				fp3 = fopen (records_stack, "w");
	 			stackInsert(fp1, fp3);
	 			fclose(fp1);
				fclose(fp3);
	 			option = 0;
	 			break;
	 		case 4: // INSERT ARRAY INTO LINKED LIST
	 				bubbleSort(records, SIZE, 2, 2);
	 				//Sorts in descending so list is in asc.
	 				fp1 = fopen (recordsfile, "w");
	 				fp1 = copyToTextFile(records, fp1);
	 				fclose(fp1);
	 				// linkedListPtr listInsert(FILE *fp1)
	 				fp1 = fopen (recordsfile, "r");
	 				list = listInsert(fp1);
	 				fclose(fp1);
	 			option = 0;
	 			break;
	 		case 5: // INSERT NEW LINK INTO LINKED LIST
	 			printf("Enter new Record Details:\n");
	 			getDetail(records, 1);
	 			list = insertLink(&list, records[0].name, records[0].id, records[0].num);
	 			printList(list);

	 			option = 0;
	 			break;
	 		case 6: // QUIT
	 			
	 			option = -1;
	 			break;


			default: printf("Invalid Option, please enter a number:");
				break;
		}
	}while(option !=-1);
	
}


//---------------------------------------------------
//					**** FUNCTIONS ****
//---------------------------------------------------

int displayMenu()
{
	int option=0;
	printf("Please Select an Option from the following:\n");
	printf("1: Sort the Array\n");
	printf("2: Search for an ID (int element)\n");
	printf("3: Insert Array into Stack\n");
	printf("4: Insert Array elements (must be sorted first) into a linked list\n");
	printf("5: Insert one more structure into the linked list\n");
	printf("6: Quit\n");
	scanf("%i", &option);
	return option;
}

void getDetail(record *records, int size)
{
	int i;
	char temp_name[20];
	int temp_id;
	float temp_num;

	for (i = 0; i < size; i++)
	{
		printf("Enter details for Record No. %i\n", i+1);
		printf("Name: ");
		scanf("%s", temp_name);
		if (strcmp(temp_name, "-1") == 0)
			break;
		strcpy(records[i].name, temp_name);
		printf("ID No.: ");
		scanf("%i", &temp_id);
		if (temp_id == -1)
			break;
		records[i].id = temp_id;
		printf("Floating Point No.: ");
		scanf("%f", &temp_num);
		if (temp_num == -1)
			break;
		records[i].num = temp_num;
	}
}

void printDetail(record *records, int size)
{
	int i;
	printf("\nRecord Details:\n");
	for (i = 0; i < size; i++)
	{
		printf("Record No. %i\n", i+1);
		printf("Name: %s\n", records[i].name);
		printf("ID No.: %i\n", records[i].id);
		printf("Floating Point No.: %f\n", records[i].num);
	}
}

FILE *copyToTextFile(record *records, FILE *fp1)
{
	int i;

	if (fp1 == NULL)
	{
		// Error check on file:
		printf("Error in opening file\n");
		return fp1;
	}

	for (i = 0; i < SIZE; i++)
	{
		fprintf(fp1, "%s\t%i\t%f\n", records[i].name, records[i].id, records[i].num);
	}

	return fp1;

}

void readFromTextFile(FILE *fp1, record *records)
{
	int i;
	for (i = 0; i < SIZE; i++)
	{
		// Read results into an array:
		fscanf(fp1, "%s", records[i].name);
		fscanf(fp1, "%i", &records[i].id);
		fscanf(fp1, "%f", &records[i].num);
	}
}

void printFromTextFile(FILE *fp1)
{
	int i;
	record records[SIZE];

	for (i = 0; i < SIZE; i++)
	{
		// Read results into an array:

		fscanf(fp1, "%s", records[i].name);
		fscanf(fp1, "%i", &records[i].id);
		fscanf(fp1, "%f", &records[i].num);
	}

	printf("Information from File is:\n");
	for (i = 0; i < SIZE; i++)
	{
		printf("Record No.: %i\n", i+1);
		printf("Name: %s\n", records[i].name);
		printf("ID No.: %i\n", records[i].id);
		printf("Number: %f\n", records[i].num);
	}
}

void bubbleSort(record *a, int array_size, int flow, int elementType)
{
	int i, j;
	record temp;

	if (flow == 1)
	{
		// SORT IN ASCENDING ORDER:
		for (i = 0; i < (array_size - 1); i++)
		{		
			for (j = 0; j < array_size - 1 - i; j++)
			{

				// NAME SEARCH:
				if (elementType == 1)
				{
					if (a[j].name[0] > a[j+1].name[0])
					{
						temp = a[j+1];
						a[j+1] = a[j];
						a[j] = temp;
					}
				}

				// INT SEARCH:
				if (elementType == 2)
				{
					if (a[j].id > a[j+1].id)
					{
						temp = a[j+1];
						a[j+1] = a[j];
						a[j] = temp;
					}
				}

				// FLOAT SEARCH:
				if (elementType == 3)
				{
					if (a[j].num > a[j+1].num)
					{
						temp = a[j+1];
						a[j+1] = a[j];
						a[j] = temp;
					}
				}
			}
		}
	}

	if (flow == 2)
	{
		// SORT IN DESCENDING ORDER:
		for (i = 0; i < (array_size - 1); i++)
		{		
			for (j = 0; j < array_size - 1 - i; j++)
			{

				// NAME SEARCH:
				if (elementType == 1)
				{
					if (a[j].name[0] < a[j+1].name[0])
					{
						temp = a[j+1];
						a[j+1] = a[j];
						a[j] = temp;
					}
				}

				// INT SEARCH:
				if (elementType == 2)
				{
					if (a[j].id < a[j+1].id)
					{
						temp = a[j+1];
						a[j+1] = a[j];
						a[j] = temp;
					}
				}

				// FLOAT SEARCH:
				if (elementType == 3)
				{
					if (a[j].num < a[j+1].num)
					{
						temp = a[j+1];
						a[j+1] = a[j];
						a[j] = temp;
					}
				}
			}
		}
	}

}

void selectionSort(record *a, int array_size, int flow, int elementType)
{
	int i, j, min;
	record temp;

	if (flow == 1)
	{
		// SORT IN ASCENDING ORDER
		for (i = 0; i < array_size - 1; i++)
		{
			//array_size - 1 is in place to save time, see above note
			min = i;
			//min is the array element number that holds the minimum value
			
			for (j = i+1; j < array_size; j++)
			{
				//start j at element 1, because currently a[min] = a[0],
				//thus it is optimal not to compare two identical values
				
				// NAME SORT:
				if (elementType == 1)
				{
					if (a[j].name[0] < a[min].name[0])
						min = j;
				}

				// INT SORT:
				if (elementType == 2)
				{
					if (a[j].id < a[min].id)
						min = j;
				}

				// FLOAT SORT:
				if (elementType == 3)
				{
					if (a[j].num < a[min].num)
						min = j;
				}
				//min will inevitably hold address of lowest value
			}
			temp = a[i];
			a[i] = a[min];
			a[min] = temp;
			//a[i] will now hold the minimum value.
		}
	}

	if (flow == 2)
	{
		// SORT IN DESCENDING ORDER
		for (i = 0; i < array_size - 1; i++)
		{
			//array_size - 1 is in place to save time, see above note
			min = i;
			//min is the array element number that holds the minimum value
			
			for (j = i+1; j < array_size; j++)
			{
				//start j at element 1, because currently a[min] = a[0],
				//thus it is optimal not to compare two identical values
				
				// NAME SORT:
				if (elementType == 1)
				{
					if (a[j].name[0] > a[min].name[0])
						min = j;
				}

				// INT SORT:
				if (elementType == 2)
				{
					if (a[j].id > a[min].id)
						min = j;
				}

				// FLOAT SORT:
				if (elementType == 3)
				{
					if (a[j].num > a[min].num)
						min = j;
				}
				//min will inevitably NOW hold address of HIGHEST value
			}
			temp = a[i];
			a[i] = a[min];
			a[min] = temp;
			//a[i] will now hold the minimum value.
		}
	}
}

void sort(FILE *fp1, FILE *fp2)
{
	int i;
	int flow, elementType, method;
	record records[SIZE];

	
	if (fp1 == NULL)
	{
		// Error check on file:
		printf("Error in opening file\n");
		return;
	}

	if (fp2 == NULL)
	{
		// Error check on file:
		printf("Error in opening file\n");
		return;
	}

	readFromTextFile(fp1, records);

	printf("Please choose from:\n");
	printf("1. Ascending\n");
	printf("2. Descending\n");
	printf("3. Quit\n");
	scanf("%i", &flow);

	if (flow == 3)
		return;

	printf("Choose which Element to sort by:\n");
	printf("1: Name (String)\n");
	printf("2: ID (Integer)\n");
	printf("3: Number (Float)\n");
	printf("4: Quit\n");
	scanf("%i", &elementType);

	if (elementType == 4)
		return;

	printf("Lastly, which Sorting Algorithm would you like to use:\n");
	printf("1. Bubble Sort\n");
	printf("2. Selection Sort\n");
	printf("3. Quit\n");
	scanf("%i", &method);

	if (method == 3)
		return;

	if (method == 1)
	{
		bubbleSort(records, SIZE, flow, elementType);
	}

	if (method == 2)
	{
		selectionSort(records, SIZE, flow, elementType);
	}

	fp2 = copyToTextFile(records, fp2);
	fclose(fp2);
	fp2 = fopen (records_sorted, "r");
	printFromTextFile(fp2);
	fclose(fp2);

}

int linearSearch(FILE *fp1, int key)
{
	// Linear search will begin comparing elements to
	// the key starting from 0; excellent for searching 
	// unsorted Arrays.
	int i;
	record records[SIZE];

	if (fp1 == NULL)
	{
		// Error check on file:
		printf("Error in opening file\n");
		return -1;
	}

	readFromTextFile(fp1, records);

	for (i = 0; i < SIZE; i++)
	{
		if (records[i].id == key)
		{
			return i;
		}
	}
	return -1;
}

int binarySearch(FILE *fp1, int searchKey, int low, int high)
{
	// Binary Search (Array must be sorted), more efficient
	// than linear search; especially with larger Arrays.
	record records[SIZE];

	if (fp1 == NULL)
	{
		// Error check on file:
		printf("Error in opening file\n");
		return -1;
	}

	readFromTextFile(fp1, records);

	int middle, i;
	while (low <= high)
	{
		middle = (low + high)/2;
		
		if (searchKey == records[middle].id)
		{
			return middle;
		}

		else if (searchKey < records[middle].id)
		{
			// If key is in lower half of array,
			// this if condition will change
			// start and end points to reflect only
			// the first half of the array.
			high = middle - 1;

		}

		else
		{
			// If key was found to be higher than 
			// middle, then start and end points of array
			// are changed to reflect only the second half
			// of the array.

			low = middle + 1;
		}
	}
	return -1;
}

void search(FILE *fp1, FILE *fp2)
{
	int answer, key, result;

	printf("Which ID (Integer) would you like to search for?\n");
	printf("1. Linear\n");
	printf("2. Binary\n");
	scanf("%i", &answer);

	record records[SIZE];

	if (fp1 == NULL)
	{
		// Error check on file:
		printf("Error in opening file\n");
		return;
	}

	readFromTextFile(fp1, records);
	fclose(fp1);
		printf("Enter the search key: ");
		scanf("%i", &key);
		do
		{
			if (answer == 1)
			{
				// LINEAR SEARCH
				fp1 = fopen (recordsfile, "r");
				result = linearSearch(fp1, key);
				fclose(fp1);
			}
			
			if (answer == 2)
			{
				// BINARY SEARCH
				bubbleSort(records, SIZE, 1, 2);
				sorted = true;
				fp2 = copyToTextFile(records, fp2);
				fclose(fp2);
				fp2 = fopen (records_sorted, "r");
				result = binarySearch(fp2, key, 0, (SIZE-1));
			}

			if (result == -1)
			{
				printf("No match found.");
			}

			if (result != -1)
			{
				printf("Match found for ID %i on record %i\n", key, result+1);
				break;
			}

			printf("Enter a new search key (-1 to quit): ");
			scanf("%i", &key);

			if (key == -1)
			{
				break;
			}

		}while(1);
}

void push(stackNodePtr *topPtr, char *name, int id, float num)
{
	stackNodePtr newPtr;
	newPtr = malloc( sizeof( stackNode ));
	
	if ( newPtr != NULL)
	{
		strcpy(newPtr->name, name);
		newPtr->id = id;
		newPtr->num = num;
		newPtr->nextPtr = *topPtr;
		*topPtr = newPtr;
	}
	else  
	{
		printf( "%i not inserted. No memory available.\n", id);
	}
} 

void printStack( stackNodePtr currentPtr )
{
	int i=1;
	stackNodePtr topPtr;
	topPtr = currentPtr;
	if ( currentPtr == NULL )
	{
		puts( "The stack is empty.\n" );
	} 
	else
	{
		puts( "Records in stack are:\n" );

		while ( currentPtr != NULL )
		{
			printf("Stack Node %i\n", i);
			printf( "Name: %s\n", currentPtr->name);
			printf("ID No.: %i\n", currentPtr->id);
			printf("Float No.: %f\n", currentPtr->num);
			printf("---------------\n");
			i++;
			currentPtr = currentPtr->nextPtr;
		}
	}
	currentPtr = topPtr;
}

int isEmpty(stackNodePtr topPtr)
{
	return topPtr == NULL;
}

void searchStack(stackNodePtr currentPtr, int key, char *name, int option)
{
	int i=1;
	stackNodePtr topPtr;
	topPtr = currentPtr;

	while ( currentPtr != NULL )
	{
		if (option == 1)
		{
			// SEARCH FOR INT
			if (currentPtr->id == key)
			{
				printf("Match found, value %i in Stack Node No.: %i\n", key, i);
				return;
			}
		}
	
		if (option == 2)
		{
			// SEARCH FOR NAME
			if (strcmp(currentPtr->name, name) == 0)
			{
				printf("Match found, name %s in Stack Node No.: %i\n", name, i);
				return;
			}
		}
		currentPtr = currentPtr->nextPtr;
		i++;
	}

	currentPtr = topPtr;
	printf("No Match found\n");
	return;
}

void copyStackToFile(stackNodePtr currentPtr, FILE *fp1)
{
	stackNodePtr topPtr;
	topPtr = currentPtr;

	if (fp1 == NULL)
	{
		// Error check on file:
		printf("Error in opening file\n");
		return;
	}

	while (currentPtr != NULL)
	{
		fprintf(fp1, "%s\t%i\t%f\n", currentPtr->name, currentPtr->id, currentPtr->num);
		currentPtr = currentPtr->nextPtr;
	}
	currentPtr = topPtr;
}

void copyFileToStack(FILE *fp1, stackNodePtr currentPtr)
{
	int i;
	stackNodePtr topPtr;
	topPtr = currentPtr;
	record records[SIZE];
	char temp_name[20];
	int temp_id;
	float temp_num;

	if (fp1 == NULL)
	{
		// Error check on file:
		printf("Error in opening file\n");
		return;
	}

	for (i = 0; i < SIZE; i++){
		fscanf(fp1, "%s", records[i].name);
		fscanf(fp1, "%i", &records[i].id);
		fscanf(fp1, "%f", &records[i].num);
	}

	for (i = SIZE; i > 0; i--)
	{
		push(&currentPtr, records[i].name, records[i].id, records[i].num);
	}
	currentPtr = topPtr;
	printStack(topPtr);
}

stackNodePtr reverse(stackNodePtr *topPtr)
{
	//Function to reverse the order of the
	//Elements in a stack, returning
	//Pointer to the (new) beginning of the stack
	stackNodePtr currentPtr, prevPtr, nextPtr;
	currentPtr = *topPtr;
	prevPtr = NULL;

	while (currentPtr != NULL)
	{
		nextPtr = currentPtr->nextPtr;
		currentPtr->nextPtr = prevPtr;
		prevPtr = currentPtr;
		currentPtr = nextPtr;
	}
	*topPtr = prevPtr;
	return *topPtr;
}

void stackInsert(FILE *fp1, FILE *fp2)
{
	int i, option, key;
	char name[20], char_option[2];

	record records[SIZE];
	readFromTextFile(fp1, records);

	stackNodePtr stackPtr = NULL;	

	for (i = 0; i < SIZE; i++)
	{
		push(&stackPtr, records[i].name, records[i].id, records[i].num);
	}

	printf("All Elements have been inserted into a Stack.\n");
	printStack(stackPtr);
	printf("Would you like to search the stack?\n");
	printf("Please select from the following options (-1 to quit):\n");
	printf("1: Search for ID (Integer)\n");
	printf("2: Search for Name (char)\n");
	scanf("%i", &option);

	if (option == -1)
	{
		return;
	}

	if (option == 1)
	{
		printf("Enter the ID No. to search for: ");
		scanf("%i", &key);
	}

	if (option == 2)
	{
		printf("Enter the Name to search for: ");
		scanf("%s", name);
	}

	searchStack(stackPtr, key, name, option);

	printf("Would you like to print the elements in reverse order from a stack onto a separate file? (y or n): ");
	scanf("%s", char_option);

	if (strcmp(char_option, "n") == 0)
	{
		return;
	}

	printStack(stackPtr);
	copyStackToFile(stackPtr, fp2);
	fclose(fp2);
	fp2 = fopen (records_stack, "a");
	stackPtr = reverse(&stackPtr);
	copyStackToFile(stackPtr, fp2);
}

void printList (linkedListPtr list1)
{
	linkedListPtr tempPtr;
	tempPtr = list1;
	//Function to print the passed List
	while (list1 != NULL)
	{
		printf("Record name: %s\n", list1->name);
		printf("ID No.: %i\n", list1->id);
		printf("Number: %f\n", list1->num);
		list1=list1->next;
	}
	list1 = tempPtr;
}

linkedListPtr insertLink(linkedListPtr *startPtr, char *name, int id, float num)
{
	linkedListPtr newPtr;
	linkedListPtr previousPtr; 
	linkedListPtr currentPtr; 

	newPtr = malloc( sizeof( linkedList ));	
	if ( newPtr != NULL )  
	{
		// CHECK IF SPACE AVAILABLE
		strcpy(newPtr->name, name);
		newPtr->id = id;
		newPtr->num = num;
		 
		newPtr->next = NULL; 
		previousPtr = NULL;
		currentPtr = *startPtr;
		
		while ( currentPtr != NULL && id > currentPtr->id)
		{
			// DETERMINE WHERE TO PLACE LINK
			previousPtr = currentPtr; 
			currentPtr = currentPtr->next; 
		} 
		
		if ( previousPtr == NULL )
		{
			// IF NULL IS REACHED, PLACE NODE AT TOP
			newPtr->next = *startPtr;
			*startPtr = newPtr;
		} 
		else   
		{	
			// ELSE, NEW NODE BELONGS BETWEEN CURRENT & PREVIOUS PTR
			previousPtr->next = newPtr;
			newPtr->next = currentPtr;
		} 
	} 
	else
	{
		printf( "%i not inserted. No memory available.\n", id );
	} 
	return *startPtr;
}

linkedListPtr listInsert(FILE *fp1)
{
	int i = 0;
	record records[SIZE];
	linkedListPtr startPtr=NULL;
	linkedListPtr newPtr;
	linkedListPtr currentPtr;
	linkedListPtr nextPtr;
	linkedListPtr previousPtr;
	linkedListPtr tempPtr;	

	readFromTextFile(fp1, records); 
	
	// HEAD OF LIST
	newPtr = (linkedList*)malloc(sizeof(linkedList));
	strcpy(newPtr->name, records[i].name);
	newPtr->id = records[i].id;
	newPtr->num = records[i].num;
	newPtr->next = NULL;
	startPtr = newPtr;

	// // REMAINING LINKS
	for (i = 1; i < SIZE; i++)
	{

	newPtr = (linkedList*)malloc(sizeof(linkedList));	
	strcpy(newPtr->name, records[i].name);
	newPtr->id = records[i].id;
	newPtr->num = records[i].num;
	newPtr->next = startPtr;
	currentPtr=startPtr->next;
	startPtr=newPtr;
	}

	printf("Printing List:\n");
	printList(startPtr);
	return startPtr;
}
