#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

//function to safely get input from user
void getInput(char *prompt, char *buffer, int size)
{
     printf("%s", prompt);
    
    if (fgets(buffer, size, stdin) == NULL) 
    {
        printf("Error reading input.\n");
        buffer[0] = '\0';  // Set empty string on error
        return;
    }

    // Remove newline character if present
    buffer[strcspn(buffer, "\n")] = '\0';

    // Handle case where input was too long
    if (strlen(buffer) == size - 1 && buffer[size - 2] != '\n') 
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF); // Clear input buffer
        
    }
}

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    if(addressBook->contactCount == 0)
    {
        printf("No contacts available.\n");
        return;
    }
    printf("-----------------------------------------------------------\n");
    printf("Sr No. %-20s %-15s %-30s\n", "Name", "Contact", "Email");
    printf("-----------------------------------------------------------\n");

    for(int i = 0 ; i < addressBook->contactCount; i++)
    {
        printf("%-6d %-20s %-15s %-30s\n",
              i + 1,
              addressBook -> contacts[i].name,
              addressBook -> contacts[i].phone,   
              addressBook -> contacts[i].email);
    }
    printf("--------------------------------------------------------------\n");
    // Sort contacts based on the chosen criteria
    
}

void initialize(AddressBook *addressBook, const char *filename) {
    FILE *file = fopen(filename, "r");
    if(!file)
    {
        addressBook->contactCount = 0;
      //  populateAddressBook(addressBook);
        return;
    }
    addressBook->contactCount = 0;
    char line[150];

    while(fgets(line, sizeof(line), file))
    {
        Contact temp;
        if(sscanf(line, "%49[^,], %14[^,], %49[^\n]", 
                   temp.name, temp.phone, temp.email) == 3){
            addressBook -> contacts[addressBook->contactCount++] = temp;        

        }
        if(addressBook -> contactCount >= MAX_CONTACTS) break;
    }
    fclose(file);
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveContactsToFile(AddressBook *addressBook, const char *filename)
{
    FILE *file = fopen(filename, "w");
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(file, "%s, %s, %s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }
    fclose(file);
    printf("Contacts saved successfully! Exiting...\n");
   // saveContactsToFile(addressBook); // Save contacts to file
   // exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
     if (addressBook->contactCount >= MAX_CONTACTS) 
    {
        printf("Address book is full!\n");
        return;
    }

    Contact newContact;

    // Get Name (allows uppercase and spaces)
    printf("Enter Name: ");
    fgets(newContact.name, NAME_LEN, stdin);
    newContact.name[strcspn(newContact.name, "\n")] = '\0'; // Remove newline

    // Check for duplicate name
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcasecmp(addressBook->contacts[i].name, newContact.name) == 0) 
        {
            printf("Error: Name already exists!\n");
            return;
        }
    }

    // Get Phone and validate
    printf("Enter Phone: ");
    fgets(newContact.phone, PHONE_LEN, stdin);
    newContact.phone[strcspn(newContact.phone, "\n")] = '\0'; // Remove newline

    // Check for duplicate phone number
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].phone, newContact.phone) == 0) 
        {
            printf("Error: Phone number already exists!\n");
            return;
        }
    }

    // Validate phone: Must be exactly 10 digits
    if (strlen(newContact.phone) != 10 || strspn(newContact.phone, "0123456789") != 10) 
    {
        printf("Error: Invalid phone number. Must be exactly 10 digits!\n");
        return;
    }

    // Get Email and validate
    printf("Enter Email: ");
    fgets(newContact.email, EMAIL_LEN, stdin);
    newContact.email[strcspn(newContact.email, "\n")] = '\0'; // Remove newline

    // Check for duplicate email
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].email, newContact.email) == 0) 
        {
            printf("Error: Email already exists!\n");
            return;
        }
    }

    // Email validation: Must contain '@' and '.com'
    if (!strchr(newContact.email, '@') || !strstr(newContact.email, ".com")) 
    {
        printf("Error: Invalid email format!\n");
        return;
    }

    // Ensure email contains no uppercase letters
    for (int i = 0; newContact.email[i] != '\0'; i++) 
    {
        if (isupper(newContact.email[i])) 
        {
            printf("Error: Email should not contain uppercase letters!\n");
            return;
        }
    }

    // Store new contact and increment count
    strcpy(addressBook->contacts[addressBook->contactCount].name, newContact.name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, newContact.phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, newContact.email);
    addressBook->contactCount++;

    // Save contacts to file in APPEND mode
    FILE *file = fopen("contacts.txt", "a");
    if (!file) 
    {
        printf("Error: Could not open file for saving.\n");
        return;
    }

    fprintf(file, "%s, %s, %s\n", newContact.name, newContact.phone, newContact.email);
    fclose(file);
    printf("Contact saved successfully!\n");
	/* Define the logic to create a Contacts */
    
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    
    if (addressBook->contactCount == 0) 
    {
        printf("No contacts available to search.\n");
        return;
    }

    int choice;
    char query[EMAIL_LEN]; // Query input
    int found = 0; // Flag to track matches

    printf("\nSearch Menu:\n");
    printf("1. Search by Name\n");
    printf("2. Search by Phone\n");
    printf("3. Search by Email\n");
    printf("Enter option: ");
    scanf("%d", &choice);
    getchar(); // Clear buffer

    getInput("Enter search query: ", query, EMAIL_LEN); // Generic input prompt

    printf("\nMatching Contacts:\n");
    printf("----------------------------------------------------------------------\n");
    printf("Sr No.  %-20s %-15s %-30s\n", "Name", "Contact", "Email");
    printf("----------------------------------------------------------------------\n");

    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        int match = 0;

        // Perform search based on the selected field
        switch (choice) 
        {
            case 1:
                if (strcasestr(addressBook->contacts[i].name, query)) {
                    match = 1;
                }
                break;
            case 2:
                if (strstr(addressBook->contacts[i].phone, query)) {
                    match = 1;
                }
                break;
            case 3:
                if (strcasestr(addressBook->contacts[i].email, query)) {
                    match = 1;
                }
                break;
            default:
                printf("Invalid option! Please choose 1, 2, or 3.\n");
                return;
        }

        if (match) 
        {
            printf("%-6d  %-20s %-15s %-30s\n",
                   i + 1, 
                   addressBook->contacts[i].name, 
                   addressBook->contacts[i].phone, 
                   addressBook->contacts[i].email);
            found = 1;
        }
    }

    if (!found) 
    {
        printf("No matching contacts found!\n");
    } else 
    {
        printf("----------------------------------------------------------------------\n");
    }
}
    


