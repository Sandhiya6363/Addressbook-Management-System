#include <stdio.h>
#include "contact.h"


int main() 
{
    int choice;
    AddressBook addressBook;

    addressBook.contactCount = 0;
    initialize(&addressBook); // Initialize the address book
    printf("\n<==============Addressbook Menu==============>\n");
    do 
    {
        
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save and Exit\n");		
        printf("7. Exit without Saving\n");
        printf("Enter your choice: ");
         

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");

            while (getchar() != '\n')
                ;

            continue;
        }


    

        
        switch (choice) 
        {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5: 
                listContacts(&addressBook);
                break;
            case 6:
                printf("Save and Exiting...\n");
                saveContactsToFile(&addressBook);
                return 0;
            case 7:
                printf("Exit without saving\n");
                return 1;
            default:
                printf("Invalid choice. Please try again.\n");

        }
    } while (choice != 7);
    
    return 0;
}
