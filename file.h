#ifndef FILE_H
#define FILE_H

#include "contact.h"

void saveContactsToFile(AddressBook *book);
void loadContactsFromFile(AddressBook *book);
void edit_deleteContactsToFile(AddressBook *book);


#endif
