#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100
#define NAME_LEN 50
#define PHONE_LEN 15
#define EMAIL_LEN 50

typedef struct {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    char email[EMAIL_LEN];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

//Function declaration
void initializeDummyContacts(AddressBook *addressBook);
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook, const char *filename);
void deleteContact(AddressBook *addressBook, const char *filename);
void listContacts(AddressBook *addressBook, int sortCriteria);
void initialize(AddressBook *addressBook, const char *filename);
void saveContactsToFile(AddressBook *AddressBook, const char *filename);
void getInput(char *prompt, char *buffer, int size);

#endif
