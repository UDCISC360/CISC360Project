#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//http://www.geeksforgeeks.org/bubble-sort/
/*void bubbleSort(int arr[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)      
 
       // Last i elements are already in place   
       for (j = 0; j < n-i-1; j++) 
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
}*/
void bubbleSort_Par(int arr[], int n, int threads)
{
	int temp;
	for (int k = 0; k <= n-2; k++)
	{
		#pragma omp parallel shared(arr, n) num_threads(threads)
		if (k % 2 == 0){
			#pragma omp for
			for (int i = 0; i <= (n/2)-1; i++)
			{
				if (arr[2 * i] > arr[2 * i + 1])
				{
					temp = arr[2 * i];
					arr[2 * i] = arr[2 * i + 1];
					arr[2 * i + 1] = temp;
				}
			}
		}
		else{
			#pragma omp for
			for (int j = 0; j <= (n/2)-2; j++)
			{
				if (arr[2 * i + 1] > arr[2 * i + 2])
				{
					temp = arr[2 * i + 1];
					arr[2 * i + 1] = arr[2 * i + 2];
					arr[2 * i + 2] = temp;
				}
			}
		}
	}
}


//http://www.geeksforgeeks.org/comb-sort/
// Function to sort a[0..n-1] using Comb Sort
/*void combSort(int a[], int n)
{
    // Initialize gap
    int gap = n;
 
    // Initialize swapped as true to make sure that
    // loop runs
    bool swapped = true;
 
    // Keep running while gap is more than 1 and last
    // iteration caused a swap
    while (gap != 1 || swapped == true)
    {
        // Find next gap
        gap = getNextGap(gap);
 
        // Initialize swapped as false so that we can
        // check if swap happened or not
        swapped = false;
 
        // Compare all elements with current gap
        for (int i=0; i<n-gap; i++)
        {
            if (a[i] > a[i+gap])
            {
                swap(a[i], a[i+gap]);
                swapped = true;
            }
        }
    }
}
*/
//https://geeksforgeeks.org/shellsort
/* function to sort arr using shellSort */
/*
int shellSort(int arr[], int n)
{
    // Start with a big gap, then reduce the gap
    for (int gap = n/2; gap > 0; gap /= 2)
    {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements a[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is
        // gap sorted 
        for (int i = gap; i < n; i += 1)
        {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            int temp = arr[i];
 
            // shift earlier gap-sorted elements up until the correct 
            // location for a[i] is found
            int j;            
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
             
            //  put temp (the original a[i]) in its correct location
            arr[j] = temp;
        }
    }
    return 0;
}
*/

void print_array(int n, double array[]) {
  int i;
  printf("[%.0f", array[0]);
  for (i = 1; i < n; i++) {
    printf(", %.0f", array[i]);
  }
  printf("]\n");
}
void test_correctness(int n, double array[]) {
  int i;
  for (i = 1; i < n; i++) {
    if (array[i] < array[i - 1]) {
      printf("Correctness test found error at %d: %.4f is not < %.4f but appears before it\n", i, array[i - 1], array[i]);
    }
  }
}
void init_random_vector(int n, double array[]) {
  int i;
  for (i = 0; i < n; i++) {
    array[i] = rand();
  }
}


int main(){
	int n = 100; //size of array
	int threads = 32; //number of threads
	int seed = 0; //seed is initial value given to random sequence generator
	srand(seed); //random number generator
	
	int *array = (int *)malloc(sizeof(int) * n);
	
	init_random_vector(n, array);
	
	double startBubble = omp_get_wtime();
	bubbleSort_Par(array, n, threads);
	double endBubble = omp_get_wtime();
	
	if (n < 10000)
	{
		test_correctness(n, array);
	}
	
	free(array);
	return 0;
}
