#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 100

typedef struct Cinema
{
    char name[MAX_LEN];
    char address[MAX_LEN];
    char telephone[MAX_LEN];
    int number;
    int price;
    struct Cinema* next;
} Cinema;

void Allocate_cinema(int n);
void Input_cinema(Cinema* current);
void Print_node(Cinema* current);
Cinema* Search_cinema();
void Free_memory();
void Edit_cinema();
void Switch_cinemas(Cinema* a, Cinema* b);
void Sort_cinema(int n);
void Print_menu();
int Count_nodes();
Cinema* Last_node_address();
void Append();
void Delete();
void Divide();
void Link();
void Read_from_file();
void Write_to_file();
void Insert();

Cinema* head = NULL;
Cinema* head_2 = NULL;
FILE* fptr;
void Allocate_cinema(int n)
{

    printf("Input number of elements: ");
    scanf("%d", &n);
    getchar();
    if (0>=n)
    {
        printf("Input error!\n");
        return;
    }

    Cinema* current = NULL;
    Cinema* last = NULL;
    for(int i=0; i<n; i++)
    {
        current = calloc(1, sizeof(Cinema));
        if(current == NULL)
        {
            printf("Memory allocation error\n!");
            break;
        }
        if (head == NULL)
        {
            head = current;
            last = current;

        }
        else
        {
            last -> next = current;
            last = current;
        }
    }
    last->next = NULL;
    printf("Memory was allocated!\n");
}

void Input_cinema(Cinema* current)
{
    printf("Input cinema's name: ");
    fgets(current->name,MAX_LEN,stdin);
    current->name[strcspn(current->name,"\n")] = '\0';
    printf("Address: ");
    fgets(current->address, MAX_LEN, stdin);
    current->address[strcspn(current->address, "\n")] = '\0';
    printf("Phone number: ");
    fgets(current->telephone, MAX_LEN, stdin);
    current->telephone[strcspn(current->telephone, "\n")] = '\0';
    printf("Number of seats: ");
    scanf("%d", &current->number);
    getchar();
    printf("Price: $");
    scanf("%d", &current->price);
    getchar();
    printf("\n");
}

void Print_node(Cinema* current)
{

    printf("Name: %s\n", current->name);
    printf("Address: %s\n", current->address);
    printf("Phone number: %s\n", current->telephone);
    printf("Number of seats: %d\n", current->number);
    printf("Price: $%d\n", current->price);
    printf("Address of the element: %p\n", (void*)current);
    printf("Address of the next element: %p\n", (void*)current->next);
    printf("\n");
}

Cinema* Search_cinema()
{
    char sentence[MAX_LEN];
    int flag = 0;
    Cinema* current = head;
    printf("Input cinema's name: ");
    fgets(sentence,MAX_LEN,stdin);
    sentence[strcspn(sentence, "\n")] = '\0';
    while(current)
    {
        if(stricmp(current->name, sentence) == 0)
        {
            flag = 1;
            return current;

        }
        current = current->next;

    }
    if(flag == 0)
    {
        printf("Cinema was not found!\n");
    }
}

void Free_memory()
{
    if(head == NULL)
    {
        printf("Error! The list is empty.\n");
        return;
    }
    Cinema* current = head;
    Cinema* temp = NULL;
    while(current)
    {
        temp = current;
        current=current->next;
        free(temp);
    }
    head = NULL;
    printf("Memory was free()ed!\n");
}

void Edit_cinema()
{
    char sentence[MAX_LEN];
    int flag = 0;
    Cinema* current = head;
    printf("Input cinema's name: ");
    fgets(sentence,MAX_LEN,stdin);
    sentence[strcspn(sentence, "\n")] = '\0';
    while(current)
    {
        if(stricmp(current->name, sentence) == 0)
        {
            printf("Cinema was found!\n");
            flag = 1;
            Input_cinema(current);
            return;
        }
        current = current->next;

    }
    if(flag == 0)
    {
        printf("Cinema was not found!\n");
    }
}

/*//more complicated swap() function
void Switch_cinemas(Cinema* a, Cinema* b)
{
    if (a == b) return;

    Cinema* prev_a = NULL;
    Cinema* prev_b = NULL;
    Cinema* current = head;

    while (current && current->next) {
        if (current->next == a) prev_a = current;
        if (current->next == b) prev_b = current;
        current = current->next;
    }

    if (prev_a) prev_a->next = b;
    if (prev_b) prev_b->next = a;

    Cinema* temp = a->next;
    a->next = b->next;
    b->next = temp;

    if (head == a) head = b;
    else if (head == b) head = a;
}*/
void Switch_cinemas(Cinema* a, Cinema* b){
    Cinema* a_next = a->next;
    Cinema* b_next = b->next;
    Cinema t = *a;
    *a = *b;
    *b = t;
    a->next = a_next;
    b->next = b_next;
}

