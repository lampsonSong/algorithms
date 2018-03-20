#import <iostream>

using namespace std;

struct Node{
	Node* leftChild;
	Node* rightChild;
	int value;
};

Node* root;
Node* current;

void insert(int a, Node* insertPointer)
{
	//insert into left
	if(a <= insertPointer->value)
	{
		if(insertPointer->leftChild == NULL)//left is NULL
		{
			insertPointer->leftChild = new Node();
			current = insertPointer->leftChild;

			current->leftChild = NULL;
			current->rightChild = NULL;
			current->value = a;
		}
		else//left is Node, continue searching left
		{
			current = insertPointer->leftChild;
			insert(a,current);
		}
	}
	else//insert into right
	{
		if(insertPointer->rightChild == NULL)//right is NULL
		{
			insertPointer->rightChild = new Node();
			current = insertPointer->rightChild;

			current->rightChild = NULL;
			current->leftChild = NULL;
			current->value = a;
		}
		else//right is Node, continue searching right
		{
			current = insertPointer->rightChild;
			insert(a,current);
		}
	}
}

void insertTree(int a)
{
	//The root is empty
	if(root==NULL)
	{
		root = new Node();
		
		root->value = a;
		root->leftChild = NULL;
		root->rightChild = NULL;
	}
	else
	{
		current = root;
		
		insert(a,current);
	}
}

//visit all elements in the binary tree
void visitTree(Node* visitPointer)
{
	if(visitPointer->leftChild == NULL && visitPointer->rightChild == NULL)
	{
		cout<<visitPointer->value<<"     ";
	}
	else
	{
		if(visitPointer->leftChild != NULL && visitPointer->rightChild != NULL)
		{
			if(visitPointer->leftChild != NULL)
			{
				visitTree(visitPointer->leftChild);
			}
			cout<<visitPointer->value<<"     ";	

			if(visitPointer->rightChild != NULL)
			{
				visitTree(visitPointer->rightChild);
			}
		}
		else
		{	
			if(visitPointer->leftChild != NULL)
			{
				visitTree(visitPointer->leftChild);
			}

			if(visitPointer->rightChild != NULL)
			{
				visitTree(visitPointer->rightChild);
			}
			cout<<visitPointer->value<<"     ";
		}
	}
}

int main()
{
	int size;
	//input the array
	cout<<"Input Array Size:"<<endl;
	cin>>size;
	
	int array[size];

	cout<<"Input Array Data:"<<endl;
	for(int i = 0; i < size; i++)
	{
		cin>>array[i];
		insertTree(array[i]);
	}
	visitTree(root);
}
