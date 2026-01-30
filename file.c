#include <stdio.h>
#include "contact.h"
#include "file.h"

void saveContactsToFile(AddressBook *addressBook, const char *filename) 
{
	FILE* fp = fopen("addressbook.csv","w");
	if(fp == NULL)
	{
		printf("File not found.");
	}
	fprintf(fp,"#%d\n",addressBook->contactCount);
	for(int i = 0; i < addressBook->contactCount; i++)
	{
		fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
	}

	fclose(fp);
  
}

//load of the contacts to store the data
void loadContactsFromFile(AddressBook *addressBook, const char *filename) 
{
	FILE* fp = fopen("addressbook.csv","r");
	fscanf(fp,"#%d",&addressBook->contactCount);
	int i = 0;
	while(fgetc(fp) != EOF)
	{
		fscanf(fp,"%[^,],%[^,],%[^\n]",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
		i++;
	}
	fclose(fp);
}


  

