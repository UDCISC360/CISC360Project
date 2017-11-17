//Author Eric
#include <cstdlib>
#include <ctime>
#include "SeqSorts.cpp"


int LEN_CONST [7] = {1, 5, 10, 100, 1000, 10000, 100000};
int LEN_CONST_LEN = 7;
int MAXVAL = 10000;

int testArray[3] = {1, 10, 100};
int testArrLen = 3; 


int main(){
  return 0;

}

void sortRun(int* lenArrs, int lenArrsLen,
	     void (*sortFun)(int*, int) ){

  for(int i = 0; i < lenArrsLen; i++){
    //loop for each Len in LEN_CONST
    //create a new array, populate array
    int* tbs = new int [lenArrs[i]];
    for(int j =0; j<lenArrs[i]; j++){
      tbs[j] = (rand()%MAXVAL)+1;
    } 


    //Start time here

    sortFun(tbs, lenArrs[i]); 

    //end & print time here


  }


} 
