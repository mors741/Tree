/* 
 * File:   main.cpp
 * Author: evgeny
 *
 * Created on April 24, 2013, 12:10 AM
 * Semestr 2
 * Laba 2
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
struct node
{
    int data;
    struct node *left;
    struct node *right;
};
void show (struct node *tree)
{
    if (tree != NULL)
    {
        show(tree->left);
        printf("%i, ",tree->data);
        show(tree->right);
    }
}
struct node *new_node(int data)
{
    struct node *pointer = (struct node*)malloc(sizeof(struct node));
    pointer->data=data;
    pointer->left=NULL;
    pointer->right=NULL;
    return pointer;
}
void add_node(struct node **tree, int data)
{
    if (*tree == NULL)
        *tree = new_node(data);
    else
    {
        if (data < (*tree)->data)
            add_node(&((*tree)->left),data);
        else 
            if ((*tree)->data != data)
                add_node(&((*tree)->right),data);
    }
}
struct node *find_node(struct node *tree, int data)
{
    if (tree!=NULL)
    {
        if (tree->data == data)
            return tree;
        else
            if (data < tree->data)
                return find_node(tree->left,data);
            else
                return find_node(tree->right,data);
    }
    else return NULL;
}
int get_size(struct node *tree)
{
    if (tree == NULL)
        return 0;
    else
        return (get_size(tree->left) + get_size(tree->right) + 1);
}
int count_list(struct node *tree)
{
    if (tree == NULL)
        return 0;
    else
    {
        if ((tree->left==NULL)&&(tree->right==NULL))
            return 1;
        else
            return count_list(tree->left) + count_list(tree->right);
    }
}
struct node *find_prev(struct node *tree, struct node *pointer)
{
    if (pointer == tree)
        return NULL;
    if (tree == NULL)
        return NULL;
    else
    {
        if((pointer==tree->right)||(pointer==tree->left))
                return tree;
        else
        {
            struct node *pointer_left = find_prev(tree->left,pointer);
            if ( pointer_left!=NULL)
                return pointer_left;
            else
                return find_prev(tree->right,pointer);
        }
    }
}
struct node *check_elem(struct node *tree)
{
    if ((tree->right==NULL)&&(tree->left==NULL))
            return NULL;
    else
    {
        if (tree->right!=NULL)
        {
            tree=tree->right;
            while (tree->left!=NULL)
                tree=tree->left;
            return tree;
        }
        else
        {
            tree=tree->left;
            while (tree->right!=NULL)
                tree=tree->right;
            return tree;
        }
    }
}
struct node* delete_elem(struct node* tree, int data)
{
    struct node* p;
    struct node* p2;
    if(tree==NULL) 
        return tree; 
    if(tree->data == data) 
    { 
        if((tree->left==NULL)&&(tree->right==NULL))
        {
            free(tree);
            return NULL;
        }
        else if(tree->left == NULL) 
        {
            p = tree->right;
            free(tree);
            return p;
        }
        else if(tree->right == NULL) 
        {
            p = tree->left;
            free(tree);
            return p;
        }
        else
        {
            p2 = tree->right;
            p = tree->right;
            while(p->left!=NULL) p = p->left;
                p->left = tree->left;
            free(tree);
            return p2;
        }
    }
    if(tree->data < data) 
        tree->right = delete_elem(tree->right, data);
    else 
        tree->left = delete_elem(tree->left, data);
    return tree;
}
int main()
{
    struct node *tree = NULL;
    add_node(&tree, 1);
    add_node(&tree, 2);
    add_node(&tree, -1);
    add_node(&tree, 10);
    add_node(&tree, -9);
    add_node(&tree, 4);
    add_node(&tree, 0);
    add_node(&tree, 11);
    add_node(&tree, -11);
    add_node(&tree, -111);
    show (tree);
    printf("\n---------------------------------------\n");
    printf ("All nodes: %i\nEnds of branches: %i\n",get_size(tree),count_list(tree));
    delete_elem(tree,-111);
    show (tree);
    printf("\n---------------------------------------\n");
    return 0;
}
