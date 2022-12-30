#include <stdio.h>
#include <string.h>
#include "PHONE_RECORD.h"

//Takes as input: a CSV file pointer
//load the phonebook with the info in the CSV
int loadCSV(FILE *CSV) {

	//open the CSV file
	CSV = fopen("phonebook.csv", "r");

	//if the pointer is NULL, the file doesn't exist
	if(CSV == NULL){

		return 1; //file does not exits
	
	}

	int person = -1;

	char line[100];

	//for every line in the CSV file
	while(fgets(line, sizeof(line), CSV)){

		char *token;

		//each token represent either the name, birthdate or phone number
		token = strtok(line, ",");

		//for each token
		for(int i = 0; i < 3; i++){
			
			//if its the header line, skip
			if(strcmp(token, "Name") == 0){
				break;
			}	
			//name
			else if(i==0){
				//set the name
				strcpy(phonebook[person].name, token);
			}
			//birthdate
			else if(i==1){
				//set the birthdate
                                strcpy(phonebook[person].birthdate, token);
                        } 
			//phone number
			else if(i==2){
				//set the phone number
                                strcpy(phonebook[person].phone, token);
				phonebook[person].phone[strlen(token)-1] = 0;
                        }
			token = strtok(NULL, ",");
		}
		//go to the next person in the phonebook
		person++;
	}


	fclose(CSV);

	return 0;

}// return errorcode, otherwise load data structure

//Takes as input a CSV file pointer
//when the user exit the program, save phonebook into the CSV file
int saveCSV(FILE *CSV) {

	int person = 0;

	int i = 0;

	//If the phonebook is empty, create a new CSV file
	if(phonebook[person].name[0] == 0){
		CSV = fopen("phonebook.csv", "at");
		fclose(CSV);
	}

	//open the CSV file with w+ to overwrite
	CSV = fopen("phonebook.csv", "w+");

	//insert the header
	fprintf(CSV, "Name,birthdate,phone\n");

	//for each record in the phonebook
	for(person; person < 10; person++){

		//Earlier we initialized the first index of every "name" to zero.
		//if we encounter a zero, there are no more record in the phonebook
		if(phonebook[person].name[0] == 0){
			break;
		}

		//add to the CSV file the name, birthdate and phone number of that record
		fprintf(CSV, "%s,%s,%s\n", phonebook[person].name, phonebook[person].birthdate, phonebook[person].phone);

	}

        fclose(CSV);

        return 0;

} // return errorcode, otherwise save data structure

//Takes as input: the name, birthdate and phone number entered by the user
//add those into the phonebook
int addRecord(char curr_name[], char curr_birth[], char curr_phone[]) {

	int j = 0;
	int size = 0;

	//check in which slot of the phonebook we want to add the record
	for(j; j<10; j++){
		

		struct PHONE_RECORD person = phonebook[j];

		//as soon as we find a 0 at the first index of "name"
		//phonebook index is available
		if(person.name[0] == 0){
			break;
		}	
		//else check for next slot in the phonebook
		else{
			size++;
		}
	}
	
	//we found our slot 
	//set the name, birthdate and phone number
	strcpy(phonebook[size].name, curr_name);

	strcpy(phonebook[size].birthdate, curr_birth);

	strcpy(phonebook[size].phone, curr_phone);

	return 0;

} // return errorcode, otherwise add a new phone entry

//Takes as input: the name the user is searching for
int findRecord(char curr_name[]) {

	int person;

	int boarders = 18;

        int len;

        int remaining;

	int result;

	//for each record in the phonebook
	for(person = 0; person < 10; person++){
		
		//as soon as we encounter a zero as the first index of their name
		//we went through all of the records and didn't find a name
		if(phonebook[person].name[0] == 0) {
			
			printf("Does not exist\n");	
			
			break;
		}

		//compare the name the user is searching for with the name of the record we are currently looking at
		//if it matches, print the information, and break out of the loop
		if(strcmp(phonebook[person].name, curr_name) == 0){

			printf("----NAME--------- ------BIRTH------ -----PHONE-------\n"); 

			len = strlen(phonebook[person].name);

        		remaining = (boarders - len);

        		printf("%s", phonebook[person].name);

		        printf("%*c", remaining, ' ');

        		len = strlen(phonebook[person].birthdate);

        		remaining = (boarders - len);

        		printf("%s", phonebook[person].birthdate);

        		printf("%*c", remaining, ' ');

        		printf("%s\n", phonebook[person].phone);

			break;
		}
	}

	return 0; //everything ok

} // return errorcode, otherwise return index of found

//prints every records in the phonebook
int listRecords() {

	//if there are no records, the CSV file does not exist
	if(phonebook[0].name[0] == 0){
		
		printf("Phonebook.csv exist but is empty\n");
		
		return 1;
	}

	//print the header
	printf("----NAME--------- ------BIRTH------ -----PHONE-------\n");      

	int boarders = 18;
        
        int len;

        int remaining;

        char line[100];

	int person;

	int i;

	//for each record in the phonebook
	for(person = 0; person < 10; person++){

		//if the first index of the record's name contains a 0
		//then we went through all the records in the phonebook
		if(phonebook[person].name[0] == 0){
			break;
		}

		//for the name, birthdate and phone number
		for(i = 0; i<3; i++){
			//name
			if(i == 0){
				//if the name is greater than 17, truncate for aesthetics
				if(strlen(phonebook[person].name) >= boarders){
					printf("%.*s", 17, phonebook[person].name);
					printf("%c", ' ');
				}
				//print the name
				else{
					printf("%s", phonebook[person].name);
					len = strlen(phonebook[person].name);
					remaining = boarders - len;
					printf("%*c", remaining, ' ');
				}
			//print the birthdate	
			}else if(i == 1){
				printf("%s", phonebook[person].birthdate);
                                len = strlen(phonebook[person].birthdate);
                                remaining = boarders - len;
                                printf("%*c", remaining, ' ');
			//print the phone number	
			}else{
				printf("%s\n", phonebook[person].phone);
			}
		}
	}

 	return 0;

} // return errorcode, otherwise displays pretty all

//Void function that sets every first first index of "name" with the value zero;
//for every slot in the phonebook
void initialize_phonebook(){
	
	int i = 0;
	
	for(i; i < 10; i++)
		phonebook[i].name[0] = 0;

}
