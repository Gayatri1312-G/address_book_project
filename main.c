#include <stdio.h>
#include "contact.h"

void initializeDummyContacts(AddressBook *addressBook);
int main() {
    
    AddressBook addressBook;
    initialize(&addressBook, "contacts.txt"); // Initialize the addressbook

    //Optional : Add dummy contacts only if the file is empty
    if(addressBook.contactCount == 0)
    {
        initializeDummyContacts(&addressBook);
    }

    int choice;
    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search all contacts\n");
        printf("3. Edit all contacts\n");
        printf("4. Delete all contacts\n");
        printf("5. list all contacts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook, "contacts.txt");
                break;
            case 4:
                deleteContact(&addressBook, "contacts.txt");
                break;
            case 5:
                printf("Select sort criteria:\n");
                printf("1. Sort by name\n");
                printf("2. Sort by phone\n");
                printf("3. Sort by email\n");
                printf("Enter your choice: ");
                int sortChoice;
                scanf("%d", &sortChoice);
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                //saveContactsToFile(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    
       return 0;
}
