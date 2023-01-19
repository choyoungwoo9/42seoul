#include <stdio.h>
#include <stdlib.h>

typedef struct s_node
{
	int value;
	struct s_node *left_node;
	struct s_node *right_node;
}	t_node;

t_node *root_node = 0;
int N;
int C = 0;

t_node *make_node(int value)
{
	t_node *node;
	node = malloc(sizeof(t_node));
	node->value = value;
	node->left_node = 0;
	node->right_node = 0;
	return node;
}

void insert(int value, t_node *node)
{
	C++;
	if(value < node->value)
	{
		if(node->left_node == 0)
			node->left_node = make_node(value);
		else
			insert(value, node->left_node);
	}
	else if(value > node->value)
	{
		if(node->right_node == 0)
			node->right_node = make_node(value);
		else
			insert(value, node->right_node);
	}
}

void insert_node(int value)
{
	if(root_node == 0)
		root_node = make_node(value);
	else
		insert(value, root_node);
	printf("%d\n", C);
}

int main()
{
	
	scanf("%d", &N);
	for(int i = 0; i < N; i ++)
	{
		int tmp;
		scanf("%d", &tmp);
		insert_node(tmp);
	}
}