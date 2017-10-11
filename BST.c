#include <stdio.h>
#include <stdlib.h>

#define NOCHIL -2
#define LECHIL -3
#define RICHIL 1
#define DOCHIL 0

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

NODE *searchedNode(NODE *node, int info){	
	if(info > node->info) {
		node = searchedNode(node->right, info);
	} else if(info < node->info) {
		node = searchedNode(node->left, info);
	}
		
	return node;
}

NODE *searchFather(NODE *node, int info){
	while(1){
		if((node->left->info == info) || (node->right->info == info)){
			return node;		
		} else {
			if(info >= node->info){
				node = node->right;
			}else if (info < node->info){
				node = node->left;		
			}
		}
	}

}

NODE *minNode(NODE *node){
	while(node->left){
		node = node->left;		
	}
	
	return node;
}



NODE *deleteNode(NODE *root){
	int nodeInfo, matches, leftRight = 0, leftRightF; //if leftRight == 0 double children's, if -3 only left children, if +1 only right children, if -2 dont have children 
	NODE *node, *father;
	printf("Enter The Node Info to Delete: ");
	scanf(" %d", &nodeInfo);
	matches = searchMatchesNode(root, nodeInfo);
	if(matches == 0) { //if node dont exist
		printf("There's no match for this info\n");
		return root;
	}
	node = searchedNode(root, nodeInfo); //node pointer in selected node to delete
	
	if(node != root) father = searchFather(root, nodeInfo);
	
	if(node->left == NULL){
		leftRight += 1; //single children in right
	} // -2 no children, -3 children left, 0 double childreens, 1 children right
	if(node->right == NULL){
		leftRight += -3; //single chindren in left
	}
	
	if(root == node){
	
		NODE *aux;
		NODE *auxP;
		
		if(leftRight == NOCHIL){
			free(root);
			return NULL;
		} else if(leftRight == RICHIL){
			root = root->right;	
			return root;	
		} else if (leftRight == LECHIL){
			root = root->left;
			return root;		
		} else {
			aux = minNode(node->right);
			auxP = searchFather(root, aux->info);
		
			if(auxP->left == aux){
				auxP->left = aux->right;
			}else{
				auxP->right = aux->left;		
			}
				
			aux->left = root->left;
			aux->right = root->right;
			free(root);
					
		}
		
		printf("Successfull Deleted\n");
		return aux;
	}
		
	if(leftRight != DOCHIL){ //se nao houver filhos duplos
		if(father->left == node){
			leftRightF = -1; //caso o filho a ser removido esteja na esquerda
		} else {
			leftRightF = 1; //caso o filho a ser removido esteja na direita
		}
		if(leftRight == NOCHIL){
		
			if(leftRightF == -1){
				father->left = NULL;		
			} else {
				father->right = NULL;			
			}
			free(node);

		} else if(leftRight == LECHIL || leftRight == RICHIL){
			NODE *aux;
			
			if(leftRight == LECHIL){
				aux = node->left;		
			} else {
				aux = node->right;			
			}
			
			if(leftRightF == -1) {
				father->left = aux;	
			} else {
				father->right = aux;		
			}
						
			free(node);
		}
	
	} else { //aqui remove caso houver 2 filhos
	
		NODE *aux = minNode(node->right);
		NODE *auxP;
		
	
		if(aux->info != node->info){ 
			auxP = searchFather(root, aux->info);
		} else {
			auxP = searchFather(node, aux->info);		
		}
		
		if(auxP->left == aux){ //se o auxiliar for filho a esquerda
			auxP->left = aux->right;
			
		}else if (auxP->right == aux){ 	
			auxP->right = aux->left;		
		}
		
		if(father->left == node){
			father->left = aux;	
		} else if (father->right == node){
			father->right = aux;
		}
		
		if(aux->left != aux ) aux->left = node->left; 
		
		if(aux->right != aux) aux->right = node->right;
		
		free(node);
		
	}
	
	printf("Successfull Deleted\n");
	return root;
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
				if(!root){
					printf("BST Not Created, Go to Opt.1\n\n");
					break;
				}	

				root = deleteNode(root);
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