void editContact(AddressBook *addressBook, const char *filename)
{
	/* Define the logic for Editcontact */
     if (addressBook->contactCount == 0) 
    {
        printf("No contacts available to edit.\n");
        return;
    }

    int choice, found = 0, selectedIndex;
    char query[EMAIL_LEN]; // Search input

    printf("\nEdit Contact Menu:\n");
    printf("1. Search by Name\n");
    printf("2. Search by Phone\n");
    printf("3. Search by Email\n");
    printf("Enter option: ");
    scanf("%d", &choice);
    getchar(); // Clear buffer

    getInput("Enter search query: ", query, EMAIL_LEN); // Search term

    printf("\nMatching Contacts:\n");
    printf("----------------------------------------------------------------------\n");
    printf("Index  %-20s %-15s %-30s\n", "Name", "Phone", "Email");
    printf("----------------------------------------------------------------------\n");

    int matchedIndices[addressBook->contactCount]; // Store matching indexes

    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        int match = 0;

        switch (choice) 
        {
            case 1:
                if (strcasestr(addressBook->contacts[i].name, query)) match = 1;
                break;
            case 2:
                if (strstr(addressBook->contacts[i].phone, query)) match = 1;
                break;
            case 3:
                if (strcasestr(addressBook->contacts[i].email, query)) match = 1;
                break;
            default:
                printf("Invalid option! Please choose 1, 2, or 3.\n");
                return;
        }

        if (match) 
        {
            matchedIndices[found] = i; // Store matching index
            printf("%-6d  %-20s %-15s %-30s\n", found + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            found++;
        }
    }

    if (found == 0) 
    {
        printf("No matching contacts found!\n");
        return;
    }

    printf("----------------------------------------------------------------------\n");
    printf("Enter the index of the contact you want to edit: ");
    scanf("%d", &selectedIndex);
    getchar(); // Clear buffer

    if (selectedIndex < 1 || selectedIndex > found) 
    {
        printf("Invalid selection!\n");
        return;
    }

    int indexToEdit = matchedIndices[selectedIndex - 1]; // Get real index

    // Edit contact details
    printf("Editing Contact: %s\n", addressBook->contacts[indexToEdit].name);
    getInput("Enter new name: ", addressBook->contacts[indexToEdit].name, NAME_LEN);
    getInput("Enter new phone: ", addressBook->contacts[indexToEdit].phone, PHONE_LEN);
    getInput("Enter new email: ", addressBook->contacts[indexToEdit].email, EMAIL_LEN);

    printf("Contact updated successfully!\n");

    saveContactsToFile(addressBook, filename); // Save changes
    
}

void deleteContact(AddressBook *addressBook, const char *filename)
{
     if (addressBook->contactCount == 0) 
    {
        printf("No contacts available to delete.\n");
        return;
    }

    char query[NAME_LEN];
    int found = 0, selectedIndex;

    getInput("Enter name to delete: ", query, NAME_LEN);

    printf("\nMatching Contacts:\n");
    printf("----------------------------------------------------------------------\n");
    printf("Index  %-20s %-15s %-30s\n", "Name", "Phone", "Email");
    printf("----------------------------------------------------------------------\n");

    int matchedIndices[addressBook->contactCount]; // Store matching indexes

    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcasestr(addressBook->contacts[i].name, query)) 
        { // Case-insensitive partial match
            matchedIndices[found] = i;
            printf("%-6d  %-20s %-15s %-30s\n", found + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            found++;
        }
    }

    if (found == 0) 
    {
        printf("No matching contacts found!\n");
        return;
    }

    printf("----------------------------------------------------------------------\n");
    printf("Enter the index of the contact you want to delete: ");
    scanf("%d", &selectedIndex);
    getchar(); // Clear buffer

    if (selectedIndex < 1 || selectedIndex > found) 
    {
        printf("Invalid selection!\n");
        return;
    }

    int indexToDelete = matchedIndices[selectedIndex - 1]; // Get actual index

    // Shift contacts to fill the gap
    for (int i = indexToDelete; i < addressBook->contactCount - 1; i++) 
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--; // Reduce count
    printf("Contact deleted successfully!\n");

    void saveContacts( AddressBook *addressBook, const char); // Save updated list
	/* Define the logic for deletecontact */
   
}
