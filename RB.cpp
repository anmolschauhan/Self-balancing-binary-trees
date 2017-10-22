#include <bits/stdc++.h>
using namespace std;

struct node
{
	int data;
	bool red;
	struct node *left, *right;
};

struct node* newNode(int value)
{
	struct node *newN = new struct node;
	newN->data = value;
	newN->red = true;
	newN->left = NULL;
	newN->right = NULL;
	return newN;
}

bool color(struct node *n)
{
	if(n == NULL)
		return false;
	return n->red;
}

void rightRotate(struct node **n)
{
	struct node *temp;
	struct node *temp1;
	temp = (*n)->left;
	temp1 = *n;
	temp1->left = temp->right;
	temp->right = temp1;
	bool t;
	t = temp->red;
	temp->red = temp1->red;
	temp1->red = t;
	*n = temp;
}


void leftRotate(struct node **n)
{
	struct node *temp;
	struct node *temp1;
	temp = (*n)->right;
	temp1 = *n;
	temp1->right = temp->left;
	temp->left = temp1;
	bool t;
	t = temp->red;
	temp->red = temp1->red;
	temp1->red = t;
	*n = temp;	
}


void insert(int value, struct node **node)
{
	//if((*node)->NIL == true)
	if(*node == NULL)
	{
		*node = newNode(value);
		return;
	}
	if(value < (*node)->data)
	{
		insert(value, &(*node)->left);
		if(color((*node)->left))
		{
			if(color((*node)->right) && (color((*node)->left->left) || color((*node)->left->right)))
			{
				(*node)->red = true;
				(*node)->left->red = false;
				(*node)->right->red = false;
			}
			else if(value < (*node)->left->data && color((*node)->left->left))			//	LEFT red > LEFT red
			{
				rightRotate(node);
			}
			else if(value >= (*node)->left->data && color((*node)->left->right))	// LEFT red > RIGHT red
			{
				leftRotate(&(*node)->left);
				rightRotate(node);
			}
		}
	}
	else
	{
		insert(value, &(*node)->right);
		if(color((*node)->right))
		{
			if(color((*node)->left) && (color((*node)->right->left) || color((*node)->right->right)))
			{
				(*node)->red = true;
				(*node)->left->red = false;
				(*node)->right->red = false;
			}
			else if(value >= (*node)->right->data && color((*node)->right->right))		//	RIGHT red > RIGHT red
			{
				leftRotate(node);
			}
			else if(value < (*node)->right->data && color((*node)->right->left))	// RIGHT red > LEFT red
			{
				rightRotate(&(*node)->right);
				leftRotate(node);
			}
		}
	}
}

void insertTree(int value, struct node **node)
{
	insert(value, node);
	(*node)->red = false;
}

/*
void inorder(struct node *n)
{
	if(n->NIL)
		return;
	inorder(n->left);
	cout << n->data << " ";
	inorder(n->right);
}*/

int main()
{
	ios::sync_with_stdio(false);

	int MAX = 5000000;
	double elapsed_secs;
	clock_t begin;
	clock_t end;
	struct node *root = NULL;
	int temp;

	begin = clock();
	for(int i=1;i<=MAX;i++)
	{
		cin >> temp;
		insertTree(temp, &root);
	}
	end = clock();

	cout << root->data << endl;
	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << elapsed_secs << endl;
	return 0;
}