#include <stdio.h>
#include <stdlib.h>

#define NUM 100

void 
swap(int array[], int i, int j)
{
    int temp;

    temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void 
insertion_sort(int array[], int num)
{
    int i, j, k;

    for (i = 1; i < NUM; i++) {
	for (j = i; (j > 0); j--) {
	    if (array[j] < array[j - 1]) {
		swap(array, j, j -1);
	    } else {
                break; 
	    }
        }
    }
}

void
merge(int array[], int left1, int right1, int left2, int right2)
{
    int i, j, k;
    int result[NUM];

    for (i = left1, j = left2, k = 0; (i < right1) && (j < right2); ) {
	 if (array[i] <= array[j]) {
	     result[k++] = array[i++];     
	     continue;
         }
         result[k++] = array[j++];
    }

    while (i < right1) {
	result[k++] = array[i++];
    }

    while (j < right2) {
	result[k++] = array[j++];
    }

    for (i = left1, j = 0; j < k; j++, i++) {
        array[i] = result[j];
    }
}

void
merge_sort(int array[], int left, int right)
{
    int middle = (left + right)/2;

    if (left == right - 1) {
        return;
    }

    merge_sort(array, left, middle);
    merge_sort(array, middle, right);
    merge(array, left, middle, middle, right);
}

#define LEFT(i) (2*i)
#define RIGHT(i) (2*i + 1)

void max_heapify(int array[], int i, int num)
{
    int j, k;
    int maximum = i;

    if ((LEFT(i) < num) && (array[i] < array[LEFT(i)])) {
        maximum = LEFT(i);
    }        

    if ((RIGHT(i) < num) && (array[RIGHT(i)] > array[maximum])) {
        maximum = RIGHT(i);
    }

    if (maximum != i) {
        swap(array, i, maximum);
        max_heapify(array, maximum, num);
    }
}

void
heapsort(int array[], int num)
{
    int i; 

    for (i = num/2; i >= 0; i--) {
         max_heapify(array, i, num);
    }    

    for (i = num - 1; i >= 0; i--) {
         swap(array, 0, i);
         max_heapify(array, 0, i);
    }   
}

void
quicksort(int array[], int left, int right)
{
    int middle = (left + right)/2;
    int pivot, i;

    if (left >= right - 1) {
	return;
    }

    swap(array, left, middle);
    pivot = left;
    for (i = left + 1; i < right; i++) {
         if (array[i] < array[left]) {
	     swap(array, ++pivot, i);
         }
    }

    swap(array, left, pivot);
    quicksort(array, left, pivot);
    quicksort(array, pivot, right);
}

void 
generate_array(int array[], int num)
{
    int i;
    srand(time(NULL));

    for (i = 0; i < NUM; i++) {
	array[i] = rand();
    }
}

int
binary_search(int array[], int left, int right, int key)
{
    int middle;

    while (left <= right) {
         middle = (left + right)/2;
         if (array[middle] == key) 
	     return middle;
         if (array[middle] < key) {
	     left = middle + 1;
             continue;
         }
	 right = middle - 1;
    }
    return -1;
}

int main()
{
    int array[NUM], i;

    generate_array(array, NUM);

    for (i = 0; i < NUM; i++) {
        printf("%d %d\n", i, array[i]);
    }

    quicksort(array, 0, NUM);

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
