//Author Eric
#include <cstdlib>
#include <ctime>
#include <utility>
#include <iostream>
#include <vector>
#include <algorithm>


int ITERATE = 10; //number of iterations for each test. 
int LEN_CONST [7] = {1, 5, 10, 100, 1000, 10000, 100000};
int LEN_CONST_LEN = 7;
int MAXVAL = 10000;

int testArray[3] = {1, 10, 100};
int testArrLen = 3;
std::clock_t start;
std::clock_t end; 
double durationAvg;
double duration;

void print_array(int n, int array[]) {
  int i;
  printf("[%d", array[0]);
  for (i = 1; i < n; i++) {
    printf(", %d", array[i]);
  }
  printf("]\n");
}


int * generateRandomArray(int len){

  int * tbr = new int [len];
  for(int k = 0; k< len; k++){
    tbr[k] = (rand()%MAXVAL)+1;
  }
  return tbr; 
}

int * generateSortedArray(int len){
  int * tbr = new int [len];
  for (int k = 0; k < len; k++){
    tbr[k] = k; 
  }
  return tbr;
}

int * generateBackwardsArray(int len){
  int * tbr = new int[len];
  for (int k = 0; k< len; k++){
    tbr[k] = len-k;
  }
  return tbr; 
} 
  

void sortRun(int* lenArrs, int lenArrsLen, void (*sortFun)(int*, int),
	     int* (*genFun)(int) ){
  duration = 0;
  durationAvg = 0; 
    for(int i = 0; i < lenArrsLen; i++){
       for(int k = 0; k < ITERATE; k++){
	 //loop for each Len in LEN_CONST
	 //create a new array, populate array
	 int* tbs = genFun(lenArrs[i]); 
	 // print_array(lenArrs[i],tbs); 
	 start = clock(); 
	 sortFun(tbs, lenArrs[i]);
	 end = clock(); 
	 durationAvg += ( end - start ) / (double) CLOCKS_PER_SEC;
	 free(tbs);
      //print_array(lenArrs[i],tbs);
       }
       duration = durationAvg/ITERATE;
       std::cout<<"time: "<< duration<<" length: " << lenArrs[i]<<'\n';
    }
    
}


 


  

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 

//Website linked above

// A function to implement bubble sort

//http://www.geeksforgeeks.org/bubble-sort/
void bubbleSort(int arr[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)      
 
       // Last i elements are already in place   
       for (j = 0; j < n-i-1; j++) 
           if (arr[j] > arr[j+1])
	     swap(&arr[j], &arr[j+1]);
}


//https://en.wikibooks.org/wiki/Algorithm_Implementation/Sorting/Comb_sort
// Function to sort a[0..n-1] using Comb Sort

// To find gap between elements
int getNextGap(int gap)
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
	      int temp = a[i];
	      a[i] = a[i+gap];
	      a[i+gap] = temp; 
              swapped = true;
            }
        }
    }
}
//https://geeksforgeeks.org/shellsort
/* function to sort arr using shellSort */
void shellSort(int arr[], int n)
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
    return;
}
 
int main(){

  printf("Running BubbleSort Tests\n");
  printf("BubbleSort Random.\n"); 
  sortRun(LEN_CONST, LEN_CONST_LEN, bubbleSort, generateRandomArray);
  printf("BubbleSort Sorted\n");
  sortRun(LEN_CONST, LEN_CONST_LEN, bubbleSort, generateSortedArray);
  printf("BubbleSort Sorted\n"); 
  sortRun(LEN_CONST, LEN_CONST_LEN, bubbleSort, generateBackwardsArray);
  printf("Running ShellSort Tests\n");
  printf("ShellSort Random.\n"); 
  sortRun(LEN_CONST, LEN_CONST_LEN,shellSort, generateRandomArray);
  printf("ShellSort Sorted:\n");
  sortRun(LEN_CONST, LEN_CONST_LEN, shellSort, generateSortedArray);
  printf("ShellSort Backwards:\n");
  sortRun(LEN_CONST, LEN_CONST_LEN, shellSort, generateBackwardsArray);
  printf("Running Combsort Tests\n");
  printf("combSort Random:\n"); 
  sortRun(LEN_CONST, LEN_CONST_LEN, combSort, generateRandomArray);
  printf("combSort Sorted:\n");
  sortRun(LEN_CONST, LEN_CONST_LEN, combSort, generateSortedArray);
  printf("combSort Backwards: \n");
  sortRun(LEN_CONST, LEN_CONST_LEN, combSort, generateBackwardsArray);
  printf("Done tests\n"); 
  return 0; 

}
