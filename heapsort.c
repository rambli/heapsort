/**
* @file heapsort.c
* @brief Heapsort implementation
* @author Rohan Ambli
*/

#include "heapsort.h"

/**
	\fn free_nodes(node *root)
	\brief -  free all nodes in the tree recursively
	\param  root - tree root
	\return void
	\note FUNCTION IS RECURSIVE
*/
void free_nodes(node *root)
{
	if(NULL != root)
	{
		free_nodes(root->link[LEFT]);
		free_nodes(root->link[RIGHT]);
		PRINT("free'ing %d\n", root->data);
		free(root);
	}
	return;
}


/*******************************************************************
	\fn create_node(int data, node *parent)
	\brief -  create a new node with the passed in data. 
		  Children are set to NULL
	\param data - Node data
	\param parent - node parent
	\return node * - newly created node
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

/*******************************************************************
	\fn add_node(node **root, int data, node *parent)
	\brief -  Create and add a new node to the passed in root, which 
		  is recursively traversed to find the right place where 
		  the new node can be inserted. If (data < root->data), 
		  then it is inserted to the left, else to the right.
		  Once inserted, the tree is normalized.
	\param root - root node
	\param data - new data to be added
	\param parent - parent for the new node
	\return void
	\note FUNCTION IS RECURSIVE
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
		//normalize_tree(*root);
	}
	else
	{
		parent = *root;
		PRINT("Adding down %d[%c]\n", data,DIR(data, (*root)->data) ? 'R':'L');
		add_node(&((*root)->link[DIR(data,(*root)->data)]), data, parent);
	}
}

/******************************************************************************
	\fn find_node(node *root, int data)
	\brief -  Find the node which matches the passed in data.
	\param root - tree root
	\param data - data to look for
	\return node * - node if found, NULL otherwise
	\note FUNCTION IS RECURSIVE
******************************************************************************/

node *find_node(node *root, int data)
{
	node *found = NULL;
	if(NULL == root)
		found = NULL;
	else
	{
		if(data == root->data)
			found = root;
		else
			found = find_node(root->link[DIR(data,root->data)],data);
	}
	return (found);
}


/******************************************************************************
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
		PRINT("node %d does not have a parent\n", norm_node->data);
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


int find_tree_height(node *root) 
{
	if (root == NULL) return 0;

	int r = find_tree_height(root->link[RIGHT]);
	int l = find_tree_height(root->link[LEFT]);

	if(abs(l - r) >= 2)
	{
		PRINT("Tree is unbalanced l:%d r:%d\n", l, r);
	}

	return (1 + ((l > r) ? l:r)); 
}

/**
	\fn main
	\brief - main fn to perform heapsort
*/
int main(void)
{
	node *root = NULL;
	int i = 0;
	int scan = 0;

	while(1)
	{
		printf("Enter number:\n");
		scanf("%d", &scan);
		if(scan == (int)-1)
			break;
		else
			add_node(&root, scan, root);

		//PRINT("Tree height is %d\n", find_tree_height(root));
	}
	/* TODO: Nodes are normalized, now begin extracting */

	print_tree(root);
	free_nodes(root);
	return 0;
}
