#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *
createlist(int num)
{
    int i, j, val;
    struct node *list = NULL, *temp = NULL, *temp2 = NULL;
    for (i = 0; i < num; i++) {
         temp = (struct node *)malloc(sizeof(struct node));
         temp->next = NULL;
         temp->data = i;
         if (temp2) {
	     temp2->next = temp;
         } else {
	     list = temp; 
         }
         temp2 = temp;
    }
    return list;
}

void printlist(struct node *list)
{
    int i;
    struct node *temp = list;
    while (temp) {
	printf("%d\n", temp->data);
	temp = temp->next;
    }
}

struct node *reverselist(struct node *list)
{
    struct node *prev = NULL, *current = list, *next = NULL;

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
    struct node *list = createlist(100);

    printlist(list);
    struct node *rev = reverselist(list);
    printlist(rev);   
}
