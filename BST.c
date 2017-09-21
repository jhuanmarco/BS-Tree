#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int info;
	struct node *left;
	struct node *right;
} NODE;


char mainMenu(){
	char option;
	printf("\nBinary Search Tree (BST)\n\nType:\n1 - Create BST\n2 - Add Node\n3 - Search Node\n4 - Del Node\n5 - Destroy BST\n6 - Print BST\n0 - Exit\n");
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

void postOrder(NODE *walk){
	if(walk){
		postOrder(walk->left);
		postOrder(walk->right);
		printf("%d\n", walk->info);
	}

	return;
}

void preOrder(NODE *walk){
	if(walk){
		printf("%d\n", walk->info);
		preOrder(walk->left);
		preOrder(walk->right);
	}

	return;	
}

void inOrder(NODE *walk){
	if(walk){
		inOrder(walk->left);
		printf("%d\n", walk->info);
		inOrder(walk->right);
	} 

	return;
}

void destroyBST(NODE **root){
	*root = NULL;
	printf("BST Successful Destroyed\n");
	return;
}

int searchMatchesNode(NODE *root, int i){
	int matches = 0; 

	if(!root) return 0;
	
	if(root->info == i) matches++;

	if(i < root->info){
		matches += searchMatchesNode(root->left, i);
	} else {
		matches += searchMatchesNode(root->right, i);
	}

	return matches;
}

void searchNode(NODE *root){
	int infoSearch, matches;
	
	printf("Enter The Info to Search: ");
	scanf(" %d", &infoSearch);

	matches = searchMatchesNode(root, infoSearch);
	if(matches == 0) {
		printf("There's no Match for this Info\n");
		return;
	}

	printf("We Found %d Matche's for this Info\n", matches);
	return;
}

void deleteNode(NODE *root){


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
				if(!root){
					printf("BST Not Created, Go to Opt.1\n\n");
					break;
				}	

				searchNode(root);
			break;
			case '4':

			break;
			case '5':
				if(!root){
					printf("BST Not Created, Go to Opt.1\n\n");
					break;
				}

				destroyBST(&root);
			break;
			case '6':
				if(root){
					printf("Tree Traversals:\nPre Order:\n");
					preOrder(root);	
					printf("\nIn Order:\n");
					inOrder(root);
					printf("\nPost Order:\n");
					postOrder(root);
				} else {
					printf("BST Not Created, Go to Opt.1\n\n");
				}

			break;
			default:
			
			break;
		}
		
		

	} while(menu != '0');
}	
