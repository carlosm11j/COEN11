#include <stdio.h>
#define SIZE 10

int counter = 0, check_duplicate(char*);
void insert(void), delete(void), print(void), search_size(void);
struct reservation_structure {
  char name[SIZE];
  int size;
};
struct reservation_structure reservation[10];

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

//Insert into array
void insert() {
	if(counter < SIZE) {
		char name[SIZE];
 	 	int size;
 	 	//Enter in Name
 	 	printf("\nEnter in Name: ");
	 	scanf("%s", &name);
    if(check_duplicate(name) == 1) {
      strcpy(reservation[counter].name, name);
      //Enter in Size
   	 	printf("\nEnter in Size: ");
   	 	scanf("%d", &size);
   	 	reservation[counter].size = size;
   	 	//Add to Counter
   	 	counter++;
    }
    else {
      printf("'%s' has already been entered...please try again\n", &name);
      insert();
    }
	}
	else
		printf("\n***FULL LIST***\n");
}

//Delete from array
void delete() {
	if(counter > 0) {
		int size;
		printf("\nEnter in Size: ");
		scanf("%d", &size);
		//Runs through array to find same size
		for(int i = 0; i < counter; i++) {
			if(reservation[i].size == size) {
				for(int j = i; j < counter-1; j++) {
					//Shifts elements up in the array
          			strcpy(reservation[j].name, reservation[j+1].name);
         	 		reservation[j].size = reservation[j+1].size;
				}
				break;
			}
		}
		counter--;
	}
	else
		printf("\n***EMPTY LIST***\n");
}

//Prints List
void print() {
 	//Runs through array
	for (int i = 0; i < counter; i++) {
		printf("\n");
		printf("%s ", reservation[i].name);
   		printf("| %d", reservation[i].size);
		printf("\n");
 	 }
}

void search_size() {
  if(counter > 0) {
    int size;
    printf("\nEnter in Size: ");
    scanf("%d", &size);
    for(int i = 0; i < counter; i++) {
      if(reservation[i].size <= size) {
        printf("\n");
    		printf("%s ", reservation[i].name);
       	printf("| %d", reservation[i].size);
    		printf("\n");
      }
    }
  }
  else
		printf("\n***EMPTY LIST***\n");
}

int check_duplicate(char* name) {
  //Runs through Array
  for(int i = 0; i < counter; i++) {
    if (!strcmp(reservation[i].name, name))
      return 0;
  }
  return 1;
}

