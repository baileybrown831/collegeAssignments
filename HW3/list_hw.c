/* This program uses the name 'link' from code from "Algorithms in C, Third Edition,"
 *               by Robert Sedgewick, Addison-Wesley, 1998.
 * 
 * - Alexandra Stefan
 */

#include <stdio.h>
#include <stdlib.h>

#include "list_hw.h"

// ------------- Node functions

/* Creates a new link, that contains the value specified in the argument, 
 * and that points to next_in. 
 */
link new_node(int value_in,  link next_in) {
    link result = (link) malloc(sizeof (struct node));
    result->data = value_in;
    result->next = next_in;
    return result;
}

/*    --------  LIST functions    */
// List implementation uses a DUMMY NODE

/* Creates and returns an empty list. */
link new_list() {
	link dummy = new_node(0,NULL);
    return dummy;
}

/* Deallocates memory for all nodes in the list and the list object itself. */
void destroy_list(link Ld) {
    link current = Ld;
    while (current != NULL) {
        link next = current->next;
        free(current);
        current = next;
    }    
}

// Inserts new_link after the link called "previous". 
void insert_node(link previous, link new_node_link) {
    if (previous == NULL) {
        printf("\n Cannot insert after a NULL node. No action taken.");        		
    } else {
        new_node_link->next = previous->next;
        previous->next = new_node_link;
    }    
}

// Returns 0 for empty lists (have just one dummy node) and NULL lists 
int compute_length(link Ld) {
    if (Ld == NULL) {
        return 0;
    }

    int counter = 0;
    link curr;
    for (curr = Ld->next; curr != NULL; curr = curr->next) {
        counter++;
    }
    return counter;
}


void print_list(link my_list) {
    if (my_list == NULL) {
		printf("\n<print_list> : list is NULL\n");    
        return;
    }
    int i = 0;    
    link curr;
    printf("\n List items:\n");
    for (i = 0, curr = my_list->next; (curr != NULL); curr = curr->next) {
        printf("item %d: %d\n", i, curr->data);
        i++;
    }
	printf(" Length of above list = %d\n", i);    
}

void print_list_horiz(link my_list) {
    if (my_list == NULL) {
		printf("\n<print_list_horiz> : List is NULL\n");    
        return;		
    }
    int i = 0;    
    link curr;

    printf("\n List items: ");
    for (i = 0, curr = my_list->next; (curr != NULL); curr = curr->next) {
        printf("%5d    ", curr->data);
        i++;
    }
	printf("\n Length of above list = %d\n", i);    
}

void print_list_horiz_pointer(link my_list) {
    if (my_list == NULL) {
		printf("\n<print_list_horiz_pointer> : List is NULL\n");    
        return;
    }

    int i = 0;    
    link curr;	
    printf("\n List items:    ");
    for (i = 0, curr = my_list->next; (curr != NULL); curr = curr->next) {
        printf("%-11d ", curr->data);
        i++;
    }    
    printf("\n List pointers: ");
    for (i = 0, curr = my_list->next; (curr != NULL); curr = curr->next) {
        printf("%p ", curr);
        i++;
    }
	printf("\n Length of above list = %d\n", i);    	
}

 // Sorts List A IN PLACE, using insertion sort by MOVING node,NOT copying node content
 // O(N^2) time,
 // O(1) data moves. Here pointer copying is counted as a constant operation, NOT a data move.
 // The data in the nodes is not copied, only the links are updated.
void insertion_sort(link Ad) {
	link c,p;      // Current and Previous in outer loop
	link cl,pl;    // Current and Previous in Left loop
	p = Ad->next;
	c = p->next;
	while (c != NULL){
		pl = Ad;
		cl = pl->next;
		while ((cl->data <= c->data) && (cl != c)){
			pl = pl->next;
			cl = cl->next;
		}
		if (cl!=c){  
			// move c between pl and cl
			p->next = c->next;
			pl->next = c;
			c->next = cl;
			
			// update temp variable c. 
			// do NOT update p.
			c = p->next;
		} 
		else { // c was not moved. Must update both p and c
			p=c;
			c=c->next;
		}
	}
    return;
}


/*----------------------------------------------------------------
 New functions.
 Finish their implementation below. 
 If you need to use helper functions you can define them and use them in this file.
 ***You should not change the behavior of any of the functions defined above.***
 *** You should only write code in this file. DO not modify the client file in any way. You will NOT submit the client file. 
 
 NOTE: that the functions:
 link array_2_list(int arr[], int sz)
 link build_list_of_ints()
 are implemented and used in the instructor_client.c file, 
 BUT YOU CAN ALSO CALL THEM AND USE THEM IN YOUR run_student_tests function,
 or any other helper function that you write here, in list_hw.c
 */
 
