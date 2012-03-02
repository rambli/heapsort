
/**
* @file heap_util.c
* @brief Heapsort implementation utility functions
* @author Rohan Ambli
*/

#include"heapsort.h"


/**	\fn new
*	\brief - allocate space and return a new node
*	\param void
*	\return node * - New Node
*/
node *new()
{
	node *new_node = (node*) malloc(sizeof(*new_node));
	if(NULL != new_node)
	{
		new_node->link[0] = new_node->link[1] = NULL;
		new_node->data = 0;
	}
	return (new_node);
}

/**	\fn get_parent(node *ndata)
*	\brief -  returns the nodes parent
*	\param ndata - Node to get parent of
*	\return node * - Node's parent	
*/
node* get_parent(node *ndata)
{
	if(NULL == ndata)
		return NULL;
	return (ndata->parent); 
}

/**	\fn get_rchild(node *parent)
	\brief -  returns the parent's right child
	\param parent - parent node to get right-child of
	\return node * - right child
*/
node *get_rchild(node *parent)
{
	if(NULL == parent)
		return NULL;
	return (parent->link[1]);
}

/**
	\fn get_lchild(node*)
	\brief -  returns the parent's left child
	\param parent - parent node to get left child of
	\return node * - left child
*/
node *get_lchild(node *parent)
{
	if(NULL == parent)
		return NULL;
	return (parent->link[0]);
}

/**
	\fn is_leaf_node(node *)
	\brief -  returns whether a node is a leaf node or not i.e both L and R children are NULL
	\param n - Node to check
	\return bool - true/false
*/
bool is_leaf_node(node *n)
{
	if(NULL == n)
		return TRUE;
	return (((n->link[0] == NULL) && (n->link[1] == NULL)) ? TRUE:FALSE);
}

/**
	\fn get_smaller_child(node *)
	\brief -  returns the smaller child
	\param parent - Node to check
	\return node * - L/R child
*/
node *get_smaller_child(node *parent)
{
	if(NULL == parent)
		return NULL;
	if(is_leaf_node(parent))
		return NULL;

	return (parent->link[0]->data > parent->link[1]->data ? parent->link[1]:parent->link[0]);
}

/**
	\fn print_tree(node *root)
	\brief -  print all nodes in the tree recursively
	@param root - Node to get right-child of
	\return void
	\note FUNCTION IS RECURSIVE
*/
void print_tree(node *root)
{
	if(NULL != root)
	{
		PRINT(" %d ",root->data);
		if(NULL != root->parent)
			PRINT("p:%d ", root->parent->data);
		print_tree(root->link[0]);
		print_tree(root->link[1]);
	}
	return;
}

/**
	\fn swap(node *child, node * parent)
	\brief -  Swap parent and child data so child's data is assigned 
		  to the parent and vice-versa
	\param child - child node
	\param parent - parent node
	\return void
*/
void swap(node *child, node *parent)
{
	child->data = child->data ^ parent->data;
	parent->data = child->data ^ parent->data;
	child->data = child->data ^ parent->data;
}
