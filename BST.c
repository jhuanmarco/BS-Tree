#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int info;
	struct node *left;
	struct node *right;
} NODE;


char mainMenu(){
	char option;
	printf("\nBinary Search Tree (BST)\n\nType:\n1 - Create BST\n2 - Add Node\n3 - Del Node\n4 - Print BST\n0 - Exit\n");
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

void searchAddNode(NODE *node, NODE *new, int info){
	
	if(node->info < info){
		if(node->left){
			node = node->left;
			searchAddNode(node, new, info);
		}
			node->left = new;
	} else {
		if(node->right){
			node = node->right;
			searchAddNode(node, new, info);
		}
			node->right = new;
	}
	
	
	return;
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




//PRINT


void erd (NODE *r) {
   if (r != NULL) {
      erd (r->left);
      printf ("%d\n", r->info);
      erd (r->right); 
   }
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
				erd(root);
			
			break;
			default:
			
			break;
		}
		
		

	} while(menu != '0');
}	
