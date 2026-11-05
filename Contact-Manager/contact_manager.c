#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
    char name[216];
    char number[15]; 
    char email[216];
}Contact;

typedef enum{
    DISPLAY = 1 , SEARCH = 2 , ADD = 3 ,EDIT = 4 , DELETE = 5 , EXIT = 6
}Choice;

void extractContacts(Contact *contacts ,int *pSize); // gets contacts stored in contacts.txt and stores them into array.
void pushContacts(Contact *contacts ,int *pSize); // takes the contacts stored in the array and adds them to contacts.txt

void addContact(Contact *contacts , int *pSize); // adds new contact to storage.
void displayContacts(); // displays all contacts in formatted order
void searchContact(Contact *contacts , int *pSize); // searches by name
void editContact(Contact *contacts , int *pSize); // can edit one or more properties 
void deleteContact(Contact *contacts , int *pSize); //number and name incase 2 contacts have same name

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
    int size = 0; // Since contacts is a pointer and not an array , we have to keep a track of the size (passing pointer to size wherever needed)
    


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

                extractContacts(contacts , &size);
                displayContacts(contacts , &size);
                break;

            case SEARCH:

                extractContacts(contacts , &size);
                searchContact(contacts , &size);
                break;

            case ADD:
                addContact(contacts , &size);
                break;

            case EDIT:

                extractContacts(contacts , &size);
                editContact(contacts , &size);
                break;

            case DELETE:

                extractContacts(contacts , &size);
                deleteContact(contacts , &size);
                break;

            case EXIT:

                managerActive = false;
                break;

            default:
                printf("\n***Invalid Choice! Retry***\n\n");

        }

    }while(managerActive);


    // freeing memory
    if(contacts != NULL){
        free(contacts);
        contacts = NULL;
    }

}




void editContact(Contact *contacts , int *pSize){

    const int SIZE = *pSize;

    if(SIZE == 0){
        printf("\nNo Contacts Found.\n");
        return;
    }

    char name[216] = "";
    char number[15] = "";

    printf("Enter Contact Name To Edit : ");
    scanf("%s" , name);
    getchar();
    printf("Enter Contact Number To Edit : ");
    scanf("%s" , number);
    getchar();

    

    for(int i = 0 ; i < SIZE ; i++){

        if(contacts[i].name == name && contacts[i].number == number ){
            int choice = 0;
            printf("\n***What would you like to edit ?***\n");
            printf("*[1] Name\n*[2] Number\n*[3] Email\n")
            printf("Select one of the choices : ");
            scanf("%d" , choice);
            getchar(); 

            switch(choice){
                case 1 : 
                    
                    printf("Enter new name : ");
                    scanf("%s" , contacts[i].name);
                    
                case 2 : 
                    
                    printf("Enter new number : ");
                    scanf("%s" , contacts[i].number);
                    
                case 3 : 
                    
                    printf("Enter new email : ");
                    scanf("%s" , contacts[i].email);
                
                default :
                    printf("Invalid Choice.");
                    
            }

            // contacts in the array updated

            pushContacts(contacts , pSize); // saving
            return;
        }


    }




}


void deleteContact(Contact *contacts , int *pSize){

    const int SIZE = *pSize;

    if(SIZE == 0){
        printf("\nNo Contacts Found.\n");
        return;
    }

    char name[216] = "";
    char number[15] = "";

    printf("Enter Contact Name To Delete : ");
    scanf("%s" , name);
    getchar();
    printf("Enter Contact Number To Delete : ");
    scanf("%s" , number);
    getchar();

    
    

    int i = 0;

    while( i < SIZE){

        if(contacts[i].name == name && contacts[i].number == number ){

            printf("\n**Contact Found**\n\n");

            // moving all next contacts one step back
            while(i < (SIZE - 1) ){

                strcpy(contacts[i].name , contacts[i+1].name);
                strcpy(contacts[i].number , contacts[i+1].number);
                strcpy(contacts[i].email , contacts[i+1].email);

                i++;
            }

            // reallocating to a smaller size (removing last element after shifts)
            Contact *temp = realloc(contacts , SIZE-1 * sizeof(contacts[0]));
            contacts = temp;
            temp = NULL;

            (*pSize)--; // updating size 

            pushContacts(contacts , pSize);
            printf("\n*** Contact Deleted ***\n\n"); 


            return;
        }

        i++;

    }

    printf("Contact Not Found.\n");

    
}

void searchContact(Contact *contacts , int *pSize){

    const int SIZE = *pSize;

    if(SIZE == 0){
        printf("\nNo Contacts Found.\n");
        return;
    }

    char name[216] = "";
    printf("Search Contact Name : ");
    scanf("%s" , name);
    getchar();

    

    for (int i = 0 ; i < SIZE; i++){
        if(contacts[i].name == name){
            printf("\n=== FOUND CONTACT ===\n\n");

            printf("---------------------------------------------------\n\n");
            printf("Name : %s\nNumber : %s\nEmail : %s\n\n" , contacts[i].name , contacts[i].number , contacts[i].email);

        }
    }

    printf("---------------------------------------------------\n\n");
    printf("\n\n***END***\n\n");



}



void addContact(Contact *contacts , int *pSize){

    char name[216] = "";
    char number[15] = "";
    char email[216] = "";

    printf("Enter the Name : \n");
    scanf("%s" , name);
    getchar();
    printf("Enter the Number : \n");
    scanf("%s" , number);
    getchar();
    printf("Enter the Email : \n");
    scanf("%s" , email);
    getchar();

    int newPos = *pSize;

    Contact *temp = realloc(contacts , (newPos+1 * sizeof(contacts[0])));

    if(temp == NULL){
        printf("Could Not Add Contact , Reallocation Failed.\n");
    }else{
        contacts = temp;
        temp = NULL;

        strcpy(contacts[newPos].name , name);
        strcpy(contacts[newPos].number , number);
        strcpy(contacts[newPos].email , email);

        (*pSize)++; //Updating size of the array

        // Pushing the updates to the text file.
        pushContacts(contacts , pSize);
    }

    

}


void displayContacts(Contact *contacts , int *pSize){

    const int SIZE = *pSize;

    if(SIZE == 0){
        printf("\nNo Contacts Found.\n");
        return;
    }

    else{

        for(int i= 0; i < SIZE; i++ ){

            printf("---------------------------------------------------\n\n");
            printf("Name : %s\nNumber : %s\nEmail : %s\n\n" , contacts[i].name , contacts[i].number , contacts[i].email);

        }

        printf("---------------------------------------------------\n\n");
        printf("\n\n***END***\n\n");
    }

}