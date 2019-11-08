#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{
	char name[20];
	int size;
  struct node *next;
}NODE;

NODE *head = NULL;
NODE *tail = NULL;

void insert_list(), delete(), read_file(FILE*), delete(), write_to_file(FILE*), print();
int check_file(char*);

//Main - Displays menu
int main(int argc, char *argv[]) {
  //Arugment Setup
  if(argc == 1)
    return 0;
  char* file = argv[1];
  FILE *infp;
  infp = fopen(file, "w+");
  if(infp == NULL)
    return 0;
  read_file(infp);
  //Menu
  int choice = 1;
	while(choice != 0) {
    	printf("\n1]Add Reservation \n2]Remove \n3]Print \n0]Exit\n");
		printf("\nEnter in choice: ");
		scanf("%d", &choice);
    	switch(choice) {
      		case 1: insert_list(infp);
        	break;
      	case 2: delete();
        	break;
		case 3: print();
			break;
    	default: choice = 0;
			write_to_file(infp);
        	fclose(infp);
        	break;
    	}
  	}
}

//Read FILE
void read_file(FILE *infp) {
	NODE *temp;
	char name[20];
	int size;
  	fseek(infp, sizeof("Name\tSize\n------------\n"), SEEK_END);
  	while(fscanf(infp, "%s\t%d\n", name, &size) == 2) {
		fscanf(infp, "%s\t%d", temp->name, temp->size);
		temp = (NODE*)malloc(sizeof(NODE));
		temp->size = size;
		strcpy(temp->name,name);
		head = temp;
		temp->next = NULL;
		tail=temp;
	}
}

//Write to File
void write_to_file(FILE *infp) {
	fprintf(infp, "Name\tSize\n------------\n");
	NODE *temp = head;
  	while(temp != NULL) {
    	fprintf(infp, "%s\t%d\n", temp->name, temp->size);
    	temp = temp->next;
  	}
}

//Print
void print() {
	NODE *temp = head;
	while(temp != NULL) {
		printf("\n%s | %d\n", temp->name, temp->size);
		temp = temp->next;
	}
  return;
}

//Insert into Linked List
void insert_list() {
  //Enter in Name
  char name[20];
  printf("\nEnter in Name: ");
  scanf("%s", &name);
  //Enter in Size
  int size;
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
		return;
	}
  else if(check_duplicate(name) == 0) {
		temp = (NODE*)malloc(sizeof(NODE));
		temp->size = size;
		strcpy(temp->name, name);
		temp->next=NULL;
		tail->next = temp;
		tail = temp;
		return;
  }
  else {
    printf("'%s' has already been entered...please try again\n", &name);
    insert_list();
  }
}

//Delete from File
void delete() {
  	int size;
	printf("\nEnter in size: ");
  	scanf("%d", &size);
  	NODE *temp = head;
	NODE *p = head;
	while(temp != NULL) {
		if(temp->size == size) {
			if (head == tail) {
				head = NULL;
				free(temp);
			}
			else if(temp == head) {
				head=head->next;
				free(temp);
			}
			else if (temp == tail) {
				p->next = NULL;
				tail=temp;
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
	return;
}

//Check for Duplicates
int check_duplicate(char *name) {
	NODE *p = head;
	while(p != NULL) {
		if(!strcmp(p->name, name))
			return 1;
		p=p->next;
	}
	return 0;
}

