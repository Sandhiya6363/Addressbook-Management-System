#include <stdio.h>
#include <string.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
    
    FILE *fp=fopen("contacts.csv","w");
    if(fp==NULL)
    {
        perror("");
        return;
    }
    fprintf(fp,"%d\n",addressBook->contactCount);
    for(int i=0;i<addressBook->contactCount;i++)
    {
     fprintf(fp,"%s,%s,%s\n", addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);
    printf("Contacts saved successfully!\n");
  
}

void loadContactsFromFile(AddressBook *addressBook) {
   

    FILE *fp = fopen("contacts.csv", "r");

    if (fp == NULL)
    {
        perror("File opening failed");
        return;
    }


    addressBook->contactCount =0;
    int count;
    fscanf(fp,"%d\n",&count);
    for(int i=0;i<count;i++)
    {
        char name[30],phone[20],email[50];
    if (fscanf(fp, "%[^,],%[^,],%[^\n]\n",name,phone,email)==3)
    {
        if(validate_phone(phone)==0)
        {
            printf("Invalid contact: %s- not loaded.\n",name);
            continue;
        }
        if(validate_name(name)==0)
        {
            printf("Invalid contact: %s -not loaded.\n",name);
            continue;
        }
        if(validate_email(email)==0)
        {
            printf("Invalid email: %s -not loaded.\n",name);
            continue;
        }
        strcpy(addressBook->contacts[addressBook->contactCount].name,name);
        strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
        strcpy(addressBook->contacts[addressBook->contactCount].email,email);
    
        addressBook->contactCount++;
    }
    }
    fclose(fp);
}

    

