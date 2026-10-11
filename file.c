#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE* fp = fopen("contacts.csv","w");
    if(fp == NULL)
    {
        printf("file not found\n");
        return;
    }
    fprintf(fp,"%d\n",addressBook->contactCount);
    for(int i = 0;i<addressBook->contactCount;i++)
    {
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);
}

void loadContactsFromFile(AddressBook *addressBook) 

{
    FILE* fp = fopen("contacts.csv","r+");
    if(fp == NULL)
    {
        printf("file not found\n");
        return;
    }
    
    for(int i = 0;i<addressBook->contactCount;i++)
    {
        fscanf(fp,"%49[^,], %19[^,], %49[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);
}
