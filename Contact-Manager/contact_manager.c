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

int extractContacts(Contact **contacts ,int *pSize); // gets contacts stored in contacts.txt and stores them into array.
void pushContacts(Contact *contacts ,int *pSize); // takes the contacts stored in the array and adds them to contacts.txt

void addContact(Contact **contacts , int *pSize); // adds new contact to storage.
void displayContacts(); // displays all contacts in formatted order
void searchContact(Contact *contacts , int *pSize); // searches by name
void editContact(Contact *contacts , int *pSize); // can edit one or more properties 
void deleteContact(Contact **contacts , int *pSize); //number and name incase 2 contacts have same name


        
int managerApp();


int main(){

    int exitStatus = managerApp();

    return exitStatus;
}



int managerApp(){

    printf("==============================\n");
    printf("  Welcome To Contact Manager  \n");
    printf("==============================\n\n");

    bool managerActive = true;
    Choice choice = 0; 

    Contact *contacts = NULL; // this pointer and its pointer will be passed on to functions to operate on it 
    int size = 0; // Since contacts is a pointer and not an array , we have to keep a track of the size (passing pointer to size wherever needed)
    


    do{
        printf("[*1] - Display Contacts\n");
        printf("[*2] - Search Contact\n");
        printf("[*3] - Add Contact\n");
        printf("[*4] - Edit Contact\n");
        printf("[*5] - Delete Contact\n");
        printf("[*6] - Exit\n\n");
        printf("==============================\n");
        printf("*** Select an option (1 to 6) : ");
        scanf("%u",&choice);
        getchar(); // eliminating the \n in input buffer

        int extractionError = extractContacts(&contacts , &size);
        if (extractionError){
            return extractionError;
        }

        switch(choice){
            case DISPLAY:
            
                displayContacts(contacts , &size);
                break;

            case SEARCH:
                
                searchContact(contacts , &size);
                break;

            case ADD:
                 
                addContact(&contacts , &size);
                break;

            case EDIT:
                
                editContact(contacts , &size);
                break;

            case DELETE:

                deleteContact(&contacts , &size);
                break;

            case EXIT:

                managerActive = false;
                free(contacts);
                contacts = NULL;
                printf("\n\n***THANK YOU***\n\n");
                break;

            default:
                printf("\n*** Invalid Choice! select from [ 1 | 2 | 3 | 4 | 5 | 6 ] ***\n\n");

        }

    }while(managerActive);


    // freeing memory
    if(contacts != NULL){
        free(contacts);
        contacts = NULL;
    }

    return 0;
}

int extractContacts(Contact **contacts ,int *pSize){


    FILE *pFile = fopen("Contact-Manager/contacts.txt" , "r");
    if(pFile == NULL){
        printf("\nCould Not open File\n\n");
        fclose(pFile);
        return 1;
    }

    if((*contacts) != NULL){ // freeing if not free
        free(*contacts);
        *contacts = NULL;
        *pSize = 0;
    }



    char buffer[500]; 



    *contacts = malloc(sizeof(Contact));
    if((*contacts) == NULL){
        printf("\nAllocation Initialization failed\n");
        return 1;
    }

    

    Contact *temp = NULL; // used for realloc
    int currentPoint = 0;

    if(fgets(buffer , sizeof(buffer) , pFile) == NULL){
        // printf("\n*** WARNING : NO CONTACT SAVED ***\n\n");
        return 0;
    }

    do{


        
        // saving to array
        sscanf(buffer , "%216[^,],%15[^,],%216[^\n]" ,(*contacts)[currentPoint].name ,(*contacts)[currentPoint].number ,(*contacts)[currentPoint].email);
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
        printf("Realloc Failed\n");
        return 1;
    }
    *contacts = temp;
    temp = NULL;

    // updating to new size
    *pSize = currentPoint;
    

    fclose(pFile);

    return 0;
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
    printf("\n========================");
    printf("\n***Saved Successfully***");
    printf("\n========================\n\n");

}


void editContact(Contact *contacts , int *pSize){

    const int SIZE = *pSize;

    if(SIZE == 0 || contacts == NULL){
        printf("\n=====================\n");
        printf("\n**No Contacts Found**\n");
        printf("\n=====================\n");
        return;
    }

    char name[216] = "";
    char number[15] = "";

    printf("\n");
    printf("[*] Enter Contact *Name* To Edit : ");
    scanf("%s" , name);
    getchar();
    printf("\n");
    printf("[*] Enter Contact *Number* To Edit : ");
    scanf("%s" , number);
    getchar();

    

    for(int i = 0 ; i < SIZE ; i++){

        if( !(strcmp(contacts[i].name , name)) && !(strcmp(contacts[i].number , number)) ){
            int choice = 0;
            printf("\n===================================\n");
            printf("\n***What would you like to edit ?***\n");
            printf("*[1] Name\n*[2] Number\n*[3] Email\n");
            printf("\n===================================\n\n");
            printf("[*] Select one of the choices : ");
            scanf("%d" , &choice);
            getchar(); 

            switch(choice){
                case 1 : 
                    
                    printf("\n==================\n");
                    printf("Enter new *name* : ");
                    scanf("%s" , contacts[i].name);
                    printf("\n==================\n\n");
                    break;
                    
                case 2 : 
                    printf("\n====================\n");
                    printf("Enter new *number* : ");
                    scanf("%s" , contacts[i].number);
                    printf("\n====================\n\n");
                    break;
                    
                case 3 : 
                    printf("\n===================\n");
                    printf("Enter new *email* : ");
                    scanf("%s" , contacts[i].email);
                    printf("\n===================\n\n");
                    break;
                
                default :
                    printf("\n***Invalid Choice***\n");
                    
            }

            // contacts in the array updated

            pushContacts(contacts , pSize); // saving
            return;
        }

    }

    printf("\n=========---=========\n");
    printf("**Contact not found**\n");
    printf("=========---=========\n\n");




}


