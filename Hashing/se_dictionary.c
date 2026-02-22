#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 7477
	
typedef struct {
	char key[100];
	char data[900];
} HashStruct;


//Hash Function Citation: Retrieved Original from http://www.cse.yorku.ca/~oz/hash.html
int hash(char *str, int M)
{ 
    unsigned long hash = 5381;
    int c = 0;

    while (c = *str++) {
		hash = hash * 33 + c; 
		hash %= M;
	}

    return hash;
 }
 
double insert(HashStruct* hashArray[], int *array, char* key, char* data, int M, int intArrIndex, double max) {
	int probes = 1;
	char a[900] = {0};
	
	int index = hash(key, M);

   while(hashArray[index]->key != NULL && strcmp(hashArray[index]->key, "-1") != 0) {
	   
		if(hashArray[index]->key != NULL && strcmp(hashArray[index]->key, key) == 0) {
			strcpy(a, "; ");
			strcat(a, data);
			strcat(hashArray[index]->data, a);
			break;
		}
		
      index = (index + key[0]) % M;
	  probes++;
   }
   
   if(max < probes)
	   max = probes;
   
   if(hashArray[index]->key == NULL) {
		HashStruct *item = malloc(sizeof(HashStruct));
		strcpy(item->data, data);  
		strcpy(item->key,key);
		hashArray[index] = item;
    }
   
   else if(strcmp(hashArray[index]->key, "-1") == 0) {
		strcpy(hashArray[index]->key,key); 
		strcpy(hashArray[index]->data,data);
    }
   
   array[intArrIndex] = probes;
   return max;
}

double search(HashStruct* hashArray[], char* key, int M) {
   int index = 0;
   index = hash(key,M);
   double probes = 1.0000;
	
   while(hashArray[index] != NULL) {
	
      if(hashArray[index]->key != NULL && strcmp(hashArray[index]->key, key) == 0) {
		printf("\t%.0lf probes\n",probes); 
		printf("\tTranslation: %s\n", hashArray[index]->data);
		return probes;
	  }
     
      index = (index + key[0]) % M;
	  probes += 1.0000;
   }  
   
   printf("\t%.0lf probes\n",probes);
   printf("\tNOT found\n");
   return probes;
   
}

double delete(HashStruct* hashArray[], char* key, int M) {
	double probes = 1;

   int index = 0;
   index = hash(key, M);

   while(hashArray[index] != NULL) {
	
      if(hashArray[index]->key != NULL && strcmp(hashArray[index]->key, key) == 0) {
         strcpy(hashArray[index]->key,"-1"); 
		 strcpy(hashArray[index]->data,"\0");
		 printf("\t%.0lf probes\n",probes); 
		 printf("\tItem was deleted\n");
		 return probes;
      }

      index = (index + key[0]) % M;
	  probes += 1.0;

   } 
   
    printf("\t%.0lf probes\n",probes); 
	printf("\tItem not found => no deletion\n");
	return probes;
   
}


void PrintProbes(int* array) {
	
	int i, j, k = 0;
	
	for(i=0; i<100; i++)
	{
		if(!i) {
			printf("Probes| Count of Keys\n");
			printf("---------------------\n");
		}
		
		for(j=0; j < SIZE; j++) {
			if(array[j] == i+1) k++;
		}
	
		printf("   %d  | %d \n", i+1, k);
		printf("---------------------\n");
		k=0;
	}
	
	printf("\n\n");
} 

void PrintTable(int* array, double max, double notHashed)
{
	double sum = 0;
	int i;
	for(i=0; i <= SIZE; i++) {
		sum += array[i];
	}
	
	printf("\n\nHash Table\n");
	printf("   average number of probes:         %.3lf\n", sum/SIZE);
	printf("   max_run of probes:                %.0lf\n", max);
	printf("   total PROBES (for 7477 items):    %.0lf\n", sum);
	printf("   items NOT hashed (out of 7477):   %.0lf\n", notHashed);
	
	printf("\n\n");
}

void DestroyArray(HashStruct* hashArray[]) {
	int i;
	for (i=0; i<23431; i++) {
		if(hashArray[i] != NULL)
			free(hashArray[i]);
	}
}
	

int main(int argc, char** argv) {
	
	HashStruct* hashArray[23431] = {NULL};
	int M = 23431;
	FILE *MyFile;
	char key[100] = {0};
	char data[900];
	//Program will fail if data/translation is longer than 900 characters
	int eof = 0;
	int intArray[7500] = {0};
	double max = 0;
	char input[2] = {0};
	char word[100];
	char transl[100];
	double probes = 0.0;
	double totalProbes = 0.0;
	double avg = 0.0;
	
	char dictname[12] = "Spanish.txt";
	MyFile = fopen(dictname, "r");
	if (MyFile == NULL)
	{
		perror("fopen() failed ");
		exit(0);
	}
	
	double i = 0.0;
	while(eof != EOF) {
		eof = fscanf(MyFile, "%s", key);
		fscanf(MyFile, " ");
		fgets(data, sizeof(data), MyFile);
		data[strlen(data)-1] = '\0';

		max = insert(hashArray, intArray, key, data, M, i, max);
		i += 1.0;
	}
	
	fclose(MyFile);
	
	PrintTable(intArray, max, SIZE-i);
	PrintProbes(intArray);
	
	i = 0;
	while(input) {
		printf("\nEnter operation ('s' to search, 'd' to delete, or 'i' to insert) followed by a space and word/s. Enter -1 to stop\n");
		scanf("%s", input);
		 
		//A 'q' or '-1' will end the program and show the average number of probes per operation
		if(strcmp(input, "q") == 0 || strcmp(input, "-1") == 0) {
			avg = totalProbes/i;
			printf("\nAverage probes per operation: %.3lf\n", avg);
			break;
		}
		
		//Enter an s, a space, and a word to look up in the file. For example, "s dog"
		else if(strcmp(input, "s") == 0) {
			scanf("%s", word);
			printf("READ op:%s query:%s\n", input, word);
			probes = search(hashArray, word, M);
			totalProbes += probes;
		}
		
		//Enter a d, a space, and a word to delete in the file. For example, "d dog"
		else if(strcmp(input, "d") == 0) {
			scanf("%s", word);
			printf("READ op:%s query:%s\n", input, word);
			probes = delete(hashArray, word, M);
			totalProbes += probes;
			}
		
		//Enter an i, a space, and the to insert in the file followed by its Spanish translation. For example, "i December diciembre"
		//any traslation with a space will not be properly inputted, only the first word will be taken
		else if(strcmp(input, "i") == 0) {
			scanf("%s", word);
			scanf("%s", transl);
			printf("READ op:%s query:%s\n", input, word);
			probes = insert(hashArray, intArray, word, transl, M, i, 0);
			printf("\t%.0lf probes\n", probes);
			printf("\tWill insert pair [%s, %s] \n", word, transl);
			totalProbes += probes;
		}
		
		else
			printf("Invalid Input\n");
		
		i += 1.0;
	}
	
	DestroyArray(hashArray);
	
	return 0;
}


