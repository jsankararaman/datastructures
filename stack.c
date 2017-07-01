#include <stdio.h>
#include <stdlib.h>

#define NUM 100

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

int main()
{
    int i;
    struct stack st;

    stackinit(&st);
    srand(time(NULL));

    for (i = 0; i < NUM; i++) {
	 push(&st, rand());
    }

    for (i = 0; i < NUM; i++) {
	 printf("%d\n", pop(&st));
    }
}
