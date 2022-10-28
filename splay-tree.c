#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>


struct node
{
	struct node *left;
	struct node *right;
	struct node *parent;
	int vertex;
};

struct node *root;

void Insert(int vertex)
{
	if(root==NULL)
	{
		root=(struct node *)malloc(sizeof(struct node));
		root->left = NULL;
		root->right = NULL;
		root->parent = NULL;
		root->vertex = vertex;
		return;
	}

	struct node *Parent = root;

	while(1)
	{
		if(Parent->vertex == vertex)
            break;

		if(vertex < (Parent->vertex) )
		{
			if(Parent->left !=NULL)

                Parent=Parent->left;

			else
			{
				Parent->left = (struct node *)malloc(sizeof(struct node));
				Parent->left->parent = Parent;
				Parent->left->right = NULL;
				Parent->left->left = NULL;
				Parent->left->vertex = vertex;
				Parent = Parent->left;
				break;
			}
		}
		else
		{
			if(Parent->right !=NULL)

                Parent = Parent->right;

			else
			{
				Parent->right = (struct node *)malloc(sizeof(struct node));
				Parent->right->parent = Parent;
				Parent->right->right = NULL;
				Parent->right->left = NULL;
				Parent->right->vertex = vertex;
				Parent = Parent->right;
				break;
			}
		}
	}

	Splay(Parent);
}


void rightRotate(struct node *Parent)
{
	struct node *child = Parent->left;
	struct node *Y = child->right;
	struct node *gr_parent = Parent->parent;
	if(gr_parent!= NULL)
	{
		if(gr_parent->right == Parent)
            gr_parent->right = child;
		else
            gr_parent->left = child;
	}
	if(Y != NULL)
		Y->parent = Parent;
        child->parent = gr_parent;
        child->right = Parent;

	Parent->parent = child;
	Parent->left = Y;
}
void leftRotate(struct node *Parent)
{
	struct node *child = Parent->right;
	struct node *Y = child->left;
	struct node *gr_parent = Parent->parent;
	if(gr_parent!=NULL)
	{
		if(gr_parent->right == Parent)
            gr_parent->right = child;
		else
            gr_parent->left = child;
	}
	if(Y !=NULL)
		Y->parent = Parent;
        child->parent = gr_parent;
        child->left = Parent;

       Parent->parent = child;
        Parent->right = Y;
}

void Splay(struct node *child)
{
	while(1)
	{
		struct node *parent = child->parent;
		if(parent==NULL)
            break;
		struct node *gr_parent = parent->parent;

		if(gr_parent==NULL)//Zig //Zag
		{
			if(parent->left == child)
				rightRotate(parent); //zig
			else
				leftRotate(parent);//zag
			break;
		}
		if(gr_parent->left == parent)
		{
			if(parent->left == child)
			{//ZigZig
				rightRotate(gr_parent);
				rightRotate(parent);
			}
			else
			{//ZagZig
				leftRotate(parent);
				rightRotate(gr_parent);
			}
		}
		else
		{
			if(parent->left == child)
			{//ZigZag
				rightRotate(parent);
				leftRotate(gr_parent);
			}
			else
			{//ZagZag
				leftRotate(gr_parent);
				leftRotate(parent);
			}
		}
	}
	root=child;
}



void Inorder(struct node *Z)
{
	if(Z==NULL)
        return;

	Inorder(Z->left);
	printf("vertex: %d ",Z->vertex);

	if(Z->left != NULL)
        printf("left: %d ",Z->left->vertex);
	if(Z->right != NULL)
        printf("right: %d ",Z->right->vertex);

	puts("");
	Inorder(Z->right);
}

struct node* Find(int vertex)
{
	if(root==NULL)
    return NULL;
    struct 	node *Parent = root;

	while(Parent)
	{
		if(Parent->vertex == vertex)
			break;
		if(vertex < (Parent->vertex))
		{
			if(Parent->left !=NULL)
				Parent = Parent->left;
			else
				break;
		}
		else
		{
			if(Parent->right != NULL)
				Parent = Parent->right;
			else
				break;
		}
	}
	Splay(Parent);
	if(Parent->vertex == vertex)
        return Parent;
	else
        return NULL;
}

bool Delete(int vertex)
{
	struct node *N = Find(vertex);

	if(N==NULL)
        return 0;

	Splay(N);

	struct node *Parent = N->left;

	if(Parent==NULL)
	{
		root = N->right;
		root->parent = NULL;
		free(N);
		return 1;
	}

	while(Parent->right)
        Parent = Parent->right;

	if(N->right != NULL)
	{
		Parent->right=N->right;
	}
	root=N->left;
	root->parent=NULL;
	free(N);
	return 1;
}


int main()
{

    printf ("\n //****//  Splay tree  //****//\n\n");

    while(1)
    {
        printf("\n1. Insert. \n2. Delete. \n3. Search. \n4. Display. \n5. Exit.\n");

        int ch,data;
        scanf("%d",&ch);

        if(ch == 1)
        {
            printf("Enter the Node You want to Insert:");
            scanf("%d",&data);
            Insert(data);
        }
        else if(ch == 2)
        {
            printf("Enter the Node You want to Delete:");
			scanf("%d",&data);
			if(Delete(data)!=NULL)
				printf("Deleted %d!\n",data);
			else
				printf("Not Find %d!\n",data);
        }
        else if(ch == 3)
        {
            printf("Enter the Node You want to Search:");
            scanf("%d",&data);
            if(Find(data)==NULL)
				printf("Not Find %d\n",data);
			else
				printf("Found %d \n",data);
        }
        else if(ch == 4)
        {
            if(root !=NULL)
                printf("root: %d\n",root->vertex);
                Inorder(root);
        }
        else if(ch == 5)
        {
            break;
        }
        else
            printf("Wrong Value Input.!!!!!!\n");
    }

}