link GetNode(link A, int pos)
{
	int i;
	for(i = 0; i < pos && A != NULL; i++)
		A = A->next;
	return A;
}

link sublist(link A, link pos_list) {
	
	if(A == NULL || pos_list == NULL ||A->next == NULL || pos_list->next == NULL)
	{
		printf("Given empty list\n");
		return NULL;
	}
	
	link OrigLink = A->next;
	link ReturnList = new_list();
	link PrevNode = NULL;
	link NewNode = ReturnList;
	int i = 0;
	
	while(pos_list != NULL)
	{		
		
		link Node = GetNode(OrigLink, pos_list->data);
		
		if(Node == NULL || pos_list->data < 0)
		{
			i = 1;
			break;
		}
		
		PrevNode = NewNode;
		NewNode->next = new_node(Node->data, NULL);
		NewNode = NewNode->next;
		
		pos_list = pos_list->next;
	}
	
	if(i)
	{
		destroy_list(ReturnList);
		return NULL;
	}
	
	free(NewNode);
	
	if(PrevNode == NULL)
		return NULL;
	else
		PrevNode->next = NULL;
	
	
    return ReturnList;
}

void swap_first_third(link A) {
	
	if(A == NULL || A->next == NULL || A->next->next == NULL)
		return;
	
	link Node = A->next;
	link Node2 = Node->next;
	
	if(Node2->next == NULL) {
		
		Node2->next = Node;
		Node->next = NULL;
		A->next = Node2;
		return;
		
	}
	
	link Node3 = Node2->next;

	link temp = Node3->next; 
	Node3->next = Node->next;
	Node->next  = temp;
	A->next = Node3;
	Node2->next = Node;	
	
    return;
}
 
void delete_occurrences(link A, int V) {
	
	if(A == NULL ||A->next == NULL)
	{
		printf("Given empty list\n");
		return;
	}
	
	link Node = NULL;
	link CurrNode = A->next;
	link PrevNode = NULL;
	
	while(CurrNode != NULL)
	{
		if(CurrNode->data == V)
		{
			if(CurrNode->next == NULL)
			{
				A->next = NULL;
				free(CurrNode);
				return;
			}
			
			PrevNode->next = CurrNode->next;
			Node = CurrNode->next; 
			free(CurrNode);
			CurrNode = Node;
		}
		
		else {
			PrevNode = CurrNode;
			CurrNode = CurrNode->next;
		}
	}
	
    return;
}

void print_sublist(link A, link pos)
{
	printf("A:");
	print_list_horiz(A);
	printf("pos_list:");
	print_list_horiz(pos);
	
	//pass the test data to your function
	link new_sublist = sublist(A, pos);
	
	//print the result 
	printf("Sublist: ");
	print_list_horiz(new_sublist);
	destroy_list(new_sublist);
}

void print_delete_occurences(link A, link pos)
{
	printf("A:");
    print_list_horiz(A);
    print_list_horiz_pointer(A);

    delete_occurrences(A, 7);

    print_list_horiz(A);
    print_list_horiz_pointer(A);
}

void run_sublist_test() {
	
	printf("\n---- TEST for sublist -----\n");
	
	printf("\nTEST 1\n");
	//create some test data 
	link A = NULL;
    int arr[] = {10, 10, 40, 20};
    A = array_2_list(arr, 4);
	
	int arr_pos[] = {-7, 3};
    link pos = array_2_list(arr_pos, 2);
	print_sublist(A, pos);
	destroy_list(pos);
	
	int arr_pos2[] = {3, 80000, 3};
	pos = array_2_list(arr_pos2, 3);
	print_sublist(A, pos);
	destroy_list(pos);
	destroy_list(A);
	
	printf("\nTEST 2\n");
	
	int arr2[] = {15, 100, 7, 5, 100};
    A = array_2_list(arr2, 5);
	
	int arr_pos3[] = {3, 0, 2};
    pos = array_2_list(arr_pos3, 3);
	
	print_sublist(A, pos);
	print_list_horiz(A);
	destroy_list(pos);
	
	printf("\nTEST 3\n");
	
	int arr_pos4[] = {3, 0, 6, 4};
    pos = array_2_list(arr_pos4, 4);
	
	print_sublist(A, pos);
	destroy_list(A);
	destroy_list(pos);
	
	printf("\nTEST 4\n");
	
	int arr3[] = {5};
    A = array_2_list(arr3, 1);
	
	int arr_pos5[] = {0, 0, 0};
    pos = array_2_list(arr_pos5, 3);
	
	print_sublist(A, pos);
	
	destroy_list(A);
	
	printf("\nTEST 5\n");
	A = NULL;
	print_sublist(A, pos);
	
	printf("\nTEST 6\n");
	A = new_list();
	print_sublist(A, pos);
	
	destroy_list(A);
	destroy_list(pos);
	int arr4[] = {15, 100, 7, 5, 100};
    A = array_2_list(arr4, 5);
	
	printf("\nTEST 7\n");
	pos = NULL;
	print_sublist(A, pos);
	
	printf("\nTest 8\n");
	pos = new_list();
	print_sublist(A, pos);
	
	destroy_list(A);
	destroy_list(pos);

	return;
}

