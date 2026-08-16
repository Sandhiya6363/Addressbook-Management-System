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

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.csv", "r");

    if (fp == NULL)
    {
        perror("File opening failed");
        return;
    }

    int count;

    addressBook->contactCount = 0;

    // Read contact count
    if (fscanf(fp, "%d\n", &count) != 1)
    {
        printf("Invalid file format.\n");
        fclose(fp);
        return;
    }

    // Read contacts
    for (int i = 0; i < count; i++)
    {
        char name[30];
        char phone[20];
        char email[50];

        // Check address book capacity
        if (addressBook->contactCount >= MAX_CONTACTS)
        {
            printf("AddressBook is full. Remaining contacts not loaded.\n");
            break;
        }

        // Read one contact
        if (fscanf(fp, "%[^,],%[^,],%[^\n]\n",
                   name, phone, email) != 3)
        {
            printf("Invalid contact format. Contact not loaded.\n");
            continue;
        }

        // Validate name
        if (!validate_name(name))
        {
            printf(" Contact not loaded.\n");
            continue;
        }

        // Validate phone
        if (!validate_phone(phone))
        {
            printf("Invalid phone number: %s. Contact not loaded.\n", phone);
            continue;
        }

        // Validate email
        if (!validate_email(email))
        {
            printf("Invalid email: %s. Contact not loaded.\n", email);
            continue;
        }

        // Check duplicate phone
        if (!unique_phone(addressBook, phone, -1))
        {
            printf("Duplicate phone number: %s. Contact not loaded.\n", phone);
            continue;
        }

        // Check duplicate email
        if (!unique_email(addressBook, email, -1))
        {
            printf("Duplicate email: %s. Contact not loaded.\n", email);
            continue;
        }

        // Store valid contact
        strcpy(addressBook->contacts[addressBook->contactCount].name, name);
        strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
        strcpy(addressBook->contacts[addressBook->contactCount].email, email);

        addressBook->contactCount++;
    }

    fclose(fp);
}