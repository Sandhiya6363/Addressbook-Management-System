/*Done by Sandhiya.S
Developed a menu-driven **Address Book Management System in C** to add, search, edit, delete, and display contacts. 
Implemented **structures, string handling, validation, sorting, and file handling** for efficient contact management.

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"

void listContacts(AddressBook *addressBook)
{
    Contact temp;

    if (addressBook->contactCount == 0)
    {
        printf("No Contacts found.\n");
        return;
    }

    // Sort contacts based on name
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++)
        {
            if (strcmp(addressBook->contacts[j].name,
                       addressBook->contacts[j + 1].name) > 0)
            {
                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }

    // Print table
    printf("+------+----------------------+----------------+------------------------------------------+\n");
    printf("| %-4s | %-20s | %-14s | %-40s |\n",
           "S.NO", "Name", "Phone", "Email");
    printf("+------+----------------------+----------------+------------------------------------------+\n");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("| %-4d | %-20s | %-14s | %-40s |\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    printf("+------+----------------------+----------------+------------------------------------------+\n");
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    if(addressBook->contactCount >=MAX_CONTACTS)
    {
        printf("AddressBook is full!\n");
        return;
    }
	
    //create a new contact
    char name[30], phone[20], email[30];
    int res;
    printf("<-----Create contact------>\n");
    do{
        printf("Enter the name : ");
        scanf(" %[^\n]", name);

        res = validate_name(name);

    }while(res == 0);
   
    int ret;
    do{
    printf("Enter the phone : ");
    scanf("%s", phone);

    ret= validate_phone(phone);
    if(ret==1)
    {
        ret=unique_phone(addressBook,phone,-1);
        if(ret==0)
        {
        printf("Phone number already Exists.\n");
        }
    }
    else
    {
        printf("Invalid Phone Number! Please enter exactly 10 Digits\n");
    }

    }while(ret == 0);

    int ver;
    do{
    printf("Enter the email : ");
    scanf("%s", email);

    ver=validate_email(email);
    if(ver==1)
    {
        ver= unique_email(addressBook,email,-1);
        if(ver==0)
        {
            printf("Email already exists.\n");
        }
    }
    else
    {
        printf("Invalid Email!Please enter correctly.\n");
    }
    }while(ver==0);


    strcpy(addressBook->contacts[addressBook->contactCount].name,name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email,email);
    printf("Contact created successfully....\n");


    addressBook->contactCount++;
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */

    int choice;
    printf("1.Search by name\n2.Search by phone\n3.Search by Email\n");
    printf("Enter your choice: ");

    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            search_by_name(addressBook);
            break;
        case 2:
            search_by_phone(addressBook);
            break;
        case 3:
            search_by_email(addressBook);
            break;
        default:
            printf("Invalid Choice!\n");
            return;
    }

}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int choice;
    printf("1.Search by name\n2.Search by phone\n3.Search by Email");
   
    printf("\nEnter your Choice:");
    scanf("%d", &choice);
    int index;
    int op;
    char name[30], phone[20], email[30];

    switch(choice)
    {
        case 1:
            index = search_by_name(addressBook);
            break;
        case 2:
            index=search_by_phone(addressBook);
            break;
        case 3:
            index= search_by_email(addressBook);
            break;
        default:
            printf("Invalid Choice!\n");
            return;
    }
    if(index==-1)
    {
        printf("Contact not found!");
        return ;
    }

    printf("Contact Found!");
    printf("What do you want to edit?...\n");
    printf("1.Name\n2.Phone Number\n3.Email Id\n");
    printf("Choose the above option:");
    scanf("%d",&op);

    switch(op)
    {
        case 1:
        int res;
        do{
        printf("Enter the name : ");
        scanf(" %[^\n]", name);

        res = validate_name(name);

       }while(res == 0);
        strcpy(addressBook->contacts[index].name,name);
        break;

        case 2:
        int ret;
        do{
        printf("Enter the phone : ");
        scanf("%s", phone);

        ret= validate_phone(phone);
        if(ret==1)
        {
        ret=unique_phone(addressBook,phone,index);
        if(ret==0)
        {
        printf("Phone number already Exists.\n");
        }
        }
        else
        {
        printf("Invalid Phone Number! Please enter exactly 10 Digits\n");
        }

        }while(ret == 0);
        strcpy(addressBook->contacts[index].phone,phone);
        break;
      
    case 3:
    int ver;
    do{
    printf("Enter the email : ");
    scanf("%s", email);

    ver=validate_email(email);
    if(ver==1)
    {
        ver= unique_email(addressBook,email,index);
        if(ver==0)
        {
            printf("Email already exists.\n");
        }
    }
    else
    {
        printf("Invalid Email!Please enter correctly.\n");
    }
    }while(ver==0);
    strcpy(addressBook->contacts[index].email,email);
    break;

    default:
    printf("Invalid Choice!\n");
    return;


    }
    printf("Contact Updated Successfully!\n");

    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */

    int choice;
    printf("1.Search by name\n2.Search by phone\n3.Search by Email");
   

    scanf("%d", &choice);
    int index;
    
    

    switch(choice)
    {
        case 1:
            index = search_by_name(addressBook);
            break;
        case 2:
            index=search_by_phone(addressBook);
            break;
        case 3:
            index= search_by_email(addressBook);
            break;
        default:
            printf("Invalid Choice!\n");
            return;
    }
    if(index==-1)
    {
        printf("Contact not found!");
        return;
    }
    char confirm;
    printf("Are you sure to delete this contact?(Y/N)");
    scanf(" %c",&confirm);
    if(confirm=='Y'||confirm=='y')
    {
     for(int i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    // Decrease contact count
    addressBook->contactCount--;

    printf("Contact deleted successfully!\n");
    }
    else if(confirm=='N'|| confirm=='n')
    {
        printf("Contact deletion cancelled.\n");
    }
    else{
        printf("Invalid choice.Contact not deleted.\n");
    }
   
}