void deleteContact(Contact **contacts , int *pSize){

    const int SIZE = *pSize;

    if(SIZE == 0 || *contacts == NULL){
        printf("\n=======================\n");
        printf("***No Contacts Found***\n");
        printf("=======================\n\n");
        return;
    }

    char name[216] = "";
    char number[15] = "";

    printf("[*] Enter Contact *Name* To Delete : ");
    scanf("%s" , name);
    getchar();
    printf("[*] Enter Contact *Number* To Delete : ");
    scanf("%s" , number);
    getchar();

    
    

    int i = 0;

    while( i < SIZE){

        if( !(strcmp((*contacts)[i].name , name)) && !(strcmp((*contacts)[i].number , number)) ){ 

            printf("\n===================\n");
            printf("**Contact Found**\n");
            printf("===================\n\n");

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
                // to deal with a single contact 
                free(*contacts);
                *contacts = NULL;
                *pSize = 0;


            }else{
                Contact *temp = realloc(*contacts , (SIZE-1) * (sizeof(Contact)));
                if(temp == NULL){
                    printf("Realloc failed - Deletion\n");
                    return;
                }
                *contacts = temp;
                temp = NULL;

                (*pSize)--; // updating size 

            }

            
            pushContacts(*contacts , pSize);
            printf("\n=======================\n");
            printf("*** Contact Deleted ***\n"); 
            printf("=======================\n\n");

            return;
        }

        i++;

    }

    printf("\n=======================\n");
    printf("***Contact Not Found***\n");
    printf("=======================\n");

    
}

void searchContact(Contact *contacts , int *pSize){

    const int SIZE = *pSize;

    if(SIZE == 0 || contacts == NULL){
        printf("\n==================\n");
        printf("No Contacts Found.\n");
        printf("==================\n\n");
        return;
    }

    char name[216] = "";
    printf("[*] Search Contact Name : ");
    scanf("%s" , name);
    getchar();

    

    for (int i = 0 ; i < SIZE; i++){
        if(!(strcmp(contacts[i].name , name))){
            printf("\n=====================\n");
            printf("=== FOUND CONTACT ===\n");
            printf("=====================\n\n");

            printf("---------------------------------------------------\n\n");
            printf("Name : %s\nNumber : %s\nEmail : %s\n\n" , contacts[i].name , contacts[i].number , contacts[i].email);

        }
    }

    printf("---------------------------------------------------\n");
    printf("\n\n***END***\n");
    printf("---------------------------------------------------\n\n");



}



void addContact(Contact **contacts , int *pSize){

    char name[216] = "";
    char number[15] = "";
    char email[216] = "";

    printf("\n[*] Enter the Name : ");
    scanf("%s" , name);
    getchar();
    printf("\n[*] Enter the Number : ");
    scanf("%s" , number);
    getchar();
    printf("\n[*] Enter the Email : ");
    scanf("%s" , email);
    getchar();

    int newPos = *pSize;


    Contact *temp = realloc(*contacts , ((newPos+1) * sizeof(Contact)));

        

    if(temp == NULL){
        printf("Could Not Add Contact , Reallocation Failed.\n");
        return;
    }else{
        *contacts = temp;
        temp = NULL;

        

        strcpy((*contacts)[newPos].name , name);
        strcpy((*contacts)[newPos].number , number);
        strcpy((*contacts)[newPos].email , email);

      

        (*pSize)++; //Updating size of the array

        // Pushing the updates to the text file.
        pushContacts(*contacts , pSize);
        
        printf("=====================");
        printf("\n**Contact Added**\n");
        printf("=====================\n\n");
    }

    

}


void displayContacts(Contact *contacts , int *pSize){

    const int SIZE = *pSize;

    if(SIZE == 0 || contacts == NULL){
        printf("\n\n=========================");
        printf("\n**No Contacts Found**\n");
        printf("=========================\n\n");
        return;
    }

    else{

        for(int i= 0; i < SIZE; i++ ){

           
            

            printf("---------------------------------------------------\n\n");
            // Segmentation fault here - illigal memory access 
            printf("[*] Name : %s\n[*] Number : %s\n[*] Email : %s\n\n\n" , contacts[i].name , contacts[i].number , contacts[i].email);

        }

        printf("---------------------------------------------------");
        printf("\n\n***END***\n\n");
        printf("---------------------------------------------------\n\n");
    }

}