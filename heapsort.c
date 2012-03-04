/**
* @file heapsort.c
* @brief Heapsort implementation
* @author Rohan Ambli
*/

#include "heapsort.h"

/*!*****************************************************************
*	\fn add_node(node **root, int data, node *parent)
*	\brief -  Create and add a new node to the passed in root, which 
*		  is recursively traversed to find the right place where 
*		  the new node can be inserted. If (data < root->data), 
*		  then it is inserted to the left, else to the right.
*		  Once inserted, the tree is normalized. (normalize_tree)
*	\param root - root node
*	\param data - new data to be added
*	\param parent - parent for the new node
*	\return void
*	\note FUNCTION IS RECURSIVE. this is on the coding-conventions branch
*******************************************************************/

void add_node(node **root, int data, node *parent)
{
	if (NULL == *root)
	{
		*root = create_node(data, parent);
		/* Created node, re-arrange it in the tree such that it is
		   smaller than its parent. If normalizing, then tree is used
		   used in heapsort. If normalizing is skipped, it is a regular
		   binary tree. */
		normalize_tree(*root);
	}
	else
	{
		parent = *root;
		add_node(&((*root)->link[DIR(data,(*root)->data)]), data, parent);
	}
}

/*!***************************************************************************
	\fn normalize_tree(node *norm_node)
	\brief - The passed in node is tested against its parent, and swapped if it is smaller
	       than the parent. This is done recursively until the condition is satisfied.
	\param norm_node - node to be normalized
	\return void
*****************************************************************************/
void normalize_tree(node *norm_node)
{
	if(NULL == norm_node)
		return;
	PRINT("Normalizing tree with node %d\n", norm_node->data);
	if(NULL == norm_node)
	{
		PRINT("Did not find node %d\n", norm_node->data);
		return;
	}

	node *parent = get_parent(norm_node);
	if(NULL == parent)
		PRINT("node %d does not have a parent. This is the root\n", norm_node->data);
	while(NULL != parent)
	{
		if(norm_node->data < parent->data)
		{
			/* Child data is smaller than parent, swap */
			swap(norm_node, parent);
			PRINT("Swapped child(%p):%d parent(%p):%d\n", norm_node, norm_node->data, parent, parent->data);
		}
		else
		{
			PRINT("Child is %d, parent is %d.. already normalized\n", norm_node->data, parent->data);
			/* If this <child,parent> pair is normalized, all pairs above here are normalized as well,
			   return here */
			break;
		}
		/* Go up a level to see if our child (now parent after swap) needs to climb higher if it is 
		   smaller than its new parent. */
		norm_node = parent;
		parent = get_parent(norm_node);
	}
	return;
}

/*!***************************************************************************
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
void normalize_tree_root(node *root)
{
	node *sc = NULL;
	while(NULL != root)
	{
		PRINT("Normalizing tree with root %d\n", root->data);
		sc = get_smaller_child(root);
		if(sc)
		{
			/* Smallest child of this node is smaller than this node.
			   Swap them and continue checking until this we reach the bottom */
			if(sc->data < root->data)
			{
				swap(sc, root);
			}
		}
		/* Now child becomes root, and same check continues lower */
		root = sc;
	}
	return;
}


/*!***************************************************************************
	\fn sort(node **root)
	\brief - The sorting function
	\param **root - tree root
	\return - void
*****************************************************************************/
void sort(node **root)
{
	int i = 10;
	node *lc = NULL;
	while(*root)
	{
		/* Get last node which is one of the largest nodes (definitely larger than our current root)
		   and make it the root of the tree. Then normalize tree so the next smallest number can 
		   float to the top */
		lc = get_last_child(*root);

		/* Reached the root, last element */
		if(lc == *root)
		{
			printf("Extracting %d\n Done sorting!!\n", lc->data);
			free(*root);
			lc = *root = NULL;
		}

		if(lc)
		{
			int data = lc->data;
			/* Extract the current root which is the smallest number currently */
			printf("Extracting %d\n", (*root)->data);

			/* Set root to the larger child, which is brought up from below */
			(*root)->data = data;
		
			/* Free the child's old node as it is now at the root position. Make sure we 
			   set it's parent's link to it to NULL. 
			   Don't really need to check if its parent is NULL or not (its not as its not 
			   the tree root), but we do it for sanity check. */
			if(NULL != lc->parent)
			{
				if(NULL != lc->parent->link[LEFT])
					if(lc->parent->link[LEFT]->data == lc->data)
						lc->parent->link[LEFT] = NULL;
				if(NULL != lc->parent->link[RIGHT])
					if(lc->parent->link[RIGHT]->data == lc->data)
						lc->parent->link[RIGHT] = NULL;
			}

			/* Parent link to this is now NULL, free it */
			free(lc);
			lc = NULL;

			/* The child which is one of the largest nodes in this tree is sitting at the 
			   root, normalize tree so that it sinks to the bottom and next smallest node
			   floats to the top */
			normalize_tree_root(*root);
		}
	}
}

/*!*************************************************************************
	\fn main
	\brief - main fn to perform heapsort
****************************************************************************/
int main(void)
{
	node *root = NULL;
	int i = 0;
	int scan = 0;
#if 0
	int arr[] = {5,10,7,4,15,25,13};

	for(i = 0; i < 7; i++)
	{
		add_node(&root, arr[i], root);
	}
	PRINT("============ BEGIN SORTING============\n");
#endif
#if 1
	while(1)
	{
		printf("Enter number:\n");
		scanf("%d", &scan);
		if(scan == (int)-1)
			break;
		else
			add_node(&root, scan, root);

		PRINT("Tree height is %d\n", find_tree_height(root));
	}
#endif
	/* TODO: Nodes are normalized, now begin extracting */
	print_tree(root);
	printf("\n");
	sort(&root);
	free_tree(root);
	return 0;
}
