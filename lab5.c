#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
	char* name;
	int size;
	struct node *next;
} NODE;

NODE *head = NULL;
NODE *tail = NULL;

int check_duplicate();
void insert(), delete(), print(), search_size();

//Main - Displays menu
int main() {
  int choice;
	while (choice != 0) {
    printf("\n1]Add Reservation \n2]Remove \n3]Print \n4]Search Size \n0]Exit\n");
		printf("\nEnter in choice: ");
		scanf("%d", &choice);
    	switch(choice) {
      		case 1: insert();
        		break;
      		case 2: delete();
        		break;
      		case 3: print();
        		break;
          case 4: search_size();
          	break;
      		default: choice = 0;
        		break;
    	}
	}
}

void insert() {
	char* name;
	int size;
	//Enter in Name
	printf("\nEnter in Name: ");
	scanf("%s", &name);
	//Enter in Size
  printf("\nEnter in Size: ");
	scanf("%d", &size);
	NODE *temp;
	if(head == NULL) {
		temp = (NODE*)malloc(sizeof(NODE));
		temp->size = size;
		strcpy(temp->name,name);
		head = temp;
		temp->next = NULL;
		tail=temp;
	}
	if(check_duplicate(name) == 0) {
		temp = (NODE*)malloc(sizeof(NODE));
		temp->size = size;  //temp of size is copies to size
		strcpy(temp->name, name);  //temp of name is copies to name
		temp->next=NULL;
		tail->next = temp;
		tail = temp;
	}
	else
		printf("'%s' has already been entered...please try again\n", &name);
}

void delete() {
	int i = 0;
	int size;
	if(head == NULL) {
		printf("EMPTY LIST\n");
		return;
	}
	NODE *temp = head;  //first node
	NODE *current = head;  //second node
	printf("What is the size of your reservation you wish to remove?\n");
  scanf("%d", &size);
	while(temp != NULL) {
		if(temp->size <= size) {
			if(head == tail)
				head = NULL;
			else if(temp == head)
				head=head->next;
			else if (temp == tail){
				current->next = NULL;
				tail=temp;
			}
			else
				current->next = temp->next;
		free(temp);
		}
		current = temp;
		temp = temp->next;
	}
}

void print() {
	NODE *temp = head;
	while(temp !=NULL) {
		printf("\n%s | %d\n", temp->name, temp->size);
		temp = temp->next;
		}
}

void search_size() {
	NODE *p=head;
	int check_size;
	printf("What is the size you wish to check?\n");
	scanf("%d", &check_size);
	while(p != NULL){
		if (p->size <= check_size)
			printf("Reservation of %s with a size of %d.\n", p->name, p->size);
		p = p->next;  //increment the the location p points to
	}
}

int check_duplicate(char *names) {
	NODE *p = head;
	while(p != NULL) {
		if(!strcmp(p->name, names))
			return 1;
		p=p->next;
	}
	return 0;  //returns 0 if there is no name in the list already that matches
}