int validate_name(char *name)
{
    for(int i = 0; name[i]; i++)
    {
        if(!((name[i] >= 'A' && name[i] <= 'Z') || name[i] == ' ' || name[i]>='a' && name[i]<='z' || name[i]=='.'))
        {
            printf("Invalid name\n");
            return 0; 
        }
    }

    return 1; 
}
int validate_phone(char *phone)
{
    if(strlen(phone)!=10)
        return 0;
    for(int i = 0; phone[i]; i++)
    {
        
        if(!(phone[i] >= '0' && phone[i] <= '9'))
        {
            printf("Invalid number\n");
            return 0; // invalid
        }
    }

    return 1; // valid
}

int unique_phone(AddressBook *addressBook,char phone[],int index)
{
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(i !=index &&strcmp(addressBook->contacts[i].phone,phone)==0)
        {
        return 0;
        }
    }
    return 1;
}

int validate_email(char *email)
{
    int at=0,dot=0;
    if(!(email[0]>='a' && email[0]<='z'))
    return 0;
    for(int i=0;email[i]!='\0';i++)
    {
    if((email[i]>='a' && email[i]<='z') || (email[i] >='0' && email[i]<='9'))
    {
      continue;
    }
    else if(email[i] == '@')
    {
        at++;
    }
    else if(email[i]=='.')
    {
        dot++;
    }
    else
    {
    return 0;
    }

}
return(at==1 && dot>=1);
}

int unique_email(AddressBook *addressBook,char email[],int index)
{
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(i !=index && strcmp(addressBook->contacts[i].email,email)==0)
        return 0;
    }
    return 1;
}

int search_by_name(AddressBook *addressBook)
{
    char str[30];
    int count = 0;
    int index= -1;

   
    printf("Enter the name to search:");
    scanf(" %[^\n]",str);

  
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if (strcmp(str,addressBook->contacts[i].name)==0)
        {
            printf("%d. %-20s %-14s %-40s\n",i+1, addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            count++;
            index = i;
        }
    }

        if(count==0)
        {
            printf("Contacts not found.\n");
            return -1;
        }
        if(count>1)
        {
            int sno;
            printf("Multiple contacts found.\n");
            printf("Enter S.No to select contact:");
            scanf("%d",&sno);
            if(sno<1 || sno>addressBook->contactCount||strcmp(str,addressBook->contacts[sno-1].name)!=0)
            {
                printf("Invalid S.No\n");
                return -1;
            }
           index=sno-1; 
        }
        printf("Contacts found...\n");
        return index;

    
}


int search_by_phone(AddressBook *addressBook)
{
    char str[11];
    printf("Enter the phone number what you want to search:");
    scanf("%s",str);

    
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if (strcmp(str,addressBook->contacts[i].phone)==0)
        {
            printf("%-20s %-14s %-40s\n", addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            return i;
        }
    }
    printf("Phone Number not found.\n");
    return -1;
}

int search_by_email(AddressBook *addressBook)
{
    char str[50];
    printf("Enter the email ID to search:");
    scanf("%s",str);

    
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if (strcmp(str,addressBook->contacts[i].email)==0)
        {
            printf("%-20s %-14s %-40s\n", addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            return i;
        }
    }
    printf("Email ID not found.\n");
    return -1;
}

