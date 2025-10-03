/*
    Project Title : Address Book
    Author        : Vishnakumar M
    Date          : 17/09/2025
    Description   : This is a simple console-based Address Book project. 
                    It allows users to manage their list of contacts with features such as:
                        - Adding contacts
                        - Searching contacts
                        - Viewing contacts
                        - Editing contacts
                        - Deleting contacts
                        - Saving contacts
                    
                    The project emphasizes:
                        - File handling for persistent storage
                        - Input validation for error-free user interaction
                        - Modular programming for better structure and maintainability
*/

// Header Files
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "contact.h"
#include "file.h"

//-----------------------------------------------Main function--------------------------------------
int main() {

    //Defination
    AddressBook book;

    
    //Variable Initialization 
    int option = 0;//Store input from user, it can be choosed one among option
    loadContactsFromFile(&book);

    //Super While loop, it will never get terminate
    while(1) 
    {
        
    // Print the Menu
    printf("==========================================================\n");
    printf("                           MENU                           \n");
    printf("==========================================================\n");
    printf("              CHOOSE THE BELOW OPTION             \n");
    printf(" 1. Create\n 2. List the contact\n 3. Search Contact\n 4. Edit Contact\n 5. Delete contact\n 6. Save contact\n 7. Exit\n");
    printf("==========================================================\n");

    do
    {
        printf("Select an option : ");
        scanf("%d", &option);
        getchar();

        if(!(option > 0 && option <= 7)) printf("Invalid Input, please select an valid option");
    }while(!(option > 0 && option <= 7));

    //Switch statement, 
    switch(option) {
        case 1:
            createContact(&book);//here, we have passing the address of user variable
            break;
        case 2:
            display(&book);
            break;
        case 3:
            searchContact(&book);
            break;
        case 4:
            editContact(&book);
            break;
        case 5:
            deleteContact(&book);
            break;
        case 6:
            saveContactsToFile(&book);
            printf("Contacts is successfully saved\n");
           break;
        case 7:
            //When user enter option 7, program going to terminate
            printf("Exiting successfully,..\n");
            return 0;
        default:
            //If user enter, unvalid input, then it will show error message
            printf("Invalid option! Please choose again.\n");
    }
    }
}

//-----------------------------------------------end of main function-----------------------------------------------
