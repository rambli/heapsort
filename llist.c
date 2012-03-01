#include"heapsort.h"

#define NEXT	1
#define PREV	0

typedef void (*fnptr) (node **, int, node*);

node *new()
{
	node *new_node = (node*) malloc(sizeof(*new_node));
	new_node->link[NEXT] = new_node->link[PREV] = NULL;
	return (new_node);
}

//
// Add link node
// Always adds to the end of the list
//

static void add_link_node(node **head, int data, node *parent)
{
	if(NULL == *head)
	{
		*head = new();
		(*head)->link[PREV] = parent;
		(*head)->link[NEXT] = NULL;
		(*head)->data = data;
	}
	else
	{
		add_link_node(&((*head)->link[NEXT]), data, *head);
	}
}

void print_nodes(node **head, int data, node *dontcare)
{
	node *iter = *head;
	while(iter != NULL)
	{
		printf("%d->", iter->data);
		iter = iter->link[NEXT];
	}
	printf("\n");
}

//void free_nodes(node *head)
void free_link_nodes(node **head, int data, node *dontcare)
{
	node *iter = *head;
	node *mem;
	while(iter)
	{
		mem = iter->link[NEXT];
		free(iter);
		iter = mem;
	}
}

void print_exit()
{
	printf("I'mma has-been\n");
}

//
// Insert Node
// Handling inserting node in between, at the start or end of the list
//
void insert_node(node **head, int data, node *dontcare)
{
	printf("Inserting data %d\n", data);
	node *iter = *head;
	node *prev = NULL;

	// trying to insert before list exists, this is
	// the first node.
	if(NULL == *head)
	{
		add_link_node(head, data, NULL);
		return;
	}


	// Check if we need to insert before head
	while(iter != NULL)
	{
		if(data < iter->data)
		{
			prev = iter;
			iter = iter->link[NEXT];
		}
		else
			break;
	}

	// This means we are at the end of the list.. re-acquire the last node
	if(NULL == iter)
	{
		iter = prev;
	}

	// Inserting before head, i.e this will be the new head
	if(NULL == iter->link[PREV])
	{
		node *new_node = new();
		new_node->data = data;
		new_node->link[PREV] = NULL;
		new_node->link[NEXT] = *head;
		printf("Created node with data %d.. reforming links\n", new_node->data);
		(*head) = new_node; 
	}
	else
	{
		printf("Not inserting at the beginning\n");
		node *new_node = new();
		new_node->data = data;
		printf("Created node with data %d.. reforming links\n", new_node->data);
		(iter->link[PREV])->link[NEXT] = new_node;
		new_node->link[PREV] = iter->link[PREV];
		new_node->link[NEXT] = iter;
		iter->link[PREV] = new_node;
	}
}

//
// Delete node
// Handles deleting nodes from the middle, start or end of list
//

void delete_node(node **head, int data, node *dontcare)
{
	node *iter = *head;
	if(NULL == iter)
		return;

	// look for node
	while(iter)
	{
		if(iter->data != data)
			iter = iter->link[NEXT];
		else
			break;
	}

	// Modifying head.. edit *ptr value so caller sees the changed head
	if(NULL == iter->link[PREV])
	{
		// This is the head, make next node the head
		iter = *head;
		*head = (*head)->link[NEXT];
		(*head)->link[PREV] = NULL; //Since this is the new head, make prev=NULL
		free(iter);
		printf("Deleted %d, %d is now head\n", data, (*head)->data);
		return;
	}
	else
	{
		(iter->link[PREV])->link[NEXT] = iter->link[NEXT];
		printf("relaid out prev->next link to %p\n", iter->link[PREV]->link[NEXT]);
		if(NULL != iter->link[NEXT])
		{
			(iter->link[NEXT])->link[PREV] = iter->link[PREV];
		}
		printf("free'ing node %d\n", data);
		free(iter);
	}
}



fnptr fn_arr[] = 
{
	insert_node,
	add_link_node,
	delete_node,
	print_nodes,
	free_link_nodes
};

int main()
{
	int opt = 0;
	int data = 0;

	node *head = NULL;

	atexit(print_exit);
	while(1)
	{
		printf("Enter option: \
			\n1)Insert \
			\n2)Append \
			\n3)Delete \
			\n4)Print \
			\n5)Quit\n");
		scanf("%d", &opt);

		if((opt != 4) && (opt != 5))
		{
			printf("Enter data:\n");
			scanf("%d",&data);
		}
		else if(5 == opt)
			break;

		fn_arr[opt-1](&head, data, head);
	}
	return 0;
}
