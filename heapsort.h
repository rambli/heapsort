/**
* @file heapsort.h
* @brief Header file for heapsort utility stuff
* @author Rohan Ambli
*/

#ifndef _HEAPSORT_H_
#define _HEAPSORT_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/** Binary tree, thus number of children is 2 */
#define NUM_LINKS (2)

/** If DEBUG is defined, printf will print, else will be commented out */
#define DEBUG
#ifdef DEBUG
 #define PRINT printf
#else
 #define PRINT //
#endif

#define NEXT	1
#define PREV	0

#define LEFT	0
#define RIGHT	1

/** Determine whether to go left or right while adding/looking for a child */
#define DIR(node_data, parent_data) \
	(node_data > parent_data)?RIGHT:LEFT

/**
	\brief struct node: the basic building block of our tree
	\param link - The left and right children links: [Left child of parent x: [2x+1] Right child: [2x+2]
	\param parent - Parent link of node x, one level up: [(x-1)/2]	
	\param data - node data
*/

typedef struct node
{
	/** The left and right children links: [Left child of parent x: [2x+1] Right child: [2x+2]
	    The next and previous nodes in the case of a linked list. */
	struct node *link[NUM_LINKS];
	/** When used as a node in a binary tree, parent of node x, one level up: [(x-1)/2] */
	struct node *parent;
	/** Node data */
	int data;
}node;

/** enum bool: define true and false
*/
typedef enum _bool
{
	FALSE = 0,
	TRUE
}bool;

// Common functions
node* new();

// Heap functions
void normalize_tree(node *norm_node);
node* get_parent(node *ndata);
node* get_rchild(node *parent);
node* get_lchild(node *parent);
bool is_leaf_node(node *n);
void free_nodes(node *root);
void print_tree(node *root);
node* create_node(int data, node *parent);
void add_node(node **root, int data, node *parent);
node* find_node(node *root, int data);
void swap(node *child, node *parent);
void normalize_tree(node *norm_node);

// Linked list functions
void append_link_node(node **head, int data, node *parent);
void print_nodes(node **head, int data, node *dontcare);
void free_link_nodes(node **head, int data, node *dontcare);
void insert_node(node **head, int data, node *dontcare);
void delete_node(node **head, int data, node *dontcare);

#endif // _HEAPSORT_H_
