
//Author Eric, Sam
#include <cstdlib>
#include <ctime>
#include <utility>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include<omp.h>
#include <stdlib.h>
#include <string.h>

int ITERATE = 10; //number of iterations for each test. 
int LEN_CONST [8] = {1,10,100,1000,5000,10000,100000,1000000};
int LEN_CONST_LEN = 8;
int MAXVAL = 10000;
int NUMTHREADS = 4; 

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

int newgap(int gap)
{
    gap = (gap * 10) / 13;
    if (gap == 9 || gap == 10)
        gap = 11;
    if (gap < 1)
        gap = 1;
    return gap;
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

void combSort_Par(int array[], int n, int threads)
{
    int gap;
	int temp, i, j, m, h, g, o;
    bool swapped;
	#pragma omp parallel shared(array, n, gap) private(o, temp, j, m, i, h, g, swapped) num_threads(threads)
	for(o = 0;o=1;)//basically while(true)
	{
		gap = newgap(gap);
		swapped = 0;
		for(i = 0; i < n-gap; i++)
		{
			if(i%2 == 0)
			{
				
				#pragma omp for
				for(m = 0; m <= (n-gap); m++)
				{
					g = m + gap;
					if(array[m] > array[g])
					{
						temp = array[m];
						array[m] = array[g];
						array[g] = temp;	
						swapped = 1;
					}
				}
			}
			else
			{
				#pragma omp for
				for(h = 0; h <= (n-gap); h++)
				{
					j = h + gap;
					if(array[h] > array[j])
					{
						temp = array[h];
						array[h] = array[j];
						array[j] = temp;	
						swapped = 1;
					}
				}
			}
		}
		if(gap == 1 && !swapped)
		{
			o=1;
			break;
		}
	}
}

void parSortRun(int* lenArrs, int lenArrsLen, void (*sortFun)(int*, int, int), int* (*genFun)(int) )
{
	int* tbs;
	int a, b;
	 
	for(a = 0; a < lenArrsLen; )
	 
	{
	  duration = 0;
	  durationAvg = 0; 
		for(b = 1; b <= ITERATE; )
		{
			tbs = genFun(lenArrs[a]);  
			start = omp_get_wtime(); 
			sortFun(tbs, lenArrs[a], NUMTHREADS);
			end = omp_get_wtime(); 
			durationAvg += ( end - start ) / (double) CLOCKS_PER_SEC;
			
			b++;
		}
		duration = durationAvg/ITERATE;
		printf("time:  %F  length:  + %d + \n", duration, lenArrs[a]);
		a++;
    }
	free(tbs);
    
}

int main(){
  parSortRun(LEN_CONST, LEN_CONST_LEN, combSort_Par, generateBackwardsArray); 
}
