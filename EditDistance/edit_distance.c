#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "edit_distance.h"


void PrintTable(char * first_string, char * second_string, int *array) {
	
	int i, j;
	
	for(i=0; i<strlen(second_string)+2; i++)
	{
		if(i<2)
			printf("  |");
		else
			printf(" %c|", second_string[i-2]);
	}
	
	for(i=0; i<strlen(first_string)+1; i++)
	{
		printf("\n");
		for(j=0; j<3*(strlen(second_string)+2); j++)
			printf("-");
		printf("\n");
		
		if(i==0)
			printf("  |");
		else
			printf(" %c|", first_string[i-1]);
		
		for(j=0; j<strlen(second_string)+1; j++)
		{
			printf(" %d|", *((array+i*(strlen(second_string)+1)+j)));
		}
	}
	
	printf("\n\n");
} 

int Min(int x, int y, int z) {
		
	int c = 0;
	while (x && y && z) { 
		x--; 
		y--; 
		z--; 
		c++; 
	}
		
	return c;
}		
	

int edit_distance(char * first_string, char * second_string, int print_table){
	
	int i, j;
	int array[strlen(first_string)+1][strlen(second_string)+1];
	
	for(i=0; i<strlen(first_string)+1; i++)
	{

		for(j=0; j<strlen(second_string)+1; j++)
		{
			if(i==0)
				array[i][j] = j;
			else if(j==0)
				array[i][j] = i;
			else {
				int c = 0; 
				int x = array[i-1][j]+1;
				
				int z;
				
				if(first_string[i-1] == second_string[j-1])
					z = array[i-1][j-1];
				else
					z = array[i-1][j-1]+1;
				
				array[i][j] = Min(array[i-1][j]+1, array[i][j-1]+1, z);
			}
		}
	}
	
	if(print_table)
		PrintTable(first_string, second_string, (int *)array);
	
	return array[strlen(first_string)][strlen(second_string)];
}
	


