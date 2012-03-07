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

/*! Macros for linked list nodes */
#define NEXT	1
#define PREV	0

/*! Macros for binary tree nodes */
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

/*!*******************************************************
*	\fn new
*	\brief - allocate space and return a new node
*	\param void
*	\return node * - New Node
*********************************************************/
node* new();

/*!****************************************************************************
	\fn normalize_tree(node *norm_node)
	\brief - The passed in node is tested against its parent, and swapped if it is smaller
	       than the parent. This is done recursively until the condition is satisfied.
	\param norm_node - node to be normalized
	\return void
*****************************************************************************/
void normalize_tree(node *norm_node);

/*!****************************************************************************
	\fn normalize_tree_root(node *root)
	\brief - During sorting, the largest child is brought up to the root
		 as the root being the smallest is extracted. The tree needs to 
		 be normalized top-down so the the next smallest node floats to 
		 the top. This is in a way reverse of normalize_tree() where a
		 node is added to the bottom and checked if it needs to be sent up
		 top. Here we add a node to the top and check if it needs to be
		 sent lower in the tree.
	\param node* - tree root
	\return void
*****************************************************************************/
void normalize_tree_root(node *norm_node);

/*!*******************************************************
*	\fn get_parent(node *ndata)
*	\brief -  returns the nodes parent
*	\param ndata - Node to get parent of
*	\return node * - Node's parent	
*********************************************************/
node* get_parent(node *ndata);

/*!*******************************************************
*	\fn get_rchild(node *parent)
*	\brief -  returns the parent's right child
*	\param parent - parent node to get right-child of
*	\return node * - right child
*********************************************************/
node* get_rchild(node *parent);

/*!*******************************************************
*	\fn get_lchild(node *parent)
*	\brief -  returns the parent's left child
*	\param parent - parent node to get left child of
*	\return node * - left child
*********************************************************/
node* get_lchild(node *parent);

/*!*******************************************************
*	\fn get_smaller_child(node *)
*	\brief -  returns the smaller child
*	\param parent - Node to check
*	\return node * - L/R child
*********************************************************/
node* get_smaller_child(node *parent);

/*!*******************************************************
*	\fn get_larger_child(node *)
*	\brief -  returns the larger child
*	\param parent - Node to check
*	\return node * - L/R child
*********************************************************/
node* get_larger_child(node *parent);

/*!****************************************************************************
*	\fn get_last_child(node *root)
*	\brief - Find the lowest child of the tree (has to be a leaf node)
*	\param norm_node - tree root
*	\return - node * - lowest child
******************************************************************************/
node* get_last_child(node *root);

/*!****************************************************************************
*	\fn find_node(node *root, int data)
*	\brief -  Find the node which matches the passed in data.
*	\param root - tree root
*	\param data - data to look for
*	\return node * - node if found, NULL otherwise
*	\note FUNCTION IS RECURSIVE
******************************************************************************/
node* find_node(node *root, int data);

/*!*****************************************************************
*	\fn create_node(int data, node *parent)
*	\brief -  create a new node with the passed in data. 
*		  Children are set to NULL
*	\param data - Node data
*	\param parent - node parent
*	\return node * - newly created node
*******************************************************************/
node* create_node(int data, node *parent);

/*!*****************************************************************
*	\fn add_node(node **root, int data, node *parent)
*	\brief -  Create and add a new node to the passed in root, which 
*		  is recursively traversed to find the right place where 
*		  the new node can be inserted. If (data < root->data), 
*		  then it is inserted to the left, else to the right.
*		  Once inserted, the tree is normalized.
*	\param root - root node
*	\param data - new data to be added
*	\param parent - parent for the new node
*	\return void
*	\note FUNCTION IS RECURSIVE
*******************************************************************/
void add_node(node **root, int data, node *parent);

/*!*******************************************************
*	\fn is_leaf_node(node *n)
*	\brief -  returns whether a node is a leaf node or 
*		  not i.e both L and R children are NULL
*	\param n - Node to check
*	\return bool - true/false
*********************************************************/
bool is_leaf_node(node *n);

/*!*******************************************************
*	\fn swap(node *child, node * parent)
*	\brief -  Swap parent and child data so child's data is assigned 
*		  to the parent and vice-versa
*	\param child - child node
*	\param parent - parent node
*	\return void
*********************************************************/
void swap(node *child, node *parent);

/*!*******************************************************
*	\fn free_tree(node *root)
*	\brief -  free all nodes in the tree recursively
*	\param  root - tree root
*	\return void
*	\note FUNCTION IS RECURSIVE
*********************************************************/
void free_tree(node *root);

/*!*******************************************************
*	\fn print_tree(node *root)
*	\brief -  print all nodes in the tree recursively
*	\param root - Node to get right-child of
*	\return void
*	\note FUNCTION IS RECURSIVE
*********************************************************/
void print_tree(node *root);

/*!****************************************************************************
*	\fn find_tree_height(node *root)
*	\brief - Find the height of the tree
*	\param norm_node - tree root
*	\return - tree height
******************************************************************************/
int find_tree_height(node *root); 


/*!****************************************************************************
*	\fn find_tree_balance(node *root)
*	\brief - Find the balance of the tree
*	\param norm_node - tree root
*	\return - tree balance (+ve - Right heavy, -ve - Left heavy)
******************************************************************************/
int find_tree_balance(node *root); 

/*!*****************************************************************
	\fn append_link_node(node**, int, node*)
	\brief - Append the node to the end of the list 
	\param head - list head
	\param data - Node data
	\param parent - node parent
	\return void
*******************************************************************/
void append_link_node(node **head, int data, node *parent);

/*!*****************************************************************
	\fn print_nodes(node**, int, node*)
	\brief - print the nodes
	\param head - list head
	\param data - Node data
	\param parent - node parent
	\return void
*******************************************************************/
void print_nodes(node **head, int data, node *dontcare);

/*!*****************************************************************
	\fn free_link_nodes(node**, int, node*)
	\brief - Free all the nodes
	\param head - list head
	\param data - Node data
	\param parent - node parent
	\return void
*******************************************************************/
void free_link_nodes(node **head, int data, node *dontcare);

/*!*****************************************************************
	\fn insert_node(node**, int, node*)
	\brief - Handling inserting node in between, at the start or end of the list
	\param head - list head
	\param data - Node data
	\param parent - node parent
	\return void
*******************************************************************/
void insert_node(node **head, int data, node *dontcare);

/*!*****************************************************************
	\fn delete_node(node**, int, node*)
	\brief - Handling deleting node in between, at the start or end of the list
	\param head - list head
	\param data - Node data
	\param parent - node parent
	\return void
*******************************************************************/
void delete_node(node **head, int data, node *dontcare);

/*!****************************************************************************
*	\fn rotate_tree_left(node **root)
*	\brief - Rotate tree left, making right node below the root the new root
*	\param root - tree root
*	\return - void
******************************************************************************/
void rotate_tree_left(node **root);

/*!****************************************************************************
*	\fn rotate_tree_right(node **root)
*	\brief - Rotate tree right, making left node below the root the new root
*	\param root - tree root
*	\return - void
******************************************************************************/
void rotate_tree_right(node **root);

/*!***************************************************************************
	\fn balance_tree(node **root)
	\brief - Called when the tree is unbalanced, to, well... balance it A balance
            factor of 2 is used. +ve implies RHS is heavier, -ve implies LHS is 
            heavier.
	\param **root - tree root
	\return - void
*****************************************************************************/
void balance_tree(node **root);

#endif // _HEAPSORT_H_
