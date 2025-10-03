#ifndef CONTACT_H
#define CONTACT_H
#define MAX_CONTACTS 100

//----------------------------------Structure Initialization----------------------------------------
typedef struct 
{
    //Following are members or fields
   char name[50];//It able to store the 49 characters and 1 for \0 and it purpose to store name of the user
   char phone_no[12];//Store 12 and 1 for \0 and its purpose to store the phone numbers
   char email_id[50];//Store 49 and 1 for \0 and it purpose for storing the email ids of users
} Contact;//here we have declared the our customized data type named "Contact"

typedef struct
{
    //Member to keep track the count of contacts
    int contactCount;

    //Defination of contact array
    Contact contacts[100];//Here we have used customized data type to construct the struct array, which is capable to store 100 contacts
} AddressBook;//Here, declared the customized struct datatype

//-----------------------------------------------end-----------------------------------------------

//-----------------------------------------Function Prototypes-------------------------------------
int validate_email(const char []);
int validate_name(const char []);
int validate_phone_no(const char []);
void createContact(AddressBook *);
void searchContact(AddressBook *);
void editContact(AddressBook *);
void deleteContact(AddressBook *);
void display(AddressBook *);
void saveContactsToFile(AddressBook *addressBook);
char* name();
char* phone();
char* email();
int found_search(AddressBook *book, char *content, int option);
void sorting(AddressBook *book);

//-----------------------------------------------end-----------------------------------------------


#endif
