##Author: Eric Kurtz
##Sequential Sorts for CISC 360 Project Gathered from internet, github
##for testing.



#http://www.geeksforgeeks.org/bubble-sort/

#bubbleSort: LoN, Num -> LoN
#consumes: LoN, a list of numbers. n, the length of the list
#produces: sorted list of numbers
def bubbleSort(arr, n):
 
    # Traverse through all array elements
    for i in range(n):
 
        # Last i elements are already in place
        for j in range(0, n-i-1):
 
            # traverse the array from 0 to n-i-1
            # Swap if the element found is greater
            # than the next element
            if arr[j] > arr[j+1] :
                arr[j], arr[j+1] = arr[j+1], arr[j]

#https://rosettacode.org/wiki/Sorting_algorithms/Comb_sort#Python

#combsort: LoN, Num -> LoN
#consumes: LoN, a list of numbers. n, the length of the list
#produces: sorted list of numbers

def combsort(arr, n):
    gap = n
    swaps = True
    while gap > 1 or swaps:
        gap = max(1, int(gap / 1.25))  # minimum gap is 1
        swaps = False
        for i in range(n - gap):
            j = i+gap
            if arr[i] > arr[j]:
                arr[i], arr[j] = arr[j], arr[i]
                swaps = True



#http://www.geeksforgeeks.org/shellsort/

#shellsort: LoN, Num -> LoN
#consumes: LoN, a list of numbers. n, the length of the list
#produces: sorted list of numbers

def shellSort(arr,n):
 
    # Start with a big gap, then reduce the gap
    gap = n/2
 
    # Do a gapped insertion sort for this gap size.
    # The first gap elements a[0..gap-1] are already in gapped 
    # order keep adding one more element until the entire array
    # is gap sorted
    while gap > 0:
 
        for i in range(gap,n):
 
            # add a[i] to the elements that have been gap sorted
            # save a[i] in temp and make a hole at position i
            temp = arr[i]
 
            # shift earlier gap-sorted elements up until the correct
            # location for a[i] is found
            j = i
            while  j >= gap and arr[j-gap] >temp:
                arr[j] = arr[j-gap]
                j -= gap
                
            # put temp (the original a[i]) in its correct location
            arr[j] = temp
        gap /= 2
