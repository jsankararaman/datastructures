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
quicksort(int array[], int left, int right)
{
    int middle = (left + right)/2;
    int i, pivot;

    if (left >= right)
	return;

    swap(array, left, middle);
    pivot = left;
    for (i = left + 1; i <= right; i++) {
	if (array[i] < array[left]) 
	    swap(array, i, ++pivot);
    }

    swap(array, left, pivot);
    quicksort(array, left, pivot-1);
    quicksort(array, pivot + 1, right);
}

int main()
{
    int array[NUM], i;

    generate_array(array, NUM);

    for (i = 0; i < NUM; i++) {
        printf("%d %d\n", i, array[i]);
    }

    quicksort(array, 0, NUM - 1);

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
