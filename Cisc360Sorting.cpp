#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//http://www.geeksforgeeks.org/bubble-sort/
void bubbleSort(int arr[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)      
 
       // Last i elements are already in place   
       for (j = 0; j < n-i-1; j++) 
           if (arr[j] > arr[j+1])
              //swap(&arr[j], &arr[j+1]);
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
}
void bubbleSort_Par(int arr[], int n, int threads)
{
	int k,i,j,temp;
	#pragma omp parallel shared(arr, n) num_threads(threads)
	//i think i need to add private(i, j, temp) k is shared?
	for (k = 0; k <= n-2; k++)
	{
		if (k % 2 == 0){
			#pragma omp for
			for (i = 0; i <= (n/2)-1; i++)
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
			for (j = 0; j <= (n/2)-2; j++)
			{
				if (arr[2 * j + 1] > arr[2 * j + 2])
				{
					temp = arr[2 * j + 1];
					arr[2 * j + 1] = arr[2 * j + 2];
					arr[2 * j + 2] = temp;
				}
			}
		}
	}
}


//http://www.geeksforgeeks.org/comb-sort/
// To find gap between elements
/*int getNextGap(int gap)
{
    // Shrink gap by Shrink factor
    gap = (gap*10)/13;
    if (gap < 1)
        return 1;
    return gap;
}
// Function to sort a[0..n-1] using Comb Sort
void combSort(int a[], int n)
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
}*/
//http://www.sanfoundry.com/c-program-implement-comb-sort/
/*Function to find the new gap between the elements*/
int newgap(int gap)
{
    gap = (gap * 10) / 13;
    if (gap == 9 || gap == 10)
        gap = 11;
    if (gap < 1)
        gap = 1;
    return gap;
}
 
/*Function to implement the combsort*/
void combsort(int a[], int aSize)
{
    int gap = aSize;
    int temp, i;
    for (;;)
    {
        gap = newgap(gap);
        int swapped = 0;
        for (i = 0; i < aSize - gap; i++) 
        {
            int j = i + gap;
            if (a[i] > a[j])
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
                swapped  =  1;
            }
        }
        if (gap  ==  1 && !swapped)
            break;
    }
}
void combSort_Par(int array[], int n, int threads)
{
    int gap = n;
	int temp, i, swapped, j, m;
    bool swapped = true;
	#pragma omp parallel shared(array, n) num_threads(threads)
	//i think i need to add private(temp, j, m, n)
	//swapped is shared? gap is shared? make i shared?
	for(;;)//basically while(true)
	{
		gap = newgap(gap);
		swapped = 0;
		for(i = 0; i < n-gap; i++)
		{
			if(i%2 == 0)
			{
				#pragma omp for
				for(m = 0; m < (n-gap)/2; m++)
				{
					j = m + gap;
					if(array[m] > array[j])
					//if(array[2*m] > array[j*2])
					{
						temp = array[m];
						array[m] = array[j];
						array[j] = temp;	
						swapped = 1;
						/*
						temp = array[2*m];
						array[2*m] = array[2*j];
						array[2*j] = temp;
						*/
					}
				}
			}
			else
			{
				#pragma omp for
				for(n = 0; n < ((n-gap)/2)-1; n++)
				{
					j = n + gap;
					if(array[n] > array[j])
					//if(array[2*n] > array[2*j])
					{
						temp = array[n];
						array[n] = array[j];
						array[j] = temp;	
						swapped = 1;
						/*
						temp = array[2*n];
						array[2*n] = array[2*j];
						array[2*j] = temp;
						*/
					}
				}
			}
		}
		if(gap == 1 && !swapped)
		{
			break;
		}
	}
}


//https://geeksforgeeks.org/shellsort
/* function to sort arr using shellSort */

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
//start of shell sort parallel
//https://stackoverflow.com/questions/5903208/shell-sort-in-openmp
void insertionsort(int a[], int n, int stride) 
{//since shellsort basically uses a bunch of insertion sorts
    for (int j=stride; j<n; j+=stride) {
        int key = a[j];
        int i = j - stride;
        while (i >= 0 && a[i] > key) {
            a[i+stride] = a[i];
            i-=stride;
        }
        a[i+stride] = key;
    }
}
void shellSort_Par(int a[], int n, int threads)
{
    int i, m;
    #pragme omp parallel shared(a,m,n) private(i) num_threads(threads)
    for(m = n/2; m > 0; m /= 2)
    {
            #pragma omp for
            for(i = 0; i < m; i++)
                insertionsort(&(a[i]), n-i, m);
    }
}
void print_array(int n, int array[]) {
  int i;
  printf("[%.d", array[0]);
  for (i = 1; i < n; i++) {
    printf(", %.d", array[i]);
  }
  printf("]\n");
}
void test_correctness(int n, int array[]) {
  int i;
  for (i = 1; i < n; i++) {
    if (array[i] < array[i - 1]) {
      printf("Correctness test found error at %d: %.4f is not < %.4f but appears before it\n", i, array[i - 1], array[i]);
    }
  }
}
void init_random_vector(int n, int array[]) {
  int i;
  for (i = 0; i < n; i++) {
    array[i] = (rand() % 100);
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
	print_array(n, array);
	bubbleSort_Par(array, n, threads);
	print_array(n, array); 
	double endBubble = omp_get_wtime();
	
	printf("BubbleSort: Total time to solve with %d OpenMP threads was %.6f\n", threads, (endBubble - startBubble));
	
	if (n < 50000)
	{
		test_correctness(n, array);
	}
	
	free(array);
	
	int *combArray = (int *)malloc(sizeof(int) * n);
	
	init_random_vector(n, combArray);
	
	double startComb = omp_get_wtime();
	print_array(n, combArray);
	combSort_Par(combArray, n, threads);
	print_array(n, combArray); 
	double endComb = omp_get_wtime();
	
	printf("CombSort: Total time to solve with %d OpenMP threads was %.6f\n", threads, (endComb - startComb));
	
	if (n < 50000)
	{
		test_correctness(n, combArray);
	}
	
	free(combArray);
	
	int *shellArray = (int *)malloc(sizeof(int) * n);
	
	init_random_vector(n, shellArray);
	
	double startShell = omp_get_wtime();
	print_array(n, shellArray);
	shellSort_Par(shellArray, n, threads);
	print_array(n, shellArray); 
	double endShell = omp_get_wtime();
	
	printf("ShellSort: Total time to solve with %d OpenMP threads was %.6f\n", threads, (endShell - startShell));
	
	if (n < 50000)
	{
		test_correctness(n, shellArray);
	}
	
	free(shellArray);
	
	return 0;
	
}
