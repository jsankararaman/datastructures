#include <stdio.h>
#include <stdlib.h>

#define NUM 100

void
generate_array(int array[NUM], int num)
{
    int i;

    srand(time(NULL));
    for (i = 0; i < num; i++) 
	 array[i] = rand();
}

int
binary_search(int array[NUM], int left, int right, int key)
{
    int middle;

    while (left <= right) {
	middle = (left + right) / 2;
	if (array[middle] == key) 
	    return middle;
	if (array[middle] < key) {
	    left = middle + 1;
	}
	if (array[middle] > key) {	
	    right = middle - 1;
	}
    }
    return -1;
}

void
swap(int array[], int i, int j)
{
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}


void
merge(int array[NUM], int left1, int right1, int left2, int right2)
{
    int i, j, k, iter = 0;
    int result[NUM];

    for (i = left1, j = left2, k = 0; (i <= right1) && (j <=right2); )
    {
        if (array[i] <= array[j]) {
	    result[k++] = array[i++];
	    continue;
        }
        result[k++] = array[j++];
    }

    while (i <= right1) {
	result[k++] = array[i++];
    }

    while (j <= right2) {
	result[k++] = array[j++];
    }

    for (iter = 0, i = left1; iter < k; iter++, i++) {
	
	array[i] = result[iter];
    }
}

void
mergesort(int array[NUM], int left, int right)
{
    int middle = (left + right)/2;

    if (left >= right)
	return;

    mergesort(array, left, middle);
    mergesort(array, middle + 1, right);
    merge(array, left, middle, middle + 1, right);
}

void
insertsort(int array[NUM], int left, int right)
{
    int i, j;

    for (i = left; i < right; i++)
	 for (j = i + 1; j >= left;  j--) {
	      if (array[j] < array[j - 1]) {
		  swap(array, j, j - 1);	
		  continue;
	      }
	      break;
	 }
}

#define LEFT(i)		(2*i)
#define RIGHT(i)	(2*i + 1)
#define PARENT(i)       (i/2)

void
heapify(int array[NUM], int i, int max)
{
    int maximum = i;
    int left = LEFT(i);
    int right = RIGHT(i);

    if ((left <= max) && (array[left] > array[i]))  {
	 maximum = left;
    }
    if ((right <= max) && (array[right] > array[maximum]))  {
	 maximum = right;
    }

    if (maximum != i) {
	swap(array, i, maximum);
	heapify(array, maximum, max);
    }
}

void
heapsort(int array[NUM], int left, int right)
{
    int i, j, k;

    for (i = right/2; i>=left; i--) 
	 heapify(array, i, right);

    for (k = left; k <= right; k++) {
	 swap(array, left, right - k);
	 heapify(array, left, right-k- 1);
    }
}

void
quicksort(int array[NUM], int left, int right)
{
    int middle = (left + right)/2;
    int i;
    int pivot;

    if (left >= right)
	return;

    swap(array, left, middle);
    pivot = left;
    for (i = left + 1; i <= right; i++) {
	 if (array[i] < array[left]) 
	     swap(array, i, ++pivot);
    } 
    
    swap(array, left, pivot);
    quicksort(array, left, pivot - 1);
    quicksort(array, pivot + 1, right);
}

int main()
{
    int array[NUM], i;

    generate_array(array, NUM);

    for (i = 0; i < NUM; i++) {
        printf("%d %d\n", i, array[i]);
    }

    heapsort(array, 0, NUM - 1);

    for (i = 0; i < NUM; i++) {
        printf("%d %d\n", i, array[i]);
    }

    for (i = 1; i < NUM; i++) { 
	if (array[i] < array[i - 1]) {
	    printf("Not sorted %d < %d, %d %d\n", array[i], array[i - 1], i, i - 1);
	    return -1;
        }
    }
    printf("Sorted successfully\n");

    printf("%d\n", binary_search(array, 0, NUM - 1, array[84]));
    return 0;
}