void Sort_cinema(int n){
    if(n == 1) return;
    for(int i=0;i<n-1;i++){
        Cinema* current = head;
        for(int j=0;j<n-i-1;j++){
            Cinema* current_n = current->next;
            if(strcmp(current->name, current_n->name)>0){
                Switch_cinemas(current, current_n);
            }
            current=current->next;
        }
    }
}

int Count_nodes(){
    Cinema* current = head;
    int counter = 0;
    while(current){
        counter++;
        current = current->next;
    }
    return counter;
}

Cinema* Last_node_address(){
    if(head == NULL){
        return NULL;
    }
    Cinema* current  = head;
    while(current->next){
        current=current->next;
    }
    return  current;

}

void Append(){
    Cinema* new_node = (Cinema*) malloc(sizeof(Cinema));
    if(new_node == NULL){
        printf("Memory allocation error!\n");
        return;
    }
    if (head == NULL){
        head = new_node;
        return;
    }
    Cinema* last = Last_node_address();
    Input_cinema(new_node);
    last->next = new_node;
    new_node->next = NULL;
}

void Delete(){
    Cinema* node = Search_cinema();
    if(node==NULL){
        printf("Cinema was not found!\n");
        return;
    }
    Cinema* current = head;
    Cinema* prev;
    Cinema* next_node = node->next;    
    if(node==head && Count_nodes()>1){   
        prev = head;
        head = head->next;
        free(prev);
        return;
    }
    else if(node==head){   
        free(head);
        head = NULL;
        return;
    }
    while(current){
        if(current->next == node){
            prev = current;     
            break;
        }
        current=current->next;
    }
    free(prev->next);
    current->next=next_node;
}

void Divide(){
    if (head == NULL){
        printf("Error! The list is empty!\n");
        return;
    }
    int n1;
    int n2;
    Cinema* current = head;
    Cinema* last = NULL;
    printf("Input number of elements for the first list: ");
    scanf("%d", &n1);
    getchar();
    printf("Input number of elements for the second list: ");
    scanf("%d", &n2);
    getchar();
    if(n1+n2 < Count_nodes()){
        printf("Not enough elements for dividing!\n");
        return;
    }
    for(int i=0; i<n1; i++){
        last =  current;
        current = current->next;
    }
    head_2 = last->next;
    last->next = NULL;
}

void Link(){
    if(head == NULL || head_2 == NULL){
        printf("Error: one of the lists is empty!\n");
        return;
    }
    Cinema* last_1 = Last_node_address();
    last_1->next = head_2;
    head_2 = NULL;
}

void Read_from_file(){
    int option;
    printf("From what type of file do you want to read information? (0-binary, 1-text): ");
    scanf("%d", &option);
    if(option==0){
        fptr = fopen("lab9.txt", "rb");
    }
    else if(option == 1){
        fptr = fopen("lab9.txt", "r");
    }
    Cinema* last = NULL;
    if(fptr == NULL){
        printf("Error! File was not opened!\n");
        return;
    }
    Free_memory();
    while(feof(fptr)!=0){
        Cinema* current = (Cinema*)malloc(sizeof(Cinema));
        if(current == NULL){
            printf("Memory allocation error!\n");
            return;
        }
        fgets(current->name,MAX_LEN,fptr);
        current->name[strcspn(current->name,"\n")] = '\0';
        fgets(current->address, MAX_LEN, fptr);
        current->address[strcspn(current->address, "\n")] = '\0';
        fgets(current->telephone, MAX_LEN, fptr);
        current->telephone[strcspn(current->telephone, "\n")] = '\0';
        fscanf(fptr, "%d",&current->number);
        fscanf(fptr, "%d",&current->price);
        if(head==NULL){
            head = current;
            last = current;
        }
        else{
            last->next = current;
            last = current;
        }
    }
    last->next = NULL;
    fclose(fptr);
}
//version for binary and text files
/*void Write_to_file(){
    Cinema* current = head;
    int option;
    printf("To what type of file do you want to write information? (0-binary, 1-text): ");
    scanf("%d", &option);
    if(option == 0){
        fptr = fopen("lab9.txt", "wb");
    }
    else if(option == 1){
        fptr = fopen("lab9.txt", "w");
    }
    if(fptr == NULL){
        printf("Error! File wasn't opened!\n");
        return;
    }
    if(option == 1) {
        while(current){
            fprintf(fptr, "%s\n", current->name);
            fprintf(fptr, "%s\n", current->address);
            fprintf(fptr, "%s\n", current->telephone);
            fprintf(fptr, "%d\n", current->number);
            fprintf(fptr, "%d\n", current->price);
            current = current->next;
        }
    }
    else if(option == 0) {
        while(current){
            fwrite(current, sizeof(Cinema), 1, fptr);
            current = current->next;
        }
    }
    fclose(fptr);
}*/
//only for binary
void Write_to_file(){
    Cinema* current = head;
    fptr = fopen("lab9.txt", "wb");
    if(fptr == NULL){
        printf("Error\n");
        return;
    }

    while(current){
        fwrite(&current->name,sizeof(Cinema),1,fptr);
        fwrite(&current->address,sizeof(Cinema),1,fptr);
        fwrite(&current->telephone,sizeof(Cinema),1,fptr);
        fwrite(&current->number,sizeof(Cinema),1,fptr);
        fwrite(&current->price,sizeof(Cinema),1,fptr);
        current = current->next;
    }
    fclose(fptr);
}

