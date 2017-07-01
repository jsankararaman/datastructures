#include <stdio.h>
#include <stdlib.h>

struct node
{
    struct node *left;
    struct node *right;
    int num;
    int count;
};

void
inorder(struct node *tree)
{
    if (tree == NULL) {
	return;
    }

    inorder(tree->left);
    printf("%d %d\n", tree->num, tree->count);
    inorder(tree->right);
}

void
preorder(struct node *tree)
{
    if (tree == NULL) {
	return;
    }

    printf("%d %d\n", tree->num, tree->count);
    preorder(tree->left);
    preorder(tree->right);
}

void
postorder(struct node *tree)
{
    if (tree == NULL) {
	return;
    }

    postorder(tree->left);
    postorder(tree->right);
    printf("%d %d\n", tree->num, tree->count);
}

struct node *
treeadd(struct node *tree, int num)
{
    if (tree == NULL) {
	tree = (struct node *)malloc(sizeof(struct node));
        tree->left = tree->right = NULL;
        tree->num = num;
	tree->count = 1;
        return tree;
    }

    if (tree->num == num) {
	tree->count++;
        return tree;
    }

    if (tree->num < num) {
        tree->right = treeadd(tree->right, num);
        return tree;
    }
 
    tree->left = treeadd(tree->left, num);
    return tree;   
}

#define NUM 100

int main()
{
    struct node *tree = NULL;
    int i;

    srand(time(NULL));

    for (i = 0; i < NUM; i++) 
	tree = treeadd(tree, rand());

    inorder(tree);
    preorder(tree);
    postorder(tree);
    return 0;
}
