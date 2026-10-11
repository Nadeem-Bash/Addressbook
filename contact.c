#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
int validate_name(char*);                            //prototype for validating name
int validate_phno(char*,AddressBook*);               //prototype for validating phone number
int validate_email(char*,AddressBook*);              //prototype for validating e-mail id
void namesearch(AddressBook*);          //prototype for searching by name (search)
void phonenosearch(AddressBook*);       //prototype for searching by phone number (search)
void emailidsearch(AddressBook*);       //prototype for searching by emailid (search)
void editsearchname(AddressBook*);      //prototype for searching by name (edit)
void editsearchphone(AddressBook*);     //prototype for searching by phone number (edit)
void editsearchmailid(AddressBook*);    //prototype for searching by email id (edit)
void delsearchname(AddressBook*);       //prototype for searching by name (delete)
void delsearchphone(AddressBook*);      //prototype for searching by phone number (delete)
void delsearchmailid(AddressBook*);     //prototype for searching by email id (delete)
void edit(AddressBook*,int);            //prototype for selecting the detail to edit (edit) 
void editname(AddressBook*,int);        //prototype for editing name
void editphoneno(AddressBook*,int);     //prototype for editing phone number
void editemailid(AddressBook*,int);     //prototype for editing email id 
void delete(AddressBook*,int);          //prototype for deleti


int arr[50];
void listContacts(AddressBook *addressBook) // int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    printf("\n%d contacts\n",addressBook->contactCount);
    for(int i=0;i<addressBook->contactCount;i++)
    {
        printf("%-25s %-20s %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    } 
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);

    
    //Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    printf("\n        CREATE CONTACT\n");
	/* Define the logic to create a Contacts */
    char _name[50]; // defined a string for name
    do
    {
        printf("Enter the contact name\n");
        scanf(" %[^\n]",_name); //reading the name
        if(validate_name(_name)) //sending the string to validate function.
        {
            break;
        }
        else
        {
            printf("Error: please enter a valid name\n");
        }
    }while(!validate_name(_name)); // returns to the loop to enter name again if validation fails

    //entering phone number
    char _phno[20];
    int valid;
    do
    {
    printf("Enter the phone number:");
    scanf("%s",_phno);  // read phone number
    valid = validate_phno(_phno,addressBook);
    if (!valid) //if validation fails and returns zero it enters the if condition
    {
        printf("Error: please enter a valid phone number\n");

        // clear leftover input to prevent problems
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF); //gets charecter from the stdin and discards them
    }
    }while (!valid);

    //entering Emailid
    char _email[50];
    int valid1;
    do{
    printf("Enter email id: ");
    scanf("%s",_email); //read the mailid
    valid1 = validate_email(_email,addressBook);
    if(!valid1)
    {
        printf("Error: please enter a valid mail id\n");
        // clear leftover input to prevent problems
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF); //gets charecter from the stdin and discards them
    }
    }while(!valid1);

    // copying contact information to structure after validation
    strcpy(addressBook->contacts[addressBook->contactCount].name,_name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,_phno);
    strcpy(addressBook->contacts[addressBook->contactCount].email,_email);
    addressBook->contactCount++;
    printf("\nNew contact created.\n");
}

void searchContact(AddressBook *addressBook) 
{
    printf("\n        SEARCH CONTACT");
    int choice;
    do {
        printf("\nSearch by:\n");
        printf("1. Name\n");
        printf("2. Phone number\n");
        printf("3. Email id\n");		
        printf("4. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                namesearch(addressBook);
                break;
            case 2:
                phonenosearch(addressBook);
                break;
            case 3:
                emailidsearch(addressBook);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}

void editContact(AddressBook *addressBook)
{
    printf("\n        EDIT CONTACT");
    int choice;
    do{
        printf("\nFind the contact to edit using:\n");
        printf("1.Name\n");
        printf("2.Phone number\n");
        printf("3.Email id\n");
        printf("4.Back\n");
        
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            editsearchname(addressBook);
            break;
            case 2:
            editsearchphone(addressBook);
            break;
            case 3:
            editsearchmailid(addressBook);
            break;
            case 4:
            printf("Exiting...\n");
            break;
            default :
            printf("Invalid choice. Please try again.\n");
        }
    }while(choice != 4);

	/* Define the logic for Editcontact */

}

void deleteContact(AddressBook *addressBook)
	/* Define the logic for deletecontact */
{
    for(int i = 0;i<49;i++)
    {
        arr[i] = 0;
    }
    printf("\n        DELETE CONTACT");
    int choice;
    do{
        printf("\nFind the contact to delete using:\n");
        printf("1.Name\n");
        printf("2.Phone number\n");
        printf("3.Email id\n");
        printf("4.Exit\n");
        
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            delsearchname(addressBook);
            break;
            case 2:
            delsearchphone(addressBook);
            break;
            case 3:
            delsearchmailid(addressBook);
            break;
            case 4:
            printf("Exiting...\n");
            break;
            default :
            printf("Invalid choice. Please try again.\n");
        }
    }while(choice != 4);
}

