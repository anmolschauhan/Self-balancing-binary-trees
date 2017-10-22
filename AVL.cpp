#include <bits/stdc++.h>
#define MAX 5000000
using namespace std;

struct node
{
	int data;
	int height;
	struct node *left, *right;
};

int height(struct node *n)
{
	if(n == NULL)
		return 0;
	return n->height;
}

void rightRotate(struct node **n)
{
	struct node *temp;
	struct node *temp1;
	temp = (*n)->left;
	temp1 = *n;
	temp1->left = temp->right;
	temp->right = temp1;
	temp1->height = 1 + max(height(temp1->left), height(temp1->right));
	temp->height = 1 + max(height(temp->left), height(temp->right));
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
	temp1->height = 1 + max(height(temp1->left), height(temp1->right));
	temp->height = 1 + max(height(temp->left), height(temp->right));
	*n = temp;	
}


void insert(struct node **node, int value)
{
	if(*node == NULL)
	{
		struct node *newNode = new struct node;
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->data = value;
		newNode->height = 1;
		*node = newNode;
		return;
	}
	if(value >= (*node)->data)
		insert(&(*node)->right, value);
	else
		insert(&(*node)->left, value);
	
	(*node)->height = 1 + max(height((*node)->left), height((*node)->right));


	if(abs(height((*node)->left) - height((*node)->right)) > 1)				// IMBALANCE
	{
		if(value < (*node)->data && value < (*node)->left->data)			//	LEFT > LEFT
		{
			rightRotate(node);
		}
		else if(value < (*node)->data && value >= (*node)->left->data)		// 	LEFT > RIGHT
		{
			leftRotate(&(*node)->left);
			rightRotate(node);
		}
		else if(value >= (*node)->data && value < (*node)->right->data)		//	RIGHT < LEFT
		{
			rightRotate(&(*node)->right);
			leftRotate(node);	
		}
		else if(value >= (*node)->data && value >= (*node)->right->data)	//	RIGHT > RIGHT
		{
			leftRotate(node);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	double elapsed_secs;
	clock_t begin;
	clock_t end;
	struct node *root = NULL;

	int temp;

	begin = clock();
	for(int i=1;i<=MAX;i++)
	{
		cin >> temp;
		insert(&root, temp);
	}
	end = clock();

	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << elapsed_secs << endl;
	
	return 0;
}