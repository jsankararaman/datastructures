#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM 100

struct queue
{
    int array[NUM];
    int begin;
    int end;
};

void
queueinit(struct queue *q)
{
    q->begin = 0;
    q->end = 0;
}

/*
 * Page 203 of CLRS
 */
void
enqueue(struct queue *q, int num)
{
    if (q->begin == (q->end + 1) % NUM) {
	printf("Queue overflow error\n");
	return;
    }

    q->array[q->end] = num;
    q->end = (q->end + 1) % NUM;
}

int 
dequeue(struct queue *q)
{
    if (q->begin == q->end) {
	printf("Queue underflow error\n");
	return -1;
    }

    return q->array[q->begin++];
}

/* 
 * how many elements are in the queue
 */
int
qsize(struct queue *q)
{
    if (q->end < q->begin) {
	return (NUM - q->begin) + q->end;
    }   

    return (q->end - q->begin); 
}

/*
       0  1  2  3
    0     1  1 
    1        1
    2  1        1
    3           1

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
*/

struct stack
{
    int array[NUM];
    int sz;
};

void
stackinit(struct stack *st)
{
    st->sz = 0;
}

void
push(struct stack *st, int num)
{
    if (st->sz == NUM) {
        printf("Stack overflow error\n");
        return;
    }

    st->array[st->sz++] = num;
}

int
pop(struct stack *st)
{
    if (st->sz == 0) {
        printf("Stack underflow error\n");
        return -1;
    }

    return st->array[--st->sz];
}

void 
bfs(int array[NUM][NUM])
{
    int i;
    struct queue q;
    bool visited[4];
    int element;

    queueinit(&q);
    for (i = 0; i < 4; i++) 
         visited[i] = false;
 
    enqueue(&q, 2);
    visited[2] = 1;

    while (qsize(&q) > 0) {
	element = dequeue(&q);
        printf("Breadth First Search %d\n", element);
        for (i = 0; i < 4; i++) {
	    if (!visited[i] && (array[element][i]==1)) {
		enqueue(&q, i);
		visited[i] = 1;
	    }
        }	
    }
}

void
dfs(int array[NUM][NUM])
{
    struct stack st;
    bool visited[4];
    int element;
    int i;

    stackinit(&st);
    for (i = 0; i < 4; i++) 
         visited[i] = false;

    push(&st, 2);
    visited[2] = 1;
    while (st.sz > 0) {
       element = pop(&st);
       printf("Depth First Search %d\n", element);
       for (i = 0; i < 4; i++) {
	    if (!visited[i] && (array[element][i] == 1)) {
		push(&st, i);
		visited[i] = 1;
	    }
       }       
    }    
}

bool visited[4];

void
dfs_recursive(int array[NUM][NUM], int i)
{
    int iter;

    printf("DSF recursive %d\n", i);
    visited[i] = 1;

    for (iter = 0; iter < 4; iter++) {
	if ((array[i][iter] == 1) && !visited[iter]) {
	     dfs_recursive(array, iter);
	}
    }
}

int main()
{
    int array[NUM][NUM] = {{0, 1, 1, 0},
			   {0, 0, 1, 0},
			   {1, 0, 0, 1},
			   {0, 0, 0, 1}};
    int i;
    for (i = 0; i < 4; i++)
	 visited[i] = false;
    bfs(array);
    dfs(array);
    dfs_recursive(array, 2);
}
