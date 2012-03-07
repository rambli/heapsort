
/**
* @file heap_util.c
* @brief Heapsort implementation utility functions
* @author Rohan Ambli
*/

#include "heapsort.h"

/*!*******************************************************
*	\fn new
*	\brief - allocate space and return a new node
*	\param void
*	\return node * - New Node
*********************************************************/
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

/*!*******************************************************
*	\fn get_parent(node *ndata)
*	\brief -  returns the nodes parent
*	\param ndata - Node to get parent of
*	\return node * - Node's parent	
*********************************************************/
node* get_parent(node *ndata)
{
	if(NULL == ndata)
		return NULL;
	return (ndata->parent); 
}

/*!*******************************************************
*	\fn get_rchild(node *parent)
*	\brief -  returns the parent's right child
*	\param parent - parent node to get right-child of
*	\return node * - right child
*********************************************************/
node *get_rchild(node *parent)
{
	if(NULL == parent)
		return NULL;
	return (parent->link[1]);
}

/*!*******************************************************
*	\fn get_lchild(node *parent)
*	\brief -  returns the parent's left child
*	\param parent - parent node to get left child of
*	\return node * - left child
*********************************************************/

node *get_lchild(node *parent)
{
	if(NULL == parent)
		return NULL;
	return (parent->link[0]);
}

/*!*******************************************************
*	\fn is_leaf_node(node *n)
*	\brief -  returns whether a node is a leaf node or 
*		  not i.e both L and R children are NULL
*	\param n - Node to check
*	\return bool - true/false
*********************************************************/
bool is_leaf_node(node *n)
{
	if(NULL == n)
		return TRUE;
	return (((n->link[0] == NULL) && (n->link[1] == NULL)) ? TRUE:FALSE);
}


/*!*******************************************************
*	\fn get_smaller_child(node *)
*	\brief -  returns the smaller child
*	\param parent - Node to check
*	\return node * - L/R child
*********************************************************/
node *get_smaller_child(node *parent)
{
	if(is_leaf_node(parent))
		return NULL;

	if(NULL == parent->link[0])
		return parent->link[1];
	else if(NULL == parent->link[1])
		return parent->link[0];
	else
		return (parent->link[0]->data > parent->link[1]->data ? parent->link[1]:parent->link[0]);
}

/*!*******************************************************
*	\fn get_larger_child(node *)
*	\brief -  returns the larger child
*	\param parent - Node to check
*	\return node * - L/R child
*********************************************************/
node *get_larger_child(node *parent)
{
	if(is_leaf_node(parent))
		return (NULL);
	if(NULL == parent->link[0])
		return (parent->link[1]);
	else if(NULL == parent->link[1])
		return (parent->link[0]);

	return (parent->link[0]->data < parent->link[1]->data ? parent->link[1]:parent->link[0]);
}

/*!*******************************************************
*	\fn print_tree(node *root)
*	\brief -  print all nodes in the tree recursively
*	\param root - Node to get right-child of
*	\return void
*	\note FUNCTION IS RECURSIVE
*********************************************************/
void print_tree(node *root)
{
	if(NULL != root)
	{
      if(NULL == root->parent)
         printf("<ROOT>");
		printf(" %d ",root->data);
		if(NULL != root->parent)
			printf("p:%d ", root->parent->data);
		print_tree(root->link[0]);
		print_tree(root->link[1]);
	}
	return;
}

/*!*******************************************************
*	\fn swap(node *child, node * parent)
*	\brief -  Swap parent and child data so child's data is assigned 
*		  to the parent and vice-versa
*	\param child - child node
*	\param parent - parent node
*	\return void
*********************************************************/
void swap(node *child, node *parent)
{
	if((NULL != child) && (NULL != parent))
	{
		PRINT("Swapping %d<->%d\n", child->data, parent->data);
		child->data = child->data ^ parent->data;
		parent->data = child->data ^ parent->data;
		child->data = child->data ^ parent->data;
	}
}

/*!*******************************************************
*	\fn free_tree(node *root)
*	\brief -  free all nodes in the tree recursively
*	\param  root - tree root
*	\return void
*	\note FUNCTION IS RECURSIVE
*********************************************************/
void free_tree(node *root)
{
	if(NULL != root)
	{
		free_tree(root->link[LEFT]);
		free_tree(root->link[RIGHT]);
		free(root);
	}
	return;
}

/*!*****************************************************************
*	\fn create_node(int data, node *parent)
*	\brief -  create a new node with the passed in data. 
*		  Children are set to NULL
*	\param data - Node data
*	\param parent - node parent
*	\return node * - newly created node
*******************************************************************/

