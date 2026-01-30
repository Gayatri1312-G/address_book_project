#ifndef FILE_H
#define FILE_H

#include "contact.h"

void saveContactsToFile(AddressBook *addressBook, const char *filename);
void loadContactsFromFile(AddressBook *addressBook, const char *filename);

#endif
