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

// Double pointers where we need to modify the pointer to the array (realloc , malloc); (POINTERS ARE PASS BY VALUE SO DOUBLE POINTERS NEEDED)

void extractContacts(Contact **contacts ,int *pSize); // gets contacts stored in contacts.txt and stores them into array.
void pushContacts(Contact *contacts ,int *pSize); // takes the contacts stored in the array and adds them to contacts.txt

void addContact(Contact **contacts , int *pSize); // adds new contact to storage.
void displayContacts(); // displays all contacts in formatted order
void searchContact(Contact *contacts , int *pSize); // searches by name
void editContact(Contact *contacts , int *pSize); // can edit one or more properties 
void deleteContact(Contact **contacts , int *pSize); //number and name incase 2 contacts have same name


        
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

                extractContacts(&contacts , &size);
                displayContacts(contacts , &size);
                break;

            case SEARCH:

                extractContacts(&contacts , &size);
                searchContact(contacts , &size);
                break;

            case ADD:
                extractContacts(&contacts , &size); 
                addContact(&contacts , &size);
                break;

            case EDIT:

                extractContacts(&contacts , &size);
                editContact(contacts , &size);
                break;

            case DELETE:

                extractContacts(&contacts , &size);
                deleteContact(&contacts , &size);
                break;

            case EXIT:

                managerActive = false;
                free(contacts);
                contacts = NULL;
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

void extractContacts(Contact **contacts ,int *pSize){


    FILE *pFile = fopen("Contact-Manager/contacts.txt" , "r");
    if(pFile == NULL){
        printf("Could Not open File");
        fclose(pFile);
        return;
    }

    if((*contacts) != NULL){ // freeing if not free
        free(*contacts);
        *contacts = NULL;
        *pSize = 0;
    }



    char buffer[500]; 



    *contacts = malloc(sizeof(Contact));
    if((*contacts) == NULL){
        printf("Allocation Initialization failed\n");
        return;
    }

    

    Contact *temp = NULL; // used for realloc
    int currentPoint = 0;

    if(fgets(buffer , sizeof(buffer) , pFile) == NULL){
        printf("Empty.\n");
        return;
    }

    do{


        
        // saving to array
        sscanf(buffer , "%216[^,],%15[^,],%216[^\n]" ,(*contacts)[currentPoint].name ,(*contacts)[currentPoint].number ,(*contacts)[currentPoint].email);
        printf("Checkpoint Extraction");
        
        

        currentPoint++; 

        
        // reallocating for next contact
        temp = realloc(*contacts , (currentPoint+1)*(sizeof(Contact)));
        if(temp == NULL){
            printf("Realloc Failed, Resetting Array.\n");
            *contacts = NULL;
            *pSize = 0;
            break;

        }

        

        
        *contacts = temp;
        temp = NULL;
    
    }while(fgets(buffer , sizeof(buffer) , pFile) != NULL);


    // reallocating to remove the extra memory added in last iteration
    temp = realloc(*contacts , (currentPoint)*sizeof(Contact));
    if(temp == NULL){
        printf("Realloc Failed , Extra memory allocated\n");
        return;
    }
    *contacts = temp;
    temp = NULL;

    // updating to new size
    *pSize = currentPoint;
    

    fclose(pFile);
}

void pushContacts(Contact *contacts ,int *pSize){


    const int SIZE = *pSize;
    FILE *pFile = fopen("Contact-Manager/contacts.txt","w");

    if(SIZE == 0){
        fclose(pFile);
        return;
    }

    

    for(int i = 0 ; i < SIZE; i++){
        fprintf(pFile , "%s,%s,%s\n" , contacts[i].name, contacts[i].number , contacts[i].email);
    }

    fclose(pFile);

}


