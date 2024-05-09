#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node* left;
	struct node* right;
	int ht;
};
struct node* root = NULL;

int height (struct node* root){
	int lh, rh;
	
	if (root == NULL){
		return 0;
	}
	if (root->left == NULL){
		lh = 0;
	}
	else{
		lh = 1 + root->left->ht;
	}
	if (root->right == NULL){
		rh = 0;
	}
	else {
		rh = 1 + root->right->ht;
	}
	if (lh > rh)
		return lh;
	return rh;
}

struct node* rotate_left(struct node* root)
{
    struct node* right_child = root->right;
    root->right = right_child->left;
    right_child->left = root;
 
    root->ht = height(root);
    right_child->ht = height(right_child);
 
    return right_child;
}

struct node* rotate_right(struct node* root)
{
    struct node* left_child = root->left;
    root->left = left_child->right;
    left_child->right = root;
 
    root->ht = height(root);
    left_child->ht = height(left_child);
 
    return left_child;
}

struct node* min_value_node(struct node* node) {
    struct node* current = node;

    while (current->left != NULL) {
        current = current->left;
    }

    return current;
}


int balance_factor(struct node* root){
	int lh, rh;
	
	if (root == NULL){
		return 0;
	}
	if (root->left == NULL){
		lh = 0;
	}
	else{
		lh = 1 + root->left->ht;
	}
	if (root->right == NULL){
		rh = 0;
	}
	else {
		rh = 1 + root->right->ht;
	}
	return lh - rh;
}

struct node* create_node(int data){
	struct node* new_node = (struct node*) malloc (sizeof(struct node));
	new_node->data = data;
	new_node->right = NULL;
	new_node->left = NULL;
	
	return new_node;
}

struct node* insert (struct node* root, int data){
	if(root == NULL){
		struct node* new_node = create_node(data);
		root = new_node;
	}
	else if ( data > root->data){
		root->right = insert(root->right, data);
		
		if (balance_factor(root) == -2){
			if (data > root->right->data){
				root = rotate_left(root);
			}
			else{ 
				root->right = rotate_right(root->right);
				root = rotate_left(root);
			}			
		}		
	}
	else{
		root->left = insert(root->left, data);
		
		if (balance_factor(root) == 2){
			if (data < root->left->data){ 
				root = rotate_right(root);
			}
			else{
				root->left = rotate_left(root->left);
				root = rotate_right(root);

			}
		}
	}
	root->ht = height(root);
	return root;
}


void inorder(struct node* root)
{
    if (root == NULL)
    {
        return;
    }
 
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}
 
void preorder(struct node* root)
{
    if (root == NULL)
    {
        return;
    }
 
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}
 
void postorder(struct node* root)
{
    if (root == NULL)
    {
        return;
    }
 
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

struct node* delete_node(struct node* root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->data) {
        root->left = delete_node(root->left, key);
    } else if (key > root->data) {
        root->right = delete_node(root->right, key);
    } else {
        if ((root->left == NULL) || (root->right == NULL)) {
            struct node* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else { 
                *root = *temp; 
            }
            free(temp);
        } else {
            struct node* temp = min_value_node(root->right);

            root->data = temp->data;

            root->right = delete_node(root->right, temp->data);
        }
    }

    if (root == NULL) {
        return root;
    }

    root->ht = max(height(root->left), height(root->right)) + 1;

    int balance = balance_factor(root);


    if (balance > 1 && balance_factor(root->left) >= 0) {
        return rotate_right(root);
    }

    if (balance > 1 && balance_factor(root->left) < 0) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }

    if (balance < -1 && balance_factor(root->right) <= 0) {
        return rotate_left(root);
    }

    if (balance < -1 && balance_factor(root->right) > 0) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }

    return root;
}

struct node* search(struct node* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }

    
    if (root->data < key) {
        return search(root->right, key);
    }

    
    return search(root->left, key);
}

int main(){

	root = insert(root, 10);
	root = insert(root, 15); 
	root = insert(root, 20); 
	root = insert(root, 9);
	root = insert(root, 5);
	root = insert(root, 16);
	root = insert(root, 17);
	root = insert(root, 8);
	root = insert(root, 6);
	
	root = delete_node(root, 5);
	

	int key = 5;
    struct node* result = search(root, key);
    if (result != NULL) {
        printf("angka %d ditemukan.\n", key);
    } else {
        printf("angka %d tidak ditemukan.\n", key);
    }

	preorder(root);
	return 0;
}
