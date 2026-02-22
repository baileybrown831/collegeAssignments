#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Use this method to print the data for foo_memoized at different depth.
void print_at_depth(int depth, int N){
	int i;
	printf("\n");
	for(i=0;i<depth; i++){
		printf("   ");		
	}
	printf("N = %d, depth = %d\n", N, depth);
}


int foo_iterative(int N){
	
	int res1 = 5;
	int res2 = 5;
	int i;

	if (N <= 1) return 5;
	
	for(i=N; i > 1; i /= 2)
	{
		res1 *= 3;
	}
		
	if (res1 >= res2)
		return res1;
	else
		return res2;
}
       

// Write the foo_memized function
int foo_memoized(int N, int depth, int* arr) {
	
	if(*(arr+N) != 0)
	{
		print_at_depth(depth, N);
		return *(arr+N);
	}
		
	*(arr+N) = N;
	
	print_at_depth(depth, N);
	if (N <= 1) return 5; // one value, multiply to product
	int res1 = 3*foo_memoized(N/2, depth+1, arr);
	int res2 = foo_memoized(N-1, depth+1, arr);
	if (res1 >= res2)
		return res1;
	else
		return res2;       
}

int foo_wrapper(int N){    
	int result;
	int arr[N];
	memset(arr, 0, (N+1)*sizeof(int));
	
	result = foo_memoized(N, 0, arr);
	
	return result; 
}

// Do not modify main
int main(int argc, char** argv) {
	int N, res1,res2;
	printf("Enter N: ");
	scanf("%d",&N);
    
	while (N!= -1){
		printf("Calling foo_iterative(N)\n");
		res1 = foo_iterative(N);
		printf("Result of iterative function for N=%d is: %d\n", N, res1);
		
		printf("Calling foo_wrapper(N)\n");
		res2 = foo_wrapper(N);
		printf("Result of memoized function for N=%d is: %d\n", N, res2);
		
		printf("\n--------------------------------\nEnter N: ");
		scanf("%d",&N);
	}
	return (EXIT_SUCCESS);
}




	
	
	
	
	

		





