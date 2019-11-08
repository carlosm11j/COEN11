#include <stdio.h>
#define SIZE 10

int counter = 0, check_duplicate(char*);
void insert(void), delete(void), print(void), search_size(void);
struct reservation_structure {
  char name[SIZE];
  int size;
  int special_occasion;
  char name_of_occasion[20];
  char info[10];
  union {
    char special_name[SIZE];
    int special_years;
    float special_average_age;
  } extra_info;
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
      //Prompt special_occasion
      int choice;
      printf("\n1]Birthday \n2]Anniversary \n0]No Special Occasion\n");
      printf("\nEnter in choice: ");
  		scanf("%d", &choice);
      reservation[counter].special_occasion = choice;
      if(choice == 1) {
          strcpy(reservation[counter].name_of_occasion, "BIRTHDAY");
          char birthday_name[SIZE];
          printf("\nEnter in name of Birthday person: ");
          scanf("%s", &birthday_name);
		  strcpy(reservation[counter].info, birthday_name);
          strcpy(reservation[counter].extra_info.special_name, birthday_name);
      }
      else if(choice == 2) {
          strcpy(reservation[counter].name_of_occasion, "ANNIVERSARY");
          int years;
          printf("\nEnter in years of anniversary: ");
          scanf("%d", &years);
		  char str1[10];
		  sprintf(str1, "%d", years);
		  strcpy(reservation[counter].info, str1);
          reservation[counter].extra_info.special_years = years;
      }
      else {
          strcpy(reservation[counter].name_of_occasion, "NO SPECIAL OCCASION");
          float average_age;
          printf("\nEnter in average age of group: ");
          scanf("%f", &average_age);
		  //Convert to string to put into variable
		   char str[10];
		  sprintf(str, "%f", average_age);
		  strcpy(reservation[counter].info, str);
          reservation[counter].extra_info.special_average_age = average_age;
      }
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
          			strcpy(reservation[j].info, reservation[j+1].info);
          			strcpy(reservation[j].name_of_occasion, reservation[j+1].name_of_occasion);
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
   		printf("| %d | ", reservation[i].size);
    	printf("%s | %s ", reservation[i].name_of_occasion, reservation[i].info);
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
       	printf("| %d | ", reservation[i].size);
        if(reservation[i].special_occasion == 1)
          printf("%s | %s", reservation[i].name_of_occasion, reservation[i].extra_info.special_name);
        else if(reservation[i].special_occasion == 2)
          printf("%s | %d", reservation[i].name_of_occasion, reservation[i].extra_info.special_years);
        else
          printf("%s | %f", reservation[i].name_of_occasion, reservation[i].extra_info.special_average_age);
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

