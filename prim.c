#include <stdio.h>
#include <stdlib.h>

#define NUM_VERTEX 9
#define INFINITY   100

int graph[NUM_VERTEX][NUM_VERTEX] = {
                       {0, 4,  0, 0,  0,  0,  0, 8,  0},
                       {4, 0,  8, 0,  0,  0,  0, 11, 0},
                       {0, 8,  0, 7,  0,  4,  0, 0,  2},
                       {0, 0,  7, 0,  9,  14, 0, 0,  0},
                       {0, 0,  0, 9,  0,  10, 0, 0,  0},
                       {0, 0,  4, 14, 10, 0,  2, 0,  0},
                       {0, 0,  0, 0,  0,  2,  0, 1,  6},
                       {8, 11, 0, 0,  0,  0,  1, 0,  7},
                       {0, 0,  2, 0,  0,  0,  6, 7,  0}};

#define left(i)   2*i
#define right(i) (2*i + 1)
#define parent(i) (i/2)

struct
vertex
{
   int vertice;
   int cost;
};

void
swap(struct vertex *key[NUM_VERTEX], int i, int j)
{
    struct vertex temp_vertex = *key[i];

    *key[i] = *key[j];
    *key[j] = temp_vertex;
}

void
min_heapify(struct vertex *key[NUM_VERTEX], int i, int heapsize)
{
   int minimum = i;

   if ((left(i) < heapsize) && (key[left(i)]->cost < key[i]->cost)) {
	minimum = left(i);
   }

   if ((right(i) < heapsize) && (key[right(i)]->cost < key[minimum]->cost)) {
	minimum = right(i);
   }

   if (i != minimum) {
       swap(key, i, minimum);
       min_heapify(key, minimum, heapsize);
   }
}

void
build_minheap(struct vertex *key[NUM_VERTEX])
{
   int i;

   for (i = NUM_VERTEX/2; i >= 0; i--)
	min_heapify(key, i, NUM_VERTEX);
}

int
extract_min(struct vertex *key[NUM_VERTEX], int heapsize)
{
    int minimum;

    if (heapsize == 0) {
	printf("Heap underflow error\n");
	return -1;
    }

    minimum = key[0]->vertice;
    *key[0] = *key[heapsize - 1];
    heapsize--;

    min_heapify(key, 0, heapsize); 
    return minimum;
}

void 
decrease_key(struct vertex *key[NUM_VERTEX], int i, int value, int heapsize)
{
    if (heapsize == 0) {
	printf("Heap underflow error\n");
	return;
    }

    key[i]->cost = value;
    while ((i >= 0) && (key[parent(i)]->cost > key[i]->cost)) {
	swap(key, i, parent(i));
        i = parent(i);
    }
}

int 
main()
{
    struct vertex *key[NUM_VERTEX];
    int pi[NUM_VERTEX];
    int i, node, heapsize, j;

    for (i = 0; i < NUM_VERTEX; i++) {
	 key[i] = (struct vertex *)malloc(sizeof(struct vertex));
         key[i]->vertice = i;
         key[i]->cost = INFINITY;
	 pi[i] = -1;
    }
    
    key[0]->cost = 0;
    pi[0] = 0;
   
    heapsize = NUM_VERTEX;
    build_minheap(key);
     
    while (heapsize > 0) {
	node = extract_min(key, heapsize--);
        printf("%d %d\n", pi[node], node);
        for (i = 0; i < NUM_VERTEX; i++) {
	     if (graph[node][i]!=0) {
		 for (j = 0; j < heapsize; j++) {
		      if ((key[j]->vertice == i) && (graph[node][i] < key[j]->cost)) {
			   decrease_key(key, j, graph[node][i], heapsize);
		           pi[i] = node;
		      }
		 }
             }
        }
    }
}