void editContact(Contact *contacts , int *pSize){

    const int SIZE = *pSize;

    if(SIZE == 0 || contacts == NULL){
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

        if( !(strcmp(contacts[i].name , name)) && !(strcmp(contacts[i].number , number)) ){
            int choice = 0;
            printf("\n***What would you like to edit ?***\n");
            printf("*[1] Name\n*[2] Number\n*[3] Email\n");
            printf("Select one of the choices : ");
            scanf("%d" , &choice);
            getchar(); 

            switch(choice){
                case 1 : 
                    
                    printf("Enter new name : ");
                    scanf("%s" , contacts[i].name);
                    break;
                    
                case 2 : 
                    
                    printf("Enter new number : ");
                    scanf("%s" , contacts[i].number);
                    break;
                    
                case 3 : 
                    
                    printf("Enter new email : ");
                    scanf("%s" , contacts[i].email);
                    break;
                
                default :
                    printf("Invalid Choice.");
                    
            }

            // contacts in the array updated

            pushContacts(contacts , pSize); // saving
            return;
        }

    }

    printf("Contact not found\n");




}


void deleteContact(Contact **contacts , int *pSize){

    const int SIZE = *pSize;

    if(SIZE == 0 || *contacts == NULL){
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

        if( !(strcmp((*contacts)[i].name , name)) && !(strcmp((*contacts)[i].number , number)) ){ 

            printf("\n**Contact Found**\n\n");

            // moving all next contacts one step back
            while(i < (SIZE - 1) ){

                strcpy((*contacts)[i].name , (*contacts)[i+1].name);
                strcpy((*contacts)[i].number , (*contacts)[i+1].number);
                strcpy((*contacts)[i].email , (*contacts)[i+1].email);

                i++;
            }

            // reallocating to a smaller size (removing last element after shifts)
            // if only one contact left , then handling for it
            if(SIZE == 1){
                printf("Only 1 Contact , Can not Realloc to 0 , returns NULL\n");
                free(*contacts);
                *contacts = NULL;
                *pSize = 0;


            }else{
                Contact *temp = realloc(*contacts , (SIZE-1) * (sizeof(Contact)));
                if(temp == NULL){
                    printf("Realloc failed , Deletion successful but Last contact repeated\n");
                    return;
                }
                *contacts = temp;
                temp = NULL;

                (*pSize)--; // updating size 

            }

            
            pushContacts(*contacts , pSize);
            printf("\n*** Contact Deleted ***\n\n"); 


            return;
        }

        i++;

    }

    printf("Contact Not Found.\n");

    
}

void searchContact(Contact *contacts , int *pSize){

    const int SIZE = *pSize;

    if(SIZE == 0 || contacts == NULL){
        printf("\nNo Contacts Found.\n");
        return;
    }

    char name[216] = "";
    printf("Search Contact Name : ");
    scanf("%s" , name);
    getchar();

    

    for (int i = 0 ; i < SIZE; i++){
        if(!(strcmp(contacts[i].name , name))){
            printf("\n=== FOUND CONTACT ===\n\n");

            printf("---------------------------------------------------\n\n");
            printf("Name : %s\nNumber : %s\nEmail : %s\n\n" , contacts[i].name , contacts[i].number , contacts[i].email);

        }
    }

    printf("---------------------------------------------------\n\n");
    printf("\n\n***END***\n\n");



}



void addContact(Contact **contacts , int *pSize){

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

    printf("%d" , newPos);

    Contact *temp = realloc(*contacts , ((newPos+1) * sizeof(Contact)));

        

    if(temp == NULL){
        printf("Could Not Add Contact , Reallocation Failed.\n");
    }else{
        *contacts = temp;
        temp = NULL;

        

        strcpy((*contacts)[newPos].name , name);
        strcpy((*contacts)[newPos].number , number);
        strcpy((*contacts)[newPos].email , email);

      

        (*pSize)++; //Updating size of the array

        // Pushing the updates to the text file.
        pushContacts(*contacts , pSize);
        
        printf("\n**Contact Added**\n");
    }

    

}


void displayContacts(Contact *contacts , int *pSize){

    const int SIZE = *pSize;

    if(SIZE == 0 || contacts == NULL){
        printf("\nNo Contacts Found.\n");
        return;
    }

    else{

        for(int i= 0; i < SIZE; i++ ){

           
            

            printf("---------------------------------------------------\n\n");
            // Segmentation fault here - illigal memory access 
            printf("Name : %s\nNumber : %s\nEmail : %s\n\n" , contacts[i].name , contacts[i].number , contacts[i].email);

        }

        printf("---------------------------------------------------\n\n");
        printf("\n\n***END***\n\n");
    }

}