void Insert(){
    int index;
    Cinema* prev;
    Cinema* current = head;
    Cinema* new_node = (Cinema*) malloc(sizeof(Cinema));
    if(new_node == NULL){
        printf("Memory allocation error!\n");
        return;
    }
    printf("Input new element's position: ");
    scanf("%d", &index);
    getchar();
    if(index<=0){
        printf("Input error!\n");
        return;
    }
    Input_cinema(new_node);
    if(index == 1){
        prev = head;
        head = new_node;
        new_node->next = prev;
        return;
    }
    else if(index == Count_nodes()){
        Append();
        return;
    }
    for(int i=1; i<index-1; i++){             
        current = current->next;
    }
    prev = current;
    Cinema* prev_n = prev->next;
    prev->next = new_node;
    new_node->next = prev_n;
}

void Print_menu()
{
    int n;
    int choice = 0;
    while(choice!=18)
    {
        printf("\tMenu\n");
        printf("1. Allocate memory for a linked list.\n");
        printf("2. Input.\n");
        printf("3. Output.\n");
        printf("4. Search.\n");
        printf("5. Edit an element.\n");
        printf("6. Swap 2 elements.\n");
        printf("7. Sort.\n");
        printf("8. Free memory.\n");
        printf("9. Append to the end.\n");
        printf("10. Delete element.\n");
        printf("11. Insert element.\n");
        printf("12. Last element's address.\n");
        printf("13. List's length.\n");
        printf("14. Divide list in 2 parts.\n");
        printf("15. Link 2 lists.\n");
        printf("16. Write to file.\n");
        printf("17. Read from file.\n");
        printf("18. Exit.\n");
        printf("Input an operation: ");
        scanf("%d", &choice);
        getchar();
        switch(choice)
        {
        case 1:
            Allocate_cinema(n);
            break;
        case 2:
            if(head == NULL)
            {
                printf("Error! The list is empty.\n");
                break;
            }
            Cinema* current = head;
            for(int i=1; i<=n; i++)
            {
                printf("Cinema number %d\n", i);
                Input_cinema(current);
                current = current->next;
            }
            break;
        case 3:
            if(head == NULL)
            {
                printf("Error! The list is empty.\n");
                break;
            }
            current = head;
            int i =1;
            while(current)
            {
                printf("Cinema number %d\n", i++);
                Print_node(current);
                current = current->next;
            }
            break;
        case 4:
            if(head == NULL)
            {
                printf("Error! The list is empty.\n");
                break;
            }

            Print_node(Search_cinema());
            break;
        case 5:
            if(head == NULL)
            {
                printf("Error! The list is empty.\n");
                break;
            }
            Edit_cinema();
            printf("The element was changed!\n");
            break;
        case 6:
            if(head == NULL)
            {
                printf("Error! The list is empty.\n");
                break;
            }
            Switch_cinemas(Search_cinema(), Search_cinema());
            break;
        case 7:
            if(head == NULL)
            {
                printf("Error! The list is empty.\n");
                break;
            }
            Sort_cinema(n);
            break;
        case 8:
            Free_memory();
            break;
        case 9:
            Append();
            break;
        case 10:
            Delete();
            break;
        case 11:
            Insert();
            break;
        case 12:
            printf("Last element's address: %p.\n", Last_node_address());
            break;
        case 13:
            printf("List's length: %d.\n", Count_nodes());
            break;
        case 14:
            Divide();
            break;
        case 15:
            Link();
            break;
        case 16:
            Write_to_file();
            break;
        case 17:
            Read_from_file();
            break;
        case 18:
            printf("Exiting program...");
            return;
        }
    }
}

int main()
{
    Print_menu();
    return 0;
}