//----------------------------------------------------FUNCTIONS----------------------------------------------------------------------------------------------

//FUNCTION TO VALIDATE NAME
int validate_name(char _name[])
{
    int flag=0;
    for(int i=0;i<strlen(_name);i++)
    {
        if((_name[i] >= 'a' && _name[i] <= 'z') || (_name[i] >= 'A' && _name[i] <= 'Z') || (_name[i] == ' '))
        {
            flag++;
        }
        else
        {
            return 0;
        }
    }
    if(flag)
        return 1;
}

// FUNCTION TO VALIDATE PHONE NUMBER
int validate_phno(char _phno[], AddressBook* addressBook)  
{
    int len = strlen(_phno);
    if (len != 10) // check whether number has exactly 10 digits
        return 0;
    for (int i = 0; i < len; i++) 
    {
        if (_phno[i] < '0' || _phno[i] > '9') // check whether all characters are digits
            return 0;
    }
    // check for duplicates
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(_phno,addressBook->contacts[i].phone) == 0) 
        {
            printf("Entered number already matches an existing contact\n");
            return 0;
        }
    }
    return 1;
}

//FUNCTION TO VALIDATE EMAIL.ID
int validate_email(char emailid[],AddressBook* addressBook)
{
    char emailid1[100];
    strcpy(emailid1,emailid);
    char* token;
    //Validating the local part 
    if(!strchr(emailid1,'@'))
    {
        return 0;
    }
    else
    {
        token = strtok(emailid1,"@");
        if(strlen(token)==0)
        {
            return 0;
        }
        else
        {
            for(int i = 0;i<strlen(token);i++)
            {
                if(token[i] >= '0' && token[i] <= '9' || token[i] >= 'a' && token[i] <= 'z' || token[i] >= 'A' && token[i] <= 'Z' || token[i] == '.' || token[i] == '_' || token[i] == '+' || token[i] == '-')
                {
                    if(token[0] == '.' || token[strlen(token)-1] == '.' || token[i] == '.' && token[i+1]== '.' || token[i] == ' ')
                    {
                        return 0;
                    }
                }
            }
        }
    }
    //Validating the domain part
    token = strtok(NULL,"@");
    if(token == NULL)
        return 0;
    if(!strchr(token,'.'))
    {
        return 0;
    }
    else
    {
        token=strtok(token,".");
        if(strlen(token)==0)
        {
            return 0;
        }
        else
        {
            for(int i=0;i<strlen(token);i++)
            {
                if(token[i] >= '0' && token[i] <= '9' || token[i] >= 'a' && token[i] <= 'z' || token[i] >= 'A' && token[i] <= 'Z'  || token[i] == '-')
                {
                    if(token[0] == '-' || token[strlen(token)-1] == '-')
                    {
                        return 0;
                    }
                }
            }
        }
    }
    token=strtok(NULL,".");
    if(token == NULL)
        return 0;
    if(strlen(token) < 2)
    {
        return 0;
    }
    else
    {
        for(int i = 0;i<strlen(token);i++)
        {
            if(token[i] >= 'a' && token[i] <= 'z' || token[i] >= 'A' && token[i] <= 'Z')
            {}
            else
            return 0;
        }
    }
    // checking for duplicates
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(emailid,addressBook->contacts[i].email) == 0) 
        {
            printf("Entered mail id already matches an existing contact\n");
            return 0;
        }
    }
    return 1;
}

//FUNCTION FOR SEARCHING BY NAME
void namesearch(AddressBook* addressbook)
{
    char name[50];
    int found=0;
    printf("enter the name:\n");
    scanf(" %[^\n]",name); //user enters the name to search
    for(int i=0;i<addressbook->contactCount;i++)
    {
        if(strcasecmp(name,addressbook->contacts[i].name)==0) // if name present strcasecmp returns 0
        {
            found++;
            printf("%s %s %s\n",addressbook->contacts[i].name,addressbook->contacts[i].phone,addressbook->contacts[i].email);
        }
    }
    if(!found) //if there is no match found = 0 
    {
        printf("contact not found\n");
    }
}

