#include <stdlib.h>
#include <stdio.h>

void merge(int a[], int l, int m, int r) {
	int i,j,k;
	int n1 = m-l+1;
	int n2 = r-m;
	
	int L[n1];
	int R[n2];
	
	for(i=0; i < n1; i++)
		L[i] = a[l+i];
	
	for(i=0; i < n2; i++)
		R[i] = a[m+1+i];
	
	i=0;
	j=0; 
	k=l;
	
	while(i < n1 && j < n2) {
		
		if(L[i] <= R[j]) {
			a[k] = L[i];
			i++;
		}
		else {
			a[k] = R[j];
			j++;
		}
		k++;
	}
	
	while(i < n1) {
		a[k] = L[i];
		i++;
		k++;
	}
	
	while(j < n2) {
		a[k] = R[j];
		j++;
		k++;
	}
}

int min(int x, int y) {
	return (x<y) ? x : y;
}

void PrintArray(int a[], int size, int l, int r) {
	int i;
	for(i=0; i < size; i++) {
		if(i < l || i > r && l != r)
			printf("     ,");
		else
			printf("%5d,", a[i]);
	}
	
	printf("\n");
}

void MergeSort(int a[], int N) {
	int currSize;
	int leftStart;
	
	for(currSize=1; currSize <= N-1; currSize *= 2) {
		
		for(leftStart=0; leftStart < N; leftStart += 2*currSize) {
			
			int mid = leftStart + currSize - 1;
			int rightEnd = min(leftStart + 2*currSize - 1, N);
			
			merge(a, leftStart, mid, rightEnd);
			PrintArray(a, N, leftStart, rightEnd);
		}
	}
}

int main (int argc, char** argv) {

	int N = 0;
	int i;
	
	while(N != -1) {
		//printf("Enter size of array: ");
		scanf("%d", &N);
		if( N == -1 ) break;
		int N2 = N;
		int arr[N];
		
		i=0;
		while(N2 != 0) {
			scanf("%d", &arr[i]);
			N2--;
			i++;
		}
		
		printf("\nread array: \n");
		PrintArray(arr, N,0,N+1);
		MergeSort(arr, N);
		PrintArray(arr, N,0,N+1);
	}

	return;
}