void run_delete_occurences_test() {
	printf("\n---- TEST for delete_occurrences -----\n");
	
	link A = NULL;
	int V;
	
	printf("\nTEST 1\n"); 
	
    int arr[] = {15,100,7,5,100,7,30};
    A = array_2_list(arr, 7);
	printf("A:");
    print_list_horiz_pointer(A);

    delete_occurrences(A, 7);
	printf("After delete occurences: ");

    print_list_horiz_pointer(A);
	destroy_list(A);
	
	printf("\nTEST 2\n");
	
	int arr2[] = {15, 100, 7, 5};
	A = array_2_list(arr2, 4);
	printf("A:");
    print_list_horiz_pointer(A);

    delete_occurrences(A, 9);
	printf("After delete occurences: ");

    print_list_horiz_pointer(A);
	destroy_list(A);
	
	printf("\nTEST 3\n");
	
	int arr3[] = {15, 7, 7, 5};
	A = array_2_list(arr3, 4);
	printf("A:");
    print_list_horiz_pointer(A);

    delete_occurrences(A, 7);
	printf("After delete occurences: ");
	
    print_list_horiz_pointer(A);
	destroy_list(A);
	
	printf("\nTEST 4\n");
	
	int arr4[] = {7};
	A = array_2_list(arr4, 1);
	printf("A:");
    print_list_horiz_pointer(A);

    delete_occurrences(A, 7);
	printf("After delete occurences: ");

    print_list_horiz_pointer(A);
	destroy_list(A);
	
	printf("\nTEST 5\n");
	
	A = NULL;
	printf("A:");
    print_list_horiz_pointer(A);

    delete_occurrences(A, 9);
	printf("After delete occurences: ");

    print_list_horiz_pointer(A);
	
	printf("\nTEST 6\n");
	
	A = new_list();
	printf("A:");
    print_list_horiz_pointer(A);

    delete_occurrences(A, 9);
	printf("After delete occurences: ");

    print_list_horiz_pointer(A);
	destroy_list(A);

	return;
}

void run_swap_first_third_test()
{
		printf("\n---- TEST for swap_first_third -----\n");
	
	link A = NULL;
	
	printf("\nTEST 1\n"); 
	
    int arr[] = {15,100,7,5,100,7,30};
    A = array_2_list(arr, 7);
	printf("A:");
    print_list_horiz_pointer(A);

    swap_first_third(A);
	printf("After swap first third: ");

    print_list_horiz_pointer(A);
	destroy_list(A);
	
	printf("\nTEST 2\n"); 
	
    int arr2[] = {10};
    A = array_2_list(arr2, 1);
	printf("A:");
    print_list_horiz_pointer(A);

    swap_first_third(A);
	printf("After swap first third: ");

    print_list_horiz_pointer(A);
	destroy_list(A);
	
	printf("\nTEST 3\n"); 
	
    int arr3[] = {10,20};
    A = array_2_list(arr3, 2);
	printf("A:");
    print_list_horiz_pointer(A);

    swap_first_third(A);
	printf("After swap first third: ");

    print_list_horiz_pointer(A);
	destroy_list(A);
	
	printf("\nTEST 4\n"); 
	
    A = NULL;
	printf("A:");
    print_list_horiz_pointer(A);

    swap_first_third(A);
	printf("After swap first third: ");

    print_list_horiz_pointer(A);
	destroy_list(A);
	
	printf("\nTEST 5\n"); 
	
    A = new_list();
	printf("A:");
    print_list_horiz_pointer(A);

    swap_first_third(A);
	printf("After swap first third: ");

    print_list_horiz_pointer(A);
	destroy_list(A);
	
	return;
}
	

// Set-up and call your testing functions from this function.
int run_student_tests() {
	
    printf("\n Running function run_student_test.\n ");
    printf("\n\n--------------------------------------\n");
	
	run_sublist_test();
	run_delete_occurences_test();
	run_swap_first_third_test();
	
	return;
}

