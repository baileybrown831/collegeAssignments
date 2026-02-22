//Bailey Brown 1001555076 :^)
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void CreateData(int N, int S, int StartVal, int EndVal, char filename[])
{
	int i;
	int nums[N];
	char Input[20];
	char Delimiters = ' ';
	FILE *MyFile;
	srand(time(NULL));

	MyFile = fopen(filename, "w");
	fprintf(MyFile, "%d %d %d %d\n", N, S, StartVal, EndVal);

	for(i=0; i<N; i++)
		fprintf(MyFile, "%d ", (rand() % (EndVal - StartVal + 1)) + StartVal);
	
	fprintf(MyFile, "\n");
	
	for(i=0; i<S; i++)
		fprintf(MyFile, "%d ", (rand() % (EndVal - StartVal + 1)) + StartVal);
	
	fclose(MyFile);
}



void SelectionSort(int A[], int N)
{
	int i, j, temp;
	
	for (j = 0; j < N-1; j++)
	{
		int min_idx = j;
		
		for (i = j+1; i < N; i++)
			if (A[i] < A[min_idx]) min_idx = i;
		
		temp = A[min_idx];
		A[min_idx] = A[j];
		A[j] = temp;
	}
}


void PrintVerbose(int a[])
{
	//do this
}

void PrintNonVerbose(int a[])
{
	//do this
}

int BinarySearch(int A[], int N, int v)
{
	int left = 0;
	int right = N-1;
	int i;
	
	while (left <= right)
	{ 
		int m = (left+right)/2;
		
		if (v == A[m]) 
			return m;
		if (v < A[m])
			right = m-1;
		else
			left = m+1;
		
		i++;
	}
	
	return -1;
}

int InterpolatedSearch(int A[], int N, int v)
{
	int left = 0;
	int right = N-1;
	int m, i = 0;
	
	while (left <= right)
	{ 
		int m = left + (v - A[left])*(right - left) / (A[right] - A[left]);
		
		if (v == A[m]) 
			return m;
		if (v < A[m])
			right = m-1;
		else
			left = m+1;
		
		i++;
	}
	
	return -1;
	
}


/*void LoadData(int N, int S, int *A, int *B)
{
	char filename[100];
	int num, mode, i;
	char buffer[100];
	FILE *MyFile;
	
	printf("Enter: filename, mode(1-verbose, 2-not verbose): ");
	scanf("%s %d", filename, &mode);

	MyFile = fopen(filename, "r");
	fgets(buffer, sizeof(buffer)-1, MyFile);

    while((fscanf(MyFile, "%d", &num) > 0) && (num != '\n')) {
        *A = num;
        A++;
    }
	
	for(i=0;i<17;i++)
	{
		printf("%d", *A);
		A++;
	}

    while(fscanf(MyFile, "%d", &num) > 0) {
        *B = num;
        B++;
    }
	
		for(i=0;i<11;i++)
	{
		printf("%d", *B);
		B++;
	}
	
	fclose(MyFile);
	
	return;
	
}*/
	

int main(void)
{

	int choice = 1;
	int i=0;
	int N, S, StartVal, EndVal, mode, num;
	char cs[100];
	char ds[100];
	int A[100];
	int B[100];
	char filename[20];
	char buffer[100];
	char Delimiters = ' ';
	FILE *MyFile;
	
	while(choice)
	{
		
		printf("0-exit\n");
		printf("1-create and save random data for search.\n");
		printf("2-load data from file, sort array and run searches.\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		
		switch(choice)
		{
			case 1 :
				printf("Enter: N S start_val end_val filename(with extension): ");
				scanf("%d %d %d %d %s", &N, &S, &StartVal, &EndVal, filename);
				CreateData(N,S,StartVal,EndVal,filename);
				break;
			case 2 :
				printf("Enter: filename, mode(1-verbose, 2-not verbose): ");
				scanf("%s %d", filename, &mode);

				MyFile = fopen(filename, "r");
				fgets(buffer, sizeof(buffer)-1, MyFile);
				

				while((fscanf(MyFile, "%[^\n]", &A[i]) != EOF)) {
					i++;
				}
	
				printf("\n");

				while(fscanf(MyFile, "%[^\n]", &B[i]) != EOF ) {
					i++;
				}*/
	
				printf("\n");
	
				fclose(MyFile);
				
		}
	}
	
	return 0;
	
}