node *create_node(int data, node *parent)
{
	node *ndata = new();
	if(NULL != ndata)
	{
		ndata->link[LEFT] = ndata->link[RIGHT] = NULL;
		ndata->data = data;
		ndata->parent = parent;
		if(NULL != parent)
			PRINT("%d's parent is %d\n", data, parent->data);
	}
	return (ndata);
}

/*!****************************************************************************
*	\fn find_node(node *root, int data)
*	\brief -  Find the node which matches the passed in data.
*	\param root - tree root
*	\param data - data to look for
*	\return node * - node if found, NULL otherwise
*	\note FUNCTION IS RECURSIVE
******************************************************************************/

node *find_node(node *root, int data)
{
	node *found = NULL;
	if(NULL != root)
	{
		if(data == root->data)
			found = root;
		else
			found = find_node(root->link[DIR(data,root->data)],data);
	}
	return (found);
}


/*!****************************************************************************
*	\fn get_last_child(node *root)
*	\brief - Find the lowest child of the tree (has to be a leaf node)
*	\param norm_node - tree root
*	\return - node * - lowest child
******************************************************************************/
node *get_last_child(node *root)
{
	while(NULL != root)
	{
		if(is_leaf_node(root))
		{
			return (root);
		}
		if((root)->link[RIGHT])
			root = (root)->link[RIGHT];
		/* Since this is not a leaf node, left cannot be NULL
		   as right is */
		else
			root = (root)->link[LEFT];
	}
}

/*!****************************************************************************
*	\fn find_tree_height(node *root)
*	\brief - Find the height of the tree
*	\param norm_node - tree root
*	\return - tree height
******************************************************************************/
int find_tree_height(node *root) 
{
	if (root == NULL) return 0;

	int l = find_tree_height(root->link[LEFT]);
	int r = find_tree_height(root->link[RIGHT]);
#if 0
	if(abs(l - r) >= 2)
	{
		PRINT("Tree is unbalanced l:%d r:%d\n", l, r);
	}
   PRINT("height: l: %d r: %d\n", l, r);
#endif
	return (1 + ((l > r) ? l:r)); 
}

/*!****************************************************************************
*	\fn find_tree_balance(node *root)
*	\brief - Find the balance of the tree
*	\param norm_node - tree root
*	\return - tree balance (+ve - Right heavy, -ve - Left heavy)
******************************************************************************/
int find_tree_balance(node *root) 
{
	if (root == NULL) return 0;

	int l = find_tree_height(root->link[LEFT]);
	int r = find_tree_height(root->link[RIGHT]);
#if 0
	if(abs(l - r) >= 2)
	{
		PRINT("Tree is unbalanced l:%d r:%d\n", l, r);
	}
   PRINT("height: l: %d r: %d\n", l, r);
#endif
   return (r-l);
}
/*!****************************************************************************
*	\fn rotate_tree_left(node **root)
*	\brief - Rotate tree left, making right node below the root the new root
*	\param root - tree root
*	\return - void
******************************************************************************/
void rotate_tree_left(node **root)
{
   node *new_root = get_rchild(*root);
   node *old_root = *root;

   PRINT("Rotating tree to left - root: %d new_root: %d\n", 
         old_root->data, new_root->data);

   /* New root's left child becomes old root's right child
    * Set the child's parent as the old_root as well */
   (*root)->link[RIGHT] = new_root->link[LEFT];
   if(NULL != new_root->link[LEFT])
      (new_root->link[LEFT])->parent = (*root);
   /* Update *root to new_root */
   *root = new_root;
   /* New root's left child is now old_root */
   (*root)->link[LEFT] = old_root;
   /* Update parents */
   old_root->parent = *root;
   (*root)->parent = NULL;
}

/*!****************************************************************************
*	\fn rotate_tree_right(node **root)
*	\brief - Rotate tree right, making left node below the root the new root
*	\param root - tree root
*	\return - void
******************************************************************************/
void rotate_tree_right(node **root)
{
   node *new_root = get_lchild(*root);
   node *old_root = *root;

   PRINT("Rotating tree to right - root: %d new_root: %d\n", 
         (*root)->data, (get_lchild(*root))->data);

   /* New root's right child becomes old root's left child
    * Set the child's parent as the old_root as well */
   (*root)->link[LEFT] = new_root->link[RIGHT];
   if(NULL != new_root->link[RIGHT])
      (new_root->link[RIGHT])->parent = (*root);
   /* Update *root to new_root */
   *root = new_root;
   /* New root's left child is now old_root */
   (*root)->link[RIGHT] = old_root;
   /* Update parents */
   old_root->parent = *root;
   (*root)->parent = NULL;
}
