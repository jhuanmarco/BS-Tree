#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int info;
	struct node *left;
	struct node *right;
} NODE;


char mainMenu(){
	char option;
	printf("\nBinary Search Tree (BST)\n\nType:\n1 - Create BST\n2 - Add Node\n3 - Del Node\n4 - Destroy BST\n5 - Print BST\n0 - Exit\n");
	scanf(" %c", &option);
	printf("\n");
	
	return option;
}

int returnInfo(){
	int info;
	printf("Type Node Info: ");
	scanf(" %d", &info);
	
	return info; 
}

NODE *createNode(){
	NODE *newNode = malloc(sizeof(NODE));
	if(!newNode){
		 printf("Error: No Memory");
		 return NULL;
	}
	
	newNode->info = returnInfo();
	newNode->left = NULL;
	newNode->right = NULL;
	printf("Node Created, Info = %d\n", newNode->info);
	
	return newNode;
}

void addNode(NODE *root){
	NODE *newNode = createNode();
	NODE *walk = root;
	
	if(!newNode){
		 printf("Error: No Memory");
		 return;
	
	}
	
	while(1) {
		if(newNode->info < walk->info) {
			if (walk->left) {
				walk = walk->left;
				continue;
			} 

			walk->left = newNode;
			break;
			

		} else { 
			if (walk->right) {
				walk = walk->right;
				continue;
			}

			walk->right = newNode;
			break;
		}	

	}

}

void postorder(NODE *walk){
	if(walk){
		postorder(walk->left);
		postorder(walk->right);
		printf("%d\n", walk->info);
	}

	return;
}

void preorder(NODE *walk){
	if(walk){
		printf("%d\n", walk->info);
		preorder(walk->left);
		preorder(walk->right);
	}

	return;	
}

void inorder(NODE *walk){
	if(walk){
		inorder(walk->left);
		printf("%d\n", walk->info);
		inorder(walk->right);
	} 

	return;
}

void destroyBST(NODE **root){
	*root = NULL;
	printf("BST Successful Destroyed\n\n");
	return;
}

void searchNode(NODE *root){
	
}

void main(){
	char menu;
	NODE *root = NULL;	
	
	do {
		menu = mainMenu();
		switch(menu){
			case '1':
				if(root){
					printf("BST Root Already Created\n\n");
					break;
				}
				
				root = createNode();
				
			break;
			case '2':
				if(!root){
					printf("BST Not Created, Go to Opt.1\n\n");
					break;
				}
				
				addNode(root);
			
			break;
			case '3':
			
			break;
			case '4':
				if(!root){
					printf("BST Not Created, Go to Opt.1\n\n");
					break;
				}

				destroyBST(&root);
			break;
			case '5':
				if(root){
					printf("Tree Traversals:\nPre Order:\n");
					preorder(root);	
					printf("\nIn Order:\n");
					inorder(root);
					printf("\nPost Order:\n");
					postorder(root);
				} else {
					printf("BST Not Created, Go to Opt.1\n\n");
				}

			break;
			default:
			
			break;
		}
		
		

	} while(menu != '0');
}	
