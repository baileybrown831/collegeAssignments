//Bailey Brown 1001555076

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void DFS(int u, int N, int visited[], int matrix[N][N], char color[], char names[][20]) {
	
	color[u] = 'g';
    int i;
	printf("\n%s", names[u]);
    visited[u]=1;
	
	for(i=0; i < N; i++) {
       if(!visited[i] && matrix[u][i]==1)
            DFS(i, N, visited, matrix, color, names);
	}
	color[u] = 'b';
}


int main (int argc, char** argv) {
	int N;
	int i, j;
	char name1[20];
	char name2[20];
	int index1;
	int index2;
	
	printf("Enter number of vertices, N: ");
	scanf("%d", &N);
	
	char names[N][20];
	char color[N];
	memset(color, 'w', N*sizeof(color[0]));
	int visited[N];
	memset(visited, 0, N*sizeof(visited[0]));
	int matrix[N][N];
	memset(matrix, 0, N*N*sizeof(matrix[0][0]));
	
	for(i=0; i < N; i++) {
		printf("Enter name1: ");
		scanf("%s", names[i]);
	}
	

	while(1) {
		printf("Enter name1 name2: ");
		scanf("%s %s", name1, name2);
		
		if(!strcmp("-1", name1))
			break;
		
		for(i=0; i < N; i++) {
			if(!strcmp(name1, names[i]))
				index1 = i;
			else if(!strcmp(name2, names[i]))
				index2 = i;
		}
		
		matrix[index1][index2] = 1;
		matrix[index2][index1] = 1;
	}
	
	printf("\n\nGRAPH:\n");
	printf("N = %d\n", N);
	
	for (i = 0; i < N; i++) {
		printf("%d - %s\n", i, names[i]);
	}
	
	printf("\n");

    for (i = 0; i < N; i++) {
		
        for (j = 0 ; j < N ; j++) {
            printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
	
	j = 0;
	for(i=0; i < N; i++) {
		if(color[i] == 'w') {
			j++;
			printf("\nGroup: %d", j);
			DFS(i, N, visited, matrix, color, names);
			printf("\n");
		}
	}
	
	printf("\nNumber of groups: %d\n", j);
	
	
}