//FUNCTION FOR SEARCHING BY PHONE NUMBER
void phonenosearch(AddressBook* addressbook)
{
    char phone[20];
    printf("enter the phone number:\n");
    int found=0;
    scanf("%s",phone); //user enters the phone number to search
    for(int i=0;i<addressbook->contactCount;i++)
    {
        if(strcmp(phone,addressbook->contacts[i].phone)==0) // if phone number present strcasecmp return 0
        {
            found++;
            printf("%s %s %s",addressbook->contacts[i].name,addressbook->contacts[i].phone,addressbook->contacts[i].email);
        }
    }
    if(!found) //if there is no match found = 0 
    {
        printf("Contact not found\n");
    }
}

//FUNCTION FOR SEARCHING BY EMAILID
void emailidsearch(AddressBook* addressbook)
{
    char email[20]; 
    printf("enter the email id:\n");
    int found=0;
    scanf("%s",email); //user enters the mailid to search
    for(int i=0;i<addressbook->contactCount;i++)
    {
        if(strcasecmp(email,addressbook->contacts[i].email)==0) // if mail id present strcasecmp return 0
        {
            found++; //found increments
            printf("%s %s %s",addressbook->contacts[i].name,addressbook->contacts[i].phone,addressbook->contacts[i].email);
        }
    }
    if(!found) //if there is no match found = 0 
    {
        printf("contact not found\n");
    }
}

// EDITING
void editsearchname(AddressBook* addressbook)
{
    char name[50];
    int j=0;
    printf("Enter the name:\n");
    scanf(" %[^\n]",name); //user enters the name to search
    for(int i=0;i<addressbook->contactCount;i++) //loops over the contact list and searches if the given name exists in the array of structures
    {
        if(strcasecmp(name,addressbook->contacts[i].name)==0) // if name present strcasecmp returns 0
        {
            printf("%d.%s %s %s\n",++j,addressbook->contacts[i].name,addressbook->contacts[i].phone,addressbook->contacts[i].email);
            arr[j-1]=i; // the index of the contact in the array of structure is stored in arr.
        }
    }
    if(!j) //if there is no match ie, found = 0 
    {
        printf("contact not found\n");
    }
    if(j)
    {
        if(j == 1)
        {
            edit(addressbook,j);
        }
        if(j > 1)
        {
            int k;
            printf("\nChoose the contact you would like to edit.\n");
            scanf("%d",&k);
            if(k>j)
            {
                printf("invalid input\n");
            }
            else
            {
                edit(addressbook,k);
            }
        }
    }
}

void editsearchphone(AddressBook* addressbook)
{
    char phone[20];
    int j=0;
    printf("Enter the phone number :\n");
    scanf(" %s",phone); //user enters the phone to search
    for(int i=0;i<addressbook->contactCount;i++) //loops over the contact list and searches if the given phone number exists in the array of structures
    {
        if(strcmp(phone,addressbook->contacts[i].phone)==0) // if phone number present strcmp returns 0
        {
            printf("%d.%s %s %s\n",++j,addressbook->contacts[i].name,addressbook->contacts[i].phone,addressbook->contacts[i].email);
            arr[j-1]=i; // the index of the contact in the array of structure is stored in arr.
        }
    }
    if(!j) //if there is no match ie, found = 0 
    {
        printf("contact not found\n");
    }
    if(j)
    {
        if(j == 1)
        {
            edit(addressbook,j);
        }
    }
}


void editsearchmailid(AddressBook* addressbook)
{
    char mailid[20];
    int j=0;
    printf("Enter the Emailid :\n");
    scanf(" %s",mailid); //user enters the email id to search
    for(int i=0;i<addressbook->contactCount;i++) //loops over the contact list and searches if the given email id exists in the array of structures
    {
        if(strcmp(mailid,addressbook->contacts[i].email)==0) // if email id present strcmp returns 0
        {
            printf("%d.%s %s %s\n",++j,addressbook->contacts[i].name,addressbook->contacts[i].phone,addressbook->contacts[i].email);
            arr[j-1]=i; // the index of the contact in the array of structure is stored in arr.
        }
    }
    if(!j) //if there is no match ie, found = 0 
    {
        printf("contact not found\n");
    }
    if(j)
    {
        if(j == 1)
        {
            edit(addressbook,j);
        }
    }
}

void edit(AddressBook* addressbook,int j)
{
    int choice;
        do{
            printf("\nSelect the contact detail you want to edit\n");
            printf("1.Name\n");
            printf("2.Phone number\n");
            printf("3.Email id\n");
            printf("4.Back\n");

            scanf("%d",&choice);

            switch(choice)
            {
                case 1:
                editname(addressbook,j);
                break;
                case 2:
                editphoneno(addressbook,j);
                case 3:
                editemailid(addressbook,j);
                case 4:
                printf("Exiting...\n");
                default:
                printf("Invalid choice. Please try again.\n");
            }
        }while(choice != 4);
}

