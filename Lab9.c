#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct node{
	char name[20];
	int size;
  struct node *next;
}NODE;

NODE *head = NULL;
NODE *tail = NULL;

pthread_t thread;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void insert_list(), delete(), read_file(FILE*), delete(NODE*, NODE*, int), write_to_file(FILE*),
print(), show_blist(NODE*), show_bnames(NODE*, char*), *auto_save(void*), print_binfile(char*);
int check_file(char*);

//Main - Displays menu
int main(int argc, char *argv[]) {
  //Arugment Setup
  if(argc < 3)
    return 0;
  char* file = argv[1];
  char* bfile = argv[2];
  FILE *infp;
  infp = fopen(file, "w+");
  if(infp == NULL)
    return 0;
	read_file(infp);
	pthread_create(&thread, NULL, auto_save, (void *) bfile);
  //Menu
  int choice = 1;
	while(choice != 0) {
    printf("\n1]Add Reservation \n2]Remove \n3]Print \n4]Print List Backwards \n5]Print Names Backwards \n6]Print Binary File \n0]Exit\n");
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
      case 6: print_binfile(bfile);
        break;
      default: choice = 0;
				write_to_file(infp);
        fclose(infp);
        break;
				pthread_exit(&thread);
    	}
  }
}

//Read FILE
void read_file(FILE *infp) {
	NODE *temp;
	char name[20];
	int size;
  fseek(infp, sizeof("Name\tSize\n------------"), SEEK_END);
  while (fscanf(infp, "%s\t%d", name, &size) == 2) {
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

//Auto Save Binary File
void * auto_save(void *bfile) {
	FILE *binf;
	while(1) {
		binf = fopen(bfile, "wb");
		if(binf == NULL)
			printf("EMPTY\n");
		pthread_mutex_lock(&mutex);
		NODE *temp = head;
  	while(temp != NULL) {
    	fwrite(&temp, sizeof(struct node), 1, binf);
			temp = temp->next;
  	}
		pthread_mutex_unlock(&mutex);
		fclose(binf);
		sleep(15);
	}
}

//Print Binary File
void print_binfile(char* bfile) {
	FILE *binf;
	binf = fopen(bfile, "wb");
	pthread_mutex_lock(&mutex);
  unsigned char buffer[100];
  fread(buffer, sizeof(buffer), 1, binf);
  for(int i=0; i<100; i++)
    printf("%u ", buffer[i]);
	pthread_mutex_unlock(&mutex);
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
void delete(NODE *head, NODE *q, int flag) {
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
/*
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
}*/

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

