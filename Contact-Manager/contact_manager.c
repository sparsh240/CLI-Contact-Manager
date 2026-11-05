#include <stdio.h>
#include <stdbool.h>

typedef struct{
    char name[216];
    char number[15]; 
    char email[216];
}Contact;

typedef enum{
    DISPLAY = 1 , SEARCH = 2 , ADD = 3 ,EDIT = 4 , DELETE = 5 , EXIT = 6
}Choice;


void addContact(Contact *contacts); // adds new contact to storage.
void displayContacts(); // displays all contacts in formatted order
void searchContact(Contact *contacts); // searches by name
void editContact(Contact *contacts); // can edit one or more properties
void deleteContact(Contact *contacts); //number and name incase 2 contacts have same name

// Goals - make following functions work , eliminate duplication of contact numbers

        // Pointers	Passing contact structures to functions
        // Structures	Representing contacts
        // Dynamic allocation	Allocating contact records
        // realloc()	Expanding the contact list
        // File I/O	Saving/loading contacts


        
void managerApp();


int main(){

    managerApp();

    return 0;
}



void managerApp(){

    printf("______________________________\n\n");
    printf("  Welcome To Contact Manager  \n");
    printf("______________________________\n");

    bool managerActive = true;
    Choice choice = 0; 

    Contact *contacts = NULL; // this pointer will be passed on to functions to operate on it 


    do{
        printf("[1]* Display Contacts\n");
        printf("[2]* Search Contact\n");
        printf("[3]* Add Contact\n");
        printf("[4]* Edit Contact\n");
        printf("[5]* Delete Contact\n");
        printf("[6]* Exit\n\n");
        printf("== What would you like to do? [1/2/3/4/5/6] == : ");
        scanf("%u",&choice);
        getchar(); // eliminating the \n in input buffer

        switch(choice){
            case DISPLAY:

                displayContacts();
                break;

            // case SEARCH:

            //     searchContact(contacts);
            //     break;
            
            case ADD:

                addContact(contacts);
                break;

            // case EDIT:

            //     editContact(contacts);
            //     break;

            // case DELETE:

            //     deleteContact(contacts);
            //     break;

            case EXIT:

                managerActive = false;
                break;

            default:
                printf("\n***Invalid Choice! Retry***\n\n");

        }

    }while(managerActive);

}

void displayContacts(){

    FILE *pFile = fopen("Contact-Manager/contacts.txt" , "r");

    char buffer[1024] = "";
    const int countryCode = 91; // can be modified from here

    bool hasContacts = (fgets(buffer , sizeof(buffer) , pFile) != NULL );

    if(!hasContacts){
        printf("\n** No Contacts Saved **\n\n");
    }else{
        printf("---------------------------------------------\n\n");
        printf("%s\n" , buffer);
    

        while(fgets(buffer , sizeof(buffer) , pFile) != NULL){
            printf("---------------------------------------------\n\n");
            printf("%s\n" , buffer);
        
        }
        printf("---------------------------------------------\n");
        printf("\n***END***\n\n");
    }



}