void editname(AddressBook* addressbook,int j)
{
    char newname[100];
    do{
    printf("Enter the new name :");
    scanf(" %[^\n]",newname);
    if(validate_name(newname))
    {
        strcpy(addressbook->contacts[arr[j-1]].name,newname);
        printf("Name has been updated\n");
    }
    else
    {
        printf("Error : please enter a valid name\n");
    }
    }while(!validate_name(newname));
}

void editphoneno(AddressBook* addressbook,int j)
{
    char newphoneno[20];
    do{
    printf("Enter the new phone number :");
    scanf(" %[^\n]",newphoneno);
    if(validate_phno(newphoneno,addressbook))
    {
        strcpy(addressbook->contacts[arr[j-1]].phone,newphoneno);
        printf("Phone number has been updated\n");
    }
    else
    {
        printf("Error : please enter a valid name\n");
    }
    }while(!validate_phno(newphoneno,addressbook));
}


void editemailid(AddressBook* addressbook,int j)
{
    char newemailid[50];
    do{
    printf("Enter the new email id :");
    scanf(" %[^\n]",newemailid);
    if(validate_email(newemailid,addressbook))
    {
        strcpy(addressbook->contacts[arr[j-1]].email,newemailid);
        printf("\nEmail has been updated\n");
    }
    else
    {
        printf("Error : please enter a valid name\n");
    }
    }while(!validate_email(newemailid,addressbook));
} 


//DELETING
void delete(AddressBook* addressbook,int j)
{
    int s = arr[j-1]; //assigning the index value to a variable s
    for (int i = s; i < addressbook->contactCount - 1; i++) 
    {
        addressbook->contacts[i] = addressbook->contacts[i + 1]; //leftshifting the values from the required index 
    }
    addressbook->contactCount--; // contact count get decremented once
    printf("Contact deleted\n");
}

void delsearchname(AddressBook* addressbook)
{
    char name[50];
    int j=0;
    printf("Enter the name:\n");
    scanf(" %[^\n]",name); //user enters the name to search
    for(int i=0;i<addressbook->contactCount;i++) //loops over the contact list and searches if the given name exists in the array of structures
    {
        if(strcasecmp(name,addressbook->contacts[i].name)==0) //if name present strcasecmp returns 0
        {
            printf("%d.%s %s %s\n",++j,addressbook->contacts[i].name,addressbook->contacts[i].phone,addressbook->contacts[i].email);
            arr[j-1]=i; // the index of the contact in the array of structure is stored in arr.
        }
    }
    if(!j) //if there is no match ie, found = 0 
    {
        printf("contact not found\n");
    }
    if(j)
    {
        if(j == 1)
        {
            delete(addressbook,j);
        }
        if(j > 1)
        {
            int k;
            printf("\nChoose the contact you would like to delete.\n");
            scanf("%d",&k);
            if(k>j)
            {
                printf("invalid input\n");
            }
            else
            {
                delete(addressbook,k);
            }
        }
    }
}  

void delsearchphone(AddressBook* addressbook)
{
    char phone[20];
    int j=0;
    printf("Enter the phone number :\n");
    scanf(" %s",phone); //user enters the phone to search
    for(int i=0;i<addressbook->contactCount;i++) //loops over the contact list and searches if the given phone number exists in the array of structures
    {
        if(strcmp(phone,addressbook->contacts[i].phone)==0) // if phone number present strcmp returns 0
        {
            printf("%d.%s %s %s\n",++j,addressbook->contacts[i].name,addressbook->contacts[i].phone,addressbook->contacts[i].email);
            arr[j-1]=i; // the index of the contact in the array of structure is stored in arr.
        }
    }
    if(!j) //if there is no match ie, found = 0 
    {
        printf("contact not found\n");
    }
    if(j)
    {
        if(j == 1)
        {
            delete(addressbook,j);
        }
    }
}

void delsearchmailid(AddressBook* addressbook)
{
    char mailid[20];
    int j=0;
    printf("Enter the Emailid :\n");
    scanf(" %s",mailid); //user enters the email id to search
    for(int i=0;i<addressbook->contactCount;i++) //loops over the contact list and searches if the given email id exists in the array of structures
    {
        if(strcmp(mailid,addressbook->contacts[i].email)==0) // if email id present strcmp returns 0
        {
            printf("%d.%s %s %s\n",++j,addressbook->contacts[i].name,addressbook->contacts[i].phone,addressbook->contacts[i].email);
            arr[j-1]=i; // the index of the contact in the array of structure is stored in arr.
        }
    }
    if(!j) //if there is no match ie, found = 0 
    {
        printf("contact not found\n");
    }
    if(j)
    {
        if(j == 1)
        {
            delete(addressbook,j);
        }
    }
}

