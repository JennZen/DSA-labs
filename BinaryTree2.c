#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    int balance;
    struct node* left;
    struct node* right;
} node;

node* inputTree();
void inorder(node* Node);
node* findTree(int value, node* Node);
void addtoTree(node* Node);
node* findRightMin(node* root);
node* deleteTree(node* root, int value);
void freeTree(node* Node);

node* inputTree() {
    int option;
    node* Node;

    printf("Do you want to create a node? (0-No, 1-Yes): ");
    scanf("%d", &option);

    if (option == 0) {
        return NULL;
    } else if (option != 1) {
        printf("Input error\n");
        exit(1);
    }

    Node = (node*)malloc(sizeof(node));
    if (Node == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }

    printf("Enter key: ");
    scanf("%d", &Node->key);

    printf("Left child of node %d\n", Node->key);
    Node->left = inputTree();

    printf("Right child of node %d\n", Node->key);
    Node->right = inputTree();

    return Node;
}

void inorder(node* Node) {
    if (Node == NULL) {
        return;
    }

    inorder(Node->left);
    printf(
        "Node %d: %p; Left child: %p; Right child: %p\n",
        Node->key,
        (void*)Node,
        (void*)Node->left,
        (void*)Node->right
    );
    inorder(Node->right);
}

node* findTree(int value, node* Node) {
    if (Node == NULL) {
        return NULL;
    }

    if (Node->key == value) {
        return Node;
    }

    node* left = findTree(value, Node->left);
    if (left != NULL) {
        return left;
    }

    return findTree(value, Node->right);
}

void addtoTree(node* Node) {
    int value;
    node* new;

    printf("Which node should become the parent of the new node? Enter key: ");
    scanf("%d", &value);

    Node = findTree(value, Node);
    if (Node == NULL) {
        printf("Node not found!\n");
        return;
    }

    printf("Node found!\n");

    new = (node*)malloc(sizeof(node));
    if (new == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }

    if (Node->left == NULL) {
        Node->left = new;
    } else if (Node->right == NULL) {
        Node->right = new;
    } else {
        printf("No space available!\n");
        free(new);
        return;
    }

    printf("Enter key of the new node: ");
    scanf("%d", &new->key);
    new->left = NULL;
    new->right = NULL;
}

// !!! this function assumes that the given tree is a BST
node* findRightMin(node* root) {
    if (root == NULL) {
        return NULL;
    }

    while (root->left != NULL) {
        root = root->left;
    }

    return root;
}

node* deleteTree(node* root, int value) {
    if (root == NULL) {
        return NULL;
    }

    if (value < root->key) {
        root->left = deleteTree(root->left, value);
        return root;
    } else if (value > root->key) {
        root->right = deleteTree(root->right, value);
        return root;
    } else {
        printf("Node found!\n");

        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->right == NULL) {
            node* temp = root->left;
            free(root);
            return temp;
        } else if (root->left == NULL) {
            node* temp = root->right;
            free(root);
            return temp;
        } else {
            node* temp = findRightMin(root->right);
            root->key = temp->key;
            root->right = deleteTree(root->right, temp->key);
            return root;
        }
    }
}

void freeTree(node* Node) {
    if (Node == NULL) {
        return;
    }

    freeTree(Node->left);
    freeTree(Node->right);
    free(Node);
}


int main() {
    int choice;
    int value;
    node* root = NULL;
    node* found = NULL;

    do {
        printf("\n\tMenu\n");
        printf("1. Input binary tree\n");
        printf("2. Output binary tree\n");
        printf("3. Add a new element\n");
        printf("4. Delete an element\n");
        printf("5. Exit program\n");
        printf("Enter operation: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                root = inputTree();
                break;
            case 2:
                inorder(root);
                break;
            case 3:
                addtoTree(root);
                break;
            case 4:
                printf("Enter key of node to delete: ");
                scanf("%d", &value);
                found = findTree(value, root);
                if (found == NULL) {
                    printf("Node not found!\n");
                } else {
                    root = deleteTree(root, value);
                }
                break;
            case 5:
                printf("Exiting the program...");
                freeTree(root);
                exit(0);
        }
    } while (choice != 5);

    return 0;
}
