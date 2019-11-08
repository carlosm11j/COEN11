#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{
	char* name;
	int size;
	struct node *next;
}NODE; //[0]: 1-2, [1]: 3-4, [2]: 5-6, [3]: 6+

NODE *head[4];
NODE *tail[4];

void insert(), delete(), print(), search_size();
int check_list(int), check_duplicate(char*);

//Main - Displays menu
int main() {
  for(int i=0; i<4; i++) {
    head[i] = NULL;
    tail[i] = NULL;
  }
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

//Insert into Linked List
void insert() {
  char* name;
  int size;
  NODE *temp;
  //Enter in Name
  printf("\nEnter in Name: ");
  scanf("%s", &name);
  //Enter in Size
  printf("\nEnter in Size: ");
  scanf("%d", &size);
  int list = check_list(size);
	temp = (NODE*)malloc(sizeof(NODE));
	temp->size = size;
	strcpy(temp->name, name);
	temp->next=NULL;
	tail[list]->next = temp;
	tail[list] = temp;
	return;
	/*
	//If linked list is empty...
	if(head[list] == NULL) {
		temp = (NODE*)malloc(sizeof(NODE));
    temp->size = size;
    strcpy(temp->name, name);
    head[list] = temp;
    temp->next = NULL;
    tail[list] = temp;
    return;
  }
  else if(check_duplicate(name) == 0) {
		temp = (NODE*)malloc(sizeof(NODE));
    temp->size = size;
    strcpy(temp->name, name);
    temp->next=NULL;
    tail[list]->next = temp;
    tail[list] = temp;
    return;
  }
  else {
    printf("'%s' has already been entered...please try again\n", &name);
    insert();
  }
	return;*/
}

//Checks which list to enter into
int check_list(int size) {
  if(size <= 2)
    return 0;
  else if(size >= 3 && size <= 4)
    return 1;
  else if(size >=5 && size <=6)
    return 2;
  else
    return 3;
}

//Delete from Linked List
void delete() {
	NODE *temp, *p;
  int size;
	printf("\nEnter in size: ");
  scanf("%d", &size);
  int list = check_list(size);
  temp = p = head[list];
  if(head[list] == NULL) {
		printf("\n***EMPTY LIST***\n");
		return;
	}
	while(temp != NULL) {
		if(temp->size == size) {
			if(head[list] == tail[list]) {
				head[list] = NULL;
				free(temp);
			}
			else if(temp == head[list]) {
				head[list] = head[list]->next;
				free(temp);
			}
			else if(temp == tail[list]) {
				p->next = NULL;
				tail[list] = temp;
				free(temp);
			}
			else {
				p->next = temp->next;
				free(temp);
			}
			return;
		}
		p = temp;
		temp = temp->next;
	}
}

//Print Linked List
void print() {
  for(int i=0; i<4; i++) {
    NODE *p = head[i];
  	while(p != NULL) {
  		printf("\n%s | %d\n", p->name, p->size);
  		p = p->next;
  	}
    printf("\n");
  }
  return;
}

//Checks duplicates of names
int check_duplicate(char *name){
  for(int i=0; i<4; i++) {
    NODE *p = head[i];
    while(p != NULL) {
  		if(!strcmp(p->name, name))
  			return 1;
  		p=p->next;
  	}
  }
  return 0;
}

//Prints nodes from linked list that are less than given
void search_size() {
  int size;
	printf("\nEnter in size: ");
  scanf("%d", &size);
  int list = check_list(size);
  for(int i=0; i<=list; i++) {
    NODE *p = head[i];
    while(p != NULL){
  		printf("\n%s | %d.\n", p->name, p->size);
  		p=p->next;
  	}
  }
}
