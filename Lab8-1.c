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

void insert_list(), delete(), read_file(FILE*), delete(NODE*, NODE*, int), write_to_file(FILE*), print(), show_blist(NODE*), show_bnames(NODE*, char*);
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
    printf("\n1]Add Reservation \n2]Remove \n3]Print \n4]Print List Backwards \n5]Print Names Backwards \n0]Exit\n");
		printf("\nEnter in choice: ");
		scanf("%d", &choice);
    switch(choice) {
      case 1: insert_list(infp);
        break;
      case 2: delete(head, head->next, 0);
        break;
			case 3: print();
				break;
			case 4: show_blist(head);
				break;
			case 5: show_bnames(head, head->name);
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
	printf("READ\n");
  fseek(infp, sizeof("Name\tSize\n------------"), SEEK_END);
  while (fscanf(infp, "%s\t%d", name, &size) == 2) {
		printf("READLOO\n");
		printf("%s\n", name);
		fscanf(infp,"%s\t%d", temp->name, temp->size);
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

//Show List Backwards
void show_blist(NODE *temp) {
	if(temp == NULL)
		return;
  show_blist(temp->next);
  printf("\n%s | %d\n", temp->name, temp->size);
}

//Show Names Backwards
void show_bnames(NODE *temp, char *spot) {
	if(temp == NULL)
		return;
	if(*spot != '\0') {
		show_bnames(temp, spot+1);
		printf("%c", *spot);
	}
	else {
		printf("\n");
		show_bnames(temp->next, temp->next->name);
		printf("\n");
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
void delete(NODE *p, NODE *q, int flag) {
	int size;
	if(flag == 0) {
		printf("\nEnter in size: ");
  	scanf("%d", &size);
		flag++;
	}
	//If list is empty
  if(p == NULL)
		return;
  else if(p->size == size && p == head) {
		head = head->next;
		free(p);
	}
	else {
		if(p->size == size) {
			q->next = p->next;
			free(p);
			return;
		}
		else
			delete(p->next, p, 1);
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
