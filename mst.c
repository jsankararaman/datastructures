#include <stdio.h>
#include <stdlib.h>

#define NUM_VERTEX 9

int parent[NUM_VERTEX];
int rank[NUM_VERTEX];

void
make_set()
{
    int i;

    for (i = 0; i < NUM_VERTEX; i++) {
	parent[i] = i;
	rank[i] = 0;
    }
}

void
link(int x, int y)
{
    if (rank[x] > rank[y]) {
        parent[y] = x;
    } else {
	parent[x] = y;
	if (rank[x] == rank[y])
	    rank[y]++;	
    }
}

void
union_set(int x, int y)
{
    link(find_set(x), find_set(y));
}

int
find_set(int i)
{
    if (parent[i] == i) {
	return i;
    }
    parent[i] = find_set(parent[i]);
    return parent[i];
}

int array[NUM_VERTEX][NUM_VERTEX] = {
		       {0, 4,  0, 0,  0,  0,  0, 8,  0},
		       {4, 0,  8, 0,  0,  0,  0, 11, 0},
		       {0, 8,  0, 7,  0,  4,  0, 0,  2},
		       {0, 0,  7, 0,  9,  14, 0, 0,  0},
		       {0, 0,  0, 9,  0,  10, 0, 0,  0},
		       {0, 0,  4, 14, 10, 0,  2, 0,  0},
		       {0, 0,  0, 0,  0,  2,  0, 1,  6},
		       {8, 11, 0, 0,  0,  0,  1, 0,  7},
		       {0, 0,  2, 0,  0,  0,  6, 7,  0}};

struct edge
{
    int i;
    int j;
    int weight;
    struct edge *next;
};

struct edge *
sorted_listadd(struct edge *list, int i, int j, int weight)
{
    struct edge *temp;

    if (list == NULL) {
	list = (struct edge *)malloc(sizeof(struct edge));
        list->i = i;
        list->j = j;
	list->weight = weight;
        return list;
    }
    if (list->weight < weight) {
        list->next = sorted_listadd(list->next, i, j, weight);
        return list;
    } else {
	temp = sorted_listadd(NULL, i, j, weight);
	temp->next = list;
        return temp;
    }
}

struct edge *
create_edges(int array[NUM_VERTEX][NUM_VERTEX])
{
    int i, j;
    struct edge *list = NULL;
    
    for (i = 0; i < NUM_VERTEX; i++) {
	 for (j = 0; j < i; j++) {
	     if (array[i][j]!=0) {
	         list = sorted_listadd(list, i, j, array[i][j]);	     
             }
         }
    }
    return list;    
}

void
printlist(struct edge *list)
{
    while (list) {
	printf("%d %d %d\n", list->i, list->j, list->weight);
        list = list->next;
    }
}

int main()
{
    struct edge *list, *temp;
    int i;

    for (i = 0; i < NUM_VERTEX; i++)
	make_set();

    list = create_edges(array);                
    for (temp = list; temp!=NULL; temp = temp->next) {
	 if (find_set(temp->i) != find_set(temp->j)) {
 	     printf("Edge %d %d\n", temp->i, temp->j);
	     union_set(temp->i, temp->j);	     
         }
    }
    return 0;
}
