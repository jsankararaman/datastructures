#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM 100

struct node 
{
    struct node *next;
    int num;
};

void
listprint(struct node *list)
{
    int i = 0;

    while (list) {
	printf("%d %d\n", i++, list->num);
        list = list->next;
    }
}

struct node *
list_add(struct node *list, int num)
{
    if (list == NULL) {
        list = (struct node *)malloc(sizeof(struct node));
        list->next = NULL;
        list->num = num;
        return list;	
    }
    list->next = list_add(list->next, num);
    return list;
}

struct node *
list_reverse(struct node *list) 
{
    struct node *next, *prev, *current;

    prev = NULL;
    current = list;

    while (current) {
	next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}

int main()
{
    struct node *list = NULL;
    int i;

    srand(time(NULL));
    for (i = 0; i < NUM; i++) {
	list = list_add(list, rand());
    }    

    listprint(list);
    list = list_reverse(list);
    listprint(list);

    return 0;
}
