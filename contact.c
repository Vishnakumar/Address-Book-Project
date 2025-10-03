#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include <ctype.h>

//--------------------------------------------Function for creating the contact--------------------------------------
//Global variable declaration
char buffer[100];

void createContact(AddressBook *book) 
{

    // Ensure contactCount does not exceed maximum value
    if (book->contactCount >= 100) {
        printf("Address Book is full!\n");
        return;
    }

    //Initialization
    //now , n directly access the int variable contactContact at addressBook
    //For example, if n = 1, book hold the address of Addressbook struture, then it directly put the 1 at contactCount 
    int n = book->contactCount;

    //-----------Read the input from user one by one using function-----------
    strcpy(book->contacts[n].name,name());
    strcpy(book->contacts[n].phone_no,phone(book));
    strcpy(book->contacts[n].email_id,email(book));
    
    //Increament the count of the contacts
    book->contactCount++;

    //print the successfull message
    printf("Successfully contact is saved\n");
}

//Function for reading the name from user
char* name()
{
    //Get the name from user
    do 
    {
        printf("Enter the Name     : ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';//Remove the newline by enter
    } while(!validate_name(buffer));//Validate the name
    return buffer;
}

//Function for reading the phone number from user untill it's get valid
char* phone(AddressBook *book)
{
    //Get the phone number from user
    Label1 : 
    do 
    {
        printf("Enter the Phone No : ");
        scanf("%s", buffer);
        getchar();//consume the newline
    } while(!validate_phone_no(buffer));//By using valid function will check entered phone number is new or already exist and also valid like only contains 10 digits and non alphabets

    //Checking the given number is already exist or not
    for(int i = 0 ; i < book->contactCount ; i++)
    {
        if((strcmp(book->contacts[i].phone_no, buffer) == 0)) 
        {
            printf("Already Phone number is exist, so enter new number\n");
            goto Label1;//If entered phone is already there, then it go to label 1 and this function will again ask input
        }
    }

    //Return the readed number to create contacts function
    return buffer;
}

//Function for reading the Email id from user untill it's gets valid
char* email(AddressBook *book)
{
    Label1 : 
    //Get the email id from user
    do 
    {
        printf("Enter the Email id : ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

    } while(!validate_email(buffer));//call the validate function for email id

    //Checking the given email id r is already exist or not
    for(int i = 0 ; i < book->contactCount ; i++)
    {
        if((strcmp(book->contacts[i].email_id, buffer)== 0)) //Compare function return 0 only comparing two contacts get match
        {
            printf("Already email id is exist, so please enter new mail id\n");
            goto Label1;
        }
    }
   
    //Return the readed email id to create contacts function
    return buffer;
}

//-----------------------------------------------end---------------------------------------------------------

//-------------------------------------Validation functions-------------------------------------------------

/*Following function validate the name
1. Given name only contains alphabets or not
Then allow spaces also
*/
int validate_name(const char *p_name)
{
    for(int i = 0 ; p_name[i] != '\0' ; i++) {
        if((isalpha(p_name[i]) || p_name[i] == ' ') == 0) {
            printf("Invalid name, please enter valid name\n");
            return 0;
        }
    }
    return 1;
}

/*Following function validate the phone number1
1.Entered number is alphabets
2.Given number only contains 10 digits
*/
int validate_phone_no(const char *p_phone_no) {
    
    int len = (int)strlen(p_phone_no);

    for(int i = 0 ; p_phone_no[i] != '\0' ; i++) {
    if(!isdigit(p_phone_no[i])) {
        printf("Invalid phone number, only digits allowed, so please enter valid phone number\n");
        return 0;
    }
    }
    
    if(len != 10) {
        printf("Invalid phone number, please enter only 10 digits\n");
        return 0;
    }
    return 1;
}

/*Function validates followings things
Checks
1.Entered email id is should not start with @
2.Entered id is only contains lower case
3.Entered id should contains @
4.Entered id should contains .com at end
5.Entered id should contains more than 1 character between @ and .com
6.Checks given id should contains only alphabets charactere between @ and .com
*/
int validate_email(const char *p_email) {

    //Checking the given email id start without @, if given id will start with @, it will print error message and return 0
    if(p_email[0] == '@') {
        printf("Invalid email, you cannot start with @, so enter valid email id \n");
        return 0;
    }

    //Checking the given email id only contain lower case or not
    for(int i = 0 ; p_email[i] != '\0' ; i++) 
    {
        if(!islower(p_email[i]) && !(p_email[i] == '@') && !(p_email[i] == '.') && !(p_email[i] >= '0' && p_email[i] <= '9'))
            {
                printf("Invalid email, you should use lower case letters, so enter valid email id \n");
                return 0;
            }
    }
    
    //Checking the given email id contain @
     if(strchr(p_email, '@') == NULL) {
        printf("Invalid email, current id does not have @, so enter valid email id \n");
        return 0;
    }

    //Checking the given if contains .com using strstr function, it find the substring is found or not in main string
    if(strstr(p_email, ".com") == NULL)//If sub string is not present, then it will return a NULL, it means nothing
    {
        printf("Invalid email, must contain .com, so enter valid email id \n");
        return 0;
    }
    
    char *a = strchr(p_email, '@');//strchr function is used to find the first occurence of particular character and it returns its address
    char *b = strchr(p_email, '.');
   
    //Checks given id should contains more than 1 charactere between @ and .com
    if((b - a - 1) <= 0)
    {
        printf("Invalid Email id, please enter valid email id\n");
        return 0;
    }
    
    //Checks given id should contains only alphabets charactere between @ and .com
    for (char *p = a + 1; p < b; p++) 
    {
        if (!isalpha((unsigned char)*p)) 
        {
            printf("Invalid email, you should have alphabets between @ and .com, so enter valid email id \n");
            return 0;
        }
    }
    return 1;
}

//-----------------------------------------Function for contact searching-----------------------------------------
//Global variable declaration
int found_index = -1;

//Function found the contact
int found_search(AddressBook *book, char *content, int option)
{
    //Ensure contactCount does not exceed maximum value
    if (book->contactCount == 0) {
        printf("No contacts available\n");
        return -1;
    }

    //Declaration
    int i;
    // Iterate through all contacts
    for (i = 0; i < book->contactCount; i++) 
    {
        if (option == 1 && strcasecmp(book->contacts[i].name, content) == 0)//Here it compare the names without considering lowercase or uppercase
        {
            //print the contacts at console
            printf("Found: %d, %s, %s, %s\n", i + 1 , book->contacts[i].name, book->contacts[i].phone_no, book->contacts[i].email_id);
            found_index = i;//store cuurect i value into fount_index variable for further use 
        }
        else if (option == 2 && strcmp(book->contacts[i].phone_no, content) == 0)
        {
            printf("Found: %d, %s, %s, %s\n", i + 1 , book->contacts[i].name, book->contacts[i].phone_no, book->contacts[i].email_id);
            found_index = i;    
        }
        else if (option == 3 && strcmp(book->contacts[i].email_id, content) == 0)
        {
            printf("Found: %d, %s, %s, %s\n", i + 1 , book->contacts[i].name, book->contacts[i].phone_no, book->contacts[i].email_id);
            found_index = i;    
        }
    }
    
}

//------------------------------------Search the contacts details-----------------------------------------------------
void searchContact(AddressBook *book)
{

    //Initialization
    int option;//Store input from user, it can be choosed one among option
    char search_content[50];
    //Show the option details in the console
    printf("Search by \n 1. Name\t 2. Phone\t 3. Email id \t 4. Exit\n");

    //Read the input from user untill it valid(between 1 to 4)
    do
    {
        //Read the input from user
        printf("Enter the Search option : ");
        if(scanf("%d", &option) != 1)
        {
            printf("Invalid input, Please enter valid a number\n"); 
            while(getchar() != '\n');
            continue;
        }
        getchar();//Remove the \n

        //Check the input lies between our mentioned range, if not, show error message
        if(!(option > 0 && option <= 4)) 
        printf("Please choose valid option based on given menu\n");
    }while(!(option> 0 && option <= 4));//If not in range, gain read the input

    int j = 0;
    
    //Switch Statement
    switch (option)
    {
        case 1:
        {
            //Read the name
            printf("Enter the Name : ");
            fgets(search_content, sizeof(search_content), stdin);
            search_content[strcspn(search_content, "\n")] = '\0';
            j = found_search(book, search_content, option);//call the function and store returned value from called function
            break;
        }
        case 2:
        {
            printf("Enter the Phone Number : ");
            fgets(search_content, sizeof(search_content), stdin);
            search_content[strcspn(search_content, "\n")] = '\0';
            j = found_search(book, search_content, option);
            break;
        }
        case 3:
        {
            printf("Enter the Email id : ");    
            fgets(search_content, sizeof(search_content), stdin);
            search_content[strcspn(search_content, "\n")] = '\0';
            j = found_search(book, search_content, option);
            break;  
        } 
        case 4:
        { 
            printf("Existing successfully,..\n.");
            break;
        }       
    }

}

//------------------------------------Edit the contacts details-----------------------------------------------------
//Editing function receives address of book structure and returns nothing
//Following function is used to edit the contacts details like name, number and email
void editContact(AddressBook *book)
{
    // Ensure contactCount does not exceed maximum value
    if (book->contactCount == 0) {
        printf("No contacts available\n");
        return;
    }
    // Call the function to see which contact needs to be edited
    searchContact(book);

    //If contact is not, it will print that message
    if(found_index == -1) 
    {
        printf("Contact is not found\n");
        return;
    }
    
    //Declaration
    int edit_option;
    
    //Show the option details in the console
    printf("Edit by \n 1. Name\t 2. Phone\t 3. Email id \t 4. ALL \t 5. Exit\n");
    
    //Read the input from user untill it valid( between 1 to 4)
    do
    {
        printf("Select an option : ");
        
        if(scanf("%d", &edit_option) != 1)
        {
            printf("Invalid option, please enter valid option\n");
            while(getchar() != '\n');
            continue;
        }
        while(getchar() != '\n');

        //Check the input lies between our mentioned range, if not show error message
        if(!(edit_option > 0 && edit_option <= 5)) 
        printf("Please enter option based on menu\n");
    }while(!(edit_option > 0 && edit_option <= 5));//If not in range, gain read the input

    switch (edit_option)
    {
        case 1:
        {
            //Replace the old name with the new one by copying it
            strcpy(book->contacts[found_index].name, name());
            printf("Name is successfully changed\n");
            break;
        }
        case 2:
        {
            // Replace the phone number with the new one by copying it
            strcpy(book->contacts[found_index].phone_no, phone(book));
            printf("Phone number is sucessfully changed\n");
            break;
        }
        case 3:
        {
           // Replace the old email id with the new one by copying it
            strcpy(book->contacts[found_index].email_id, email(book));
            printf("Email id is successfully changed\n");
            break;
        }
        case 4:
        {
            //Replace the all details with old once
            strcpy(book->contacts[found_index].name, name());
            strcpy(book->contacts[found_index].phone_no, phone(book));
            strcpy(book->contacts[found_index].email_id, email(book));
            printf("Contacts is successfully changed\n");
            break;
        }
        case 5:
        {
            printf("Existing successfully,..\n.");
            return;

        }
    }
}

//-------------------------------- Function Deleting the contacts --------------------------------
//Declaring the global variable
int delete_option;

//Deleting function receives address of book structure and returns nothing
void deleteContact(AddressBook *book)
{
    //Ensure contactCount does not exceed maximum value
    if (book->contactCount == 0) {
        printf("No contacts available\n");
        return;
    }
    //Call the function for seeing the which Contact has to be delete
    searchContact(book);

    //If contact is not, it will print that message
    if(found_index == -1) 
    {
        printf("Contact is not found\n");
        return;
    }

    //Read the input from user
    do
    {
        //Read the input from user
        printf("Enter the serial number : ");
        if((scanf("%d", &delete_option) != 1))//scanf the input, if input is digit, then it return 1, else return 0
        {
            printf("Invalid input, please enter again\n");
            while(getchar() != '\n');//clear the input buffer
            continue;
        }

        getchar();//consume newline after succefull readind of input

        //Check the input lies between our mentioned range, if not show error message
        if(!(delete_option > 0 && delete_option <= book->contactCount)) {
        printf("Please choose valid corresponding serial number\n");
        }
    }while(!(delete_option > 0 && delete_option <= book->contactCount));//If not in range, gain read the input

    //Delete the contact using shifting method
    for(int i = 0 ; i < book->contactCount - 1 ; i++)
    {
        //Shift the next struct array element into the current index (deleting one element)
        if(i >= delete_option - 1)
        book->contacts[i] = book->contacts[i + 1];
    }

    printf("Contact is successfully deleted\n");

    //After deleting the contact, reduce the total count of contacts in the book
    book->contactCount--;
}

//--------------------------------------------Function to display the contact------------------------------------------------------
void display(AddressBook *book) 
{
    //Check the Contacts is there or not
    if (book->contactCount == 0) {
        printf("Sorry, No contacts available.\n");
        return;
    }

    //Call the sorting function
    sorting(book);
        
    printf("==========================================================\n");
    printf("======================  Address Book =====================\n");    
    printf("%-2s| %-14s | %-10s | %s\n", "No.", "Name", "Phone", "Email");
    printf("----------------------------------------------------------\n");

    //Following loop prints all available contacts upto book->contactcount
    for (int i = 0; i < book->contactCount; i++) 
    printf("%-2d | %-14s | %-6s | %s\n", i + 1, book->contacts[i].name, book->contacts[i].phone_no, book->contacts[i].email_id);
    printf("==========================================================\n");
}
//------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------Bubble Sorting for sorting the names in A to Z order--------------------------------------------
void sorting(AddressBook *book)
{
    //Structure Declaration
    Contact temp;//Only for temporary

    //Following loop sorting the user's names in Alphabetic order
    for(int j = 0 ; j < book->contactCount ; j++)//Loop run untill total count is reached
    {
        for(int i = 0 ; i < book->contactCount - 1 ; i++)
        {
            //We have converted the First letter in names into lower case only for comparing, so comparing is done between small alphabets
            if(tolower(book->contacts[i].name[0]) > tolower(book->contacts[i + 1].name[0]))
            {
                //temp structure contains space for names, phone no, email and it can able to hold the contacts for temporarily
                temp = book->contacts[i];
                book->contacts[i] = book->contacts[i + 1];
                book->contacts[i + 1] = temp;
            }
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------

