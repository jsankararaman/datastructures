#include <stdio.h>
#include <stdlib.h>

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

int main()
{
    int i;
    struct queue q;

    queueinit(&q);
    srand(time(NULL));

    for (i = 0; i < NUM - 1; i++) {
	 enqueue(&q, rand());
    }

    for (i = 0; i < NUM - 1; i++) {
	 printf("%d\n", dequeue(&q));
    }
}
