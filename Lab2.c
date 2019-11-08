#include <stdio.h>
#define SIZE 10
#define LENGTH 20

int size_of_reservation[SIZE], counter = 0;
char name_of_reservation[SIZE][LENGTH];
void insert(void), delete(void), print(void);

//Main - Displays menu
int main() {
    int choice;
	while (choice != 0) {
    	printf("\n1]Add Reservation \n2]Remove \n3]Print \n0]Exit\n");
		printf("\nEnter in choice: ");
		scanf("%d", &choice);
    	switch(choice) {
      		case 1: insert();
        		break;
      		case 2: delete();
        		break;
      		case 3: print();
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
 	 	strcpy(name_of_reservation[counter], name);
 	 	//Enter in Size
 	 	printf("\nEnter in Size: ");
 	 	scanf("%d", &size);
 	 	size_of_reservation[counter] = size;
 	 	//Add to Counter
 	 	counter++;
	}
	else
		printf("\n***FULL LIST***\n");
}

void delete() {
	if(counter > 0) {
		int size;
		printf("\nEnter in Size: ");
		scanf("%d", &size);
		//Runs through array to find same size
		for(int i = 0; i < counter; i++) {
			if(size_of_reservation[i] == size) {
				for(int j = i; j < counter-1; j++) {
					//Shifts elements up in the array
					strcpy(name_of_reservation[j], name_of_reservation[j+1]);
					size_of_reservation[j] = size_of_reservation[j+1];
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
		printf("%s ", name_of_reservation[i]);
   		printf("| %d", size_of_reservation[i]);
		printf("\n");
 	 }
}

