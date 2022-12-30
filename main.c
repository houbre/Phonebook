#include <stdio.h>
#include <string.h>
#include "PHONE_RECORD.h"

struct PHONE_RECORD phonebook[10];

//Here are the promises for every functions
void initialize_phonebook();
int loadCSV(FILE *CSV);
int saveCSV(FILE *CSV);
int addRecord(char name[], char birth[], char phone[]);
int findRecord(char name[]);
int listRecords();

//Takes as input: the menu option 1 2 3 or 4 (int)
//returns the same number
int menu(int user_input) {

	//initialize three char arrays to store the name, birthdate and phone
	char name[50], birth[12], phone[15], garbage[300];

	int errorcode;

	int check;

	//Initialize a pointer to a CSV file 
	FILE *CSV;

	//Takes in the menu option
	switch(user_input){

	//if the user input is 1, we will add a record to the phone book	
	case 1:

		//if the last slot in the phonebook is used, then te phonebook is full
		//we cannot add any records anymore
		if(phonebook[9].name[0] != 0){

			printf("Sorry the phonebook is full\n");
			break; //break so that the user can input another number
		}

		//open the CSV file
                CSV = fopen("phonebook.csv", "r");

                //if the pointer is NULL, the file doesn't exist
                if(CSV == NULL){
			CSV = fopen("phonebook.csv", "at");
                	fclose(CSV);
                }

		printf("Name: ");

		//get the name from stdin
		fgets(name, 50, stdin);
			
		//int to store the last possible index
		check = name[48];

		//if the array is full and the last index 
		if(strlen(name) == 49 && check != 10){
			//store the garbage
			fgets(garbage, 300, stdin);
		}

		//delete the newline char from the array name
		check = name[strlen(name)-1];
		if(check == 10){
			name[strlen(name) -1] = 0;
		}

      		printf("Birth: ");

		//get the birthdate from stdin
		fgets(birth, 12, stdin);

		check = birth[10];

		if(strlen(birth) == 11 && check != 10){
			fgets(garbage, 300, stdin);
		}
		
		//delete the newline char from the array birth
		check  = birth[strlen(birth)-1];
		if(check == 10){
			birth[strlen(birth) -1] = 0;
		}

		printf("Phone: ");

		//get the phone number from stdin
		fgets(phone, 15, stdin);

		check = phone[13];

		if(strlen(phone) == 14 && check != 10){
			fgets(garbage, 300, stdin);
		}

		//delete the newline char from stdin
		check = phone[strlen(phone)-1];
		if(check == 10){
			phone[strlen(phone)-1] = 0;
		}

		//call the function "addRecord" to add a record to the phonebook
		addRecord(name, birth, phone);

		break;
	
	//if the user input is 2, we will find a record in the phonebook	
	case 2:
		
		//open the CSV file
	        CSV = fopen("phonebook.csv", "r");

       		//if the pointer is NULL, the file doesn't exist
       		if(CSV == NULL){

			printf("phonebook.csv does not exist\n");
                	break; //file does not exits
        	}

		//if the first record's name[0] is equal to zero, then there are no records and the CSV file does not exist
	        if(phonebook[0].name[0] == 0){

        	        printf("Phonebook.csv exists but is empty\n");
                	break; //no one in the phonebook;
       		}

		printf("Find name: ");

		//get the name the user is looking for from stdin
		fgets(name, 50, stdin);

		//delete the newline char
		name[strlen(name)-1] = 0;

		//call "findRecord" to try and find the name the user is looking for
		findRecord(name);

		break;

	//if the user input is 3, we will list all records in the phonebook	
	case 3:
      		
		//open the CSV file
                CSV = fopen("phonebook.csv", "r");

                //if the pointer is NULL, the file doesn't exist
                if(CSV == NULL){

		printf("phonebook.csv does not exist\n");
                break; //file does not exits
                }
		fclose(CSV);

		//call "list record" to list all the records present in the phonebook
		listRecords();	

		break;

	//if the user input is 4, we will save all the phonebook records into a CSV file and exit the program	
	case 4: 
		
		//call "saveCSV" to save all the phonebook records into the CSV file
		saveCSV(CSV);
		

		break;

	}
		
	return 0;

}// to display the prompt and return the input

//Takes as input: an array of char containing the user input
//returns 0 if the input is valid 1 otherwise
int check_valid_input(char tmp[]){

	//if the length of the string is greater than 1
	//not a valid input
	if(strlen(tmp) > 1){
		printf("Choose a valid option\n");
                printf("Phonebook Menu: (1)Add, (2)Find, (3)List, (4)Quit>");

                return 1;
        }

	//If the string is of length 1, check if it is equal to 1 2 3 or 4
	//if not, not a valid input
	if((tmp[0] != '1') && (tmp[0] != '2') && (tmp[0] != '3') && (tmp[0] != '4')){

		printf("Choose a valid option\n");
                printf("Phonebook Menu: (1)Add, (2)Find, (3)List, (4)Quit>");

		return 1;; //wrong input;
	}
	
	//valid input
	return 0;
}


int main() {

	//Call "initialize_phonebook" to set the first char in name to '0'
	//it will be useful later
	initialize_phonebook();

	int err;

	FILE *CSV;

	char garbage;

	int user_input;

	char tmp[100];

	//first, call "loadCSV" to load everyline in the CSV file as a phonebook record
	loadCSV(CSV);

	printf("Phonebook Menu: (1)Add, (2)Find, (3)List, (4)Quit>");	

	//get the user input
	fgets(tmp, 50, stdin);

	//delete the newline char
	tmp[strlen(tmp)-1] = 0;

	//call "check_valid_input" to see if the user input is either 1 2 3 or 4
	err = check_valid_input(tmp);
	
	//while the input is not valid; keep asking for a valid input
	while(err == 1){

		fgets(tmp, 100,  stdin);
		tmp[strlen(tmp)-1] = 0;
		err = check_valid_input(tmp);
	}

	//the input is fine, call menu();
	sscanf(tmp, "%d", &user_input);

	menu(user_input);

	//loop until the user input is 4;
	while (user_input != 4){

		printf("Phonebook Menu: (1)Add, (2)Find, (3)List, (4)Quit>");
                
                fgets(tmp, 100, stdin);

		tmp[strlen(tmp)-1] = 0;

        	err = check_valid_input(tmp);

        	while(err == 1){

                	fgets(tmp, 100, stdin);
			tmp[strlen(tmp)-1] = 0;
                	err = check_valid_input(tmp);
        	}

        	sscanf(tmp, "%d", &user_input);
        	
		menu(user_input);
	}

	//the program has ended
	puts("End of phonebook program");

	return 0;


} // loops until 4 selected, call mini5phone.c functions
//done:)
