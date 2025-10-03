//Header files
#include <stdio.h>
#include <string.h>
#include "file.h"
#include "contact.h"
#include <ctype.h>

//Saving the contacts in csv file
void saveContactsToFile(AddressBook *book)
{
    //Open the file in write mode
    FILE *fptr = fopen("contact.csv", "w");//In write mode file is not need to exist

    //Check the fopen function returning NULL or not, 
    if (fptr == NULL)
    {
        printf("Error opening file for writing!\n");
        return;
    }

    //Call the sorting function
    sorting(book);

    //Print the contacts into the csv file
    //Loop runs untill Total no of we have created
    for (int i = 0; i < book->contactCount; i++)
    {
        fprintf(fptr,"%s,%s,%s\n",book->contacts[i].name,book->contacts[i].phone_no,book->contacts[i].email_id);
    }

    //Close the file
    fclose(fptr);
}

//Load the contacts into buffer
void loadContactsFromFile(AddressBook *book)
{
    //Open the file in Read mode
    FILE *fptr = fopen("contact.csv", "r");//File need to exist
    char buffer[200];  // temporary line storage

    //Check files is exist or not, if doesn't exist, fopen function return a NULL to fptr
    if (fptr == NULL)
    {
        printf("Error opening file for reading!\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fptr))//Read the contacts in csv file line by line
    {
        // Parse the line: name,phone,email
        //Following condition only satisfies, when all three values are read sucessfully.sscanf function returns the number of items it sucessfully, if it read all, it will return the 3
        if (sscanf(buffer, "%49[^,],%11[^,],%49[^\n]",book->contacts[book->contactCount].name,book->contacts[book->contactCount].phone_no,book->contacts[book->contactCount].email_id) == 3)
        {
            book->contactCount++;//Increment the count 
        }
    }

    //close the function
    fclose(fptr);
}
