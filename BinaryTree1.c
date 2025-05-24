#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 100

typedef struct Node
{
    char name[MAX_LEN];
    char address[MAX_LEN];
    char telephone[MAX_LEN];
    int number;
    int price;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct n_q
{
    Node *address;
    struct n_q *next;
} n_q;

typedef struct n_st
{
    Node *address;
    struct n_st *prev;
} n_st;

Node *root;
n_q *first_q;
n_q *last_q;
n_st *head_st;

void inQ(Node *new);
Node *deQ();
void push(Node *new);
Node *pop();
void inputNode(Node* z);
void printNode(Node* node);
void createTreeQ();
void printTreeQ();
void createTreeS();
void printTreeS();
void preOrder(Node* node);
void inOrder(Node* node);
void postOrder(Node* node);
void printTraversals();
int sizeTree(Node* node);
void inputToArray(Node* arr, Node* node, int* i);
Node* sortArray(Node* arr, int size);
Node* sortTree(Node* arr, int start, int end);
void freeTree(Node* node);


void inQ(Node *new)
{
    n_q *node = (n_q *)calloc(1, sizeof(n_q));
    if (node == NULL)
    {
        printf("Memory allocation error\n");
        return;
    }
    node->address = new;
    node->next = NULL;
    if (first_q == NULL)
    { // if the queue is empty
        first_q = node;
    }
    else
    { // if the queue is not empty
        last_q->next = node;
    }
    last_q = node;
}

Node *deQ()
{
    n_q *temp = first_q; //save first element
    Node *adr = temp->address;
    if (temp == last_q)
    { //if there was only 1 element in the queue
        first_q = NULL;
        last_q = NULL;
    }
    else
    {
        first_q = temp->next;
    }
    free(temp);
    return adr;
}

void push(Node *new)
{
    n_st *temp = (n_st *)calloc(1, sizeof(n_st));
    if (temp == NULL)
    {
        printf("Memory allocation error\n");
        return;
    }
    temp->prev = head_st;
    temp->address = new;
    head_st = temp;
}

Node *pop()
{
    if (head_st == NULL)
    {
        return NULL;
    }
    n_st *temp = head_st;
    Node *result = temp->address;
    head_st = temp->prev;
    free(temp);
    return result;
}

void inputNode(Node *z)
{
    printf("Cinema's name: ");
    fgets(z->name, MAX_LEN, stdin);
    z->name[strcspn(z->name, "\n")] = '\0';
    printf("Address: ");
    fgets(z->address, MAX_LEN, stdin);
    z->address[strcspn(z->address, "\n")] = '\0';
    printf("Phone number: ");
    fgets(z->telephone, MAX_LEN, stdin);
    z->telephone[strcspn(z->telephone, "\n")] = '\0';
    printf("Number of seats: ");
    scanf("%d", &z->number);
    getchar();
    printf("Price: ");
    scanf("%d", &z->price);
    getchar();
}

void printNode(Node* node){
    printf("Address: %s\nPhone: %s\nNumber of seats: %d\nPrice: $%d\n\n\n", node->address, node->telephone, node->number, node->price);
}

void createTreeQ()
{
    int option;
    printf("Do you want to input the root?(0-No, 1-Yes): ");
    scanf("%d", &option);
    getchar();
    if (option == 0)
    {
        return;
    }
    root = (Node *)calloc(1, sizeof(Node));
    first_q = NULL;
    last_q = NULL;
    if (root == NULL)
    {
        printf("Memory allocation error\n");
        return;
    }
    inputNode(root);
    inQ(root);
    while (first_q)
    {
        Node *temp = deQ();
        printf("Do you want to create the left son of node %s?(0-No, 1-Yes): ", temp->name);
        scanf("%d", &option);
        getchar();
        if (option == 0)
        {
            temp->left = NULL;
        }
        else
        {
            temp->left = calloc(1, sizeof(Node));
            if (temp->left == NULL)
            {
                printf("Memory allocation error\n");
                return;
            }
            inputNode(temp->left); 
            inQ(temp->left);
        }
        printf("Do you want to create the right son of node %s?(0-No, 1-Yes): ", temp->name);
        scanf("%d", &option);
        getchar();
        if (option == 0)
        {
            temp->right = NULL;
        }
        else
        {
            temp->right = calloc(1, sizeof(Node));
            if (temp->right == NULL)
            {
                printf("Memory allocation error\n");
                return;
            }
            inputNode(temp->right);
            inQ(temp->right);
        }
    }
}

void printTreeQ()
{
    last_q = NULL;
    first_q = NULL;
    inQ(root);
    Node *temp;
    while (first_q)
    {
        temp = deQ();
        printf("Name: %s (%p); Left son: (%p); Right son: (%p).\n", temp->name, (void *)temp, (void *)temp->left, (void *)temp->right);
        printNode(temp);
        if (temp->left != NULL)
        {
            inQ(temp->left);
        }
        if (temp->right != NULL)
        {
            inQ(temp->right);
        }
    }
}

void createTreeS()
{
    int option;
    printf("Do you want to input the root?(0-No, 1-Yes): ");
    scanf("%d", &option);
    getchar();
    if (option == 0)
    {
        return;
    }
    root = (Node *)calloc(1, sizeof(Node));
    head_st = NULL;
    if (root == NULL)
    {
        printf("Memory allocation error\n");
        return;
    }
    inputNode(root);
    push(root);
    while (head_st)
    {
        Node *temp = pop();
        printf("Do you want to create the right son of node %s?(0-No, 1-Yes): ", temp->name);
        scanf("%d", &option);
        getchar();
        if (option == 0)
        {
            temp->right = NULL;
        }
        else
        {
            temp->right = calloc(1, sizeof(Node));
            if (temp->right == NULL)
            {
                printf("Memory allocation error\n");
                return;
            }
            inputNode(temp->right); 
            push(temp->right);
        }
        printf("Do you want to create the left son of node %s?(0-No, 1-Yes): ", temp->name);
        scanf("%d", &option);
        getchar();
        if (option == 0)
        {
            temp->left = NULL;
        }
        else
        {
            temp->left = calloc(1, sizeof(Node));
            if (temp->left == NULL)
            {
                printf("Memory allocation error\n");
                return;
            }
            inputNode(temp->left);
            push(temp->left);
        }
    }
}

void printTreeS()
{
    head_st = NULL;
    push(root);
    Node *temp;
    while (head_st)
    {
        temp = pop();
        printf("Name: %s (%p); Left son: (%p); Right son: (%p).\n", temp->name, (void *)temp, (void *)temp->left, (void *)temp->right);
        printNode(temp);
        if (temp->right != NULL)
        {
            push(temp->right);
        }
        if (temp->left != NULL)
        {
            push(temp->left);
        }
    }
}


void preOrder(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    printf("Name: %s (%p); Left son: (%p); Right son: (%p).\n", node->name, (void *)node, (void *)node->left, (void *)node->right);
    printNode(node);
    preOrder(node->left);
    preOrder(node->right);
}

void inOrder(Node *node){
    if (node == NULL)
    {
        return;
    }
    inOrder(node->left);
    printf("Name: %s (%p); Left son: (%p); Right son: (%p).\n", node->name, (void *)node, (void *)node->left, (void *)node->right);
    printNode(node);
    inOrder(node->right);
}

void postOrder(Node *node){
    if (node == NULL)
    {
        return;
    }
    postOrder(node->left);
    postOrder(node->right);
    printf("Name: %s (%p); Left son: (%p); Right son: (%p).\n", node->name, (void *)node, (void *)node->left, (void *)node->right);
    printNode(node);
}

void printTraversals(){
    printf("\n\n");
    printf("Preorder:\n");
    preOrder(root);
    printf("\n\n");
    printf("Inorder:\n");
    inOrder(root);
    printf("\n\n");
    printf("Postorder:\n");
    postOrder(root);
    printf("\n\n");
    printf("BFS:\n");
    printTreeQ();
    printf("\n\n");
}

int sizeTree(Node* node){
    int size=0;
    if(!node){
        return 0;
    }
    size = 1 + sizeTree(node->right) + sizeTree(node->left);
    return size;
}

void inputToArray(Node* arr, Node* node, int* i){
    if(!node){
        return;
    }
    inputToArray(arr, node->left, i);
    arr[(*i)++] = *node;
    inputToArray(arr, node->right, i);
}

Node* sortArray(Node* arr, int size){
    Node temp;
    for(int i=0;i<size;i++){
        for(int j=0; j<size-1-i;j++){
            if(strcmp(arr[j].name, arr[j+1].name) < 0){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    return arr;
}

Node* sortTree(Node* arr, int start, int end){
    if(start>end){
        return NULL;
    }
    int mid = (end+start)/2;
    Node* root = (Node*) malloc(sizeof(Node));
    if(root==NULL){
        printf("Memory allocation memory!\n");
        exit(1);
    }
    *root = arr[mid];
    root->left = sortTree(arr, mid+1, end);
    root->right = sortTree(arr, start, mid-1);
    return root;
}

void freeTree(Node* node) {
    if (node == NULL) {
        return;
    }
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int main()
{
    int choice = 0;
    int i;
    do
    {
        printf("\t\tMENU\n");
        printf("1. Input binary tree with a queue.\n");
        printf("2. Input binary tree with a stack.\n");
        printf("3. Output binary tree with a queue.\n");
        printf("4. Output binary tree with a stack.\n");
        printf("5. Output 4 traversals.\n");
        printf("6. Sort.\n");
        printf("7. Exit.\n\n");
        printf("Input an operation: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            createTreeQ();
            break;
        case 2:
            createTreeS();
            break;
        case 3:
            printTreeQ();
            break;
        case 4:
            printTreeS();
            break;
        case 5:
            printTraversals();
            break;
        case 6:
            i=0;
            int size = sizeTree(root);
            Node* arr = (Node*)malloc(size*sizeof(Node));
            inputToArray(arr,root,&i);
            arr = sortArray(arr, size);
            root = sortTree(arr, 0, size-1);
            free(arr);
            break;
        case 7:
            printf("Exiting program...\n");
            freeTree(root);
            return 1;
        }
    } while (choice != 7);
    return 0;
}
