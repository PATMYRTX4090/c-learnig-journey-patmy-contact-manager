/*
	GLOBAL VARIABLES PROHIBITED ! TOTAL LINE CODE: 1600
*/

#include "contact_manager.h"

int main(void)
{
	bool working = true;
	AddressBook *my_addressbook = NULL;
	while (working)
	{
		printf("+-------------------------------------------------------------+\n");
		printf("| +---------------------------------------------------------+ |\n");
		printf("| | +-----------------------------------------------------+ | |\n");
		printf("| | |            Welcome to the Address Book !            | | |\n");
		printf("| | |            Available options below:                 | | |\n");
		printf("| | |                                                     | | |\n");
		printf("| | |            1. Add contact.                          | | |\n");
		printf("| | |            2. View contacts.                        | | |\n");
		printf("| | |            3. Delete contacts.                      | | |\n");
		printf("| | |            4. Search contacts.                      | | |\n");
		printf("| | |            5. Edit contact.                         | | |\n");
		printf("| | |            6. Write contacts to file.               | | |\n");
		printf("| | |            7. Read contacts from file.              | | |\n");
		printf("| | |            8. Change Address Book name.             | | |\n");
		printf("| | |            0. Exit.                                 | | |\n");
		printf("| | |                                                     | | |\n");
		printf("| | +-----------------------------------------------------+ | |\n");
		printf("| +---------------------------------------------------------+ |\n");
		printf("+-------------------------------------------------------------+\n");
		ASKING;
		int options;
		switch (options = taking_number())
		{
		case 0:
			if (my_addressbook != NULL)
			{
				is_struct_saved_to_file(my_addressbook);
				cleanup_struct(my_addressbook);
			}
			working = false;
			Sleep(250);
			printf("Good bye !\n");
			break;
		case 1:
			if (my_addressbook == NULL)
			{
				my_addressbook = init_struct_main(0);
				complete_struct(my_addressbook);
			}
			else
			{
				complete_struct(my_addressbook);
			}
			break;
		case 2:
			view_struct(my_addressbook);
			break;
		case 3:
			delete_contact(my_addressbook);
			break;
		case 4:
			search_contacts_main(my_addressbook, false);
			break;
		case 5:
			edit_contacts_main(my_addressbook);
			break;
		case 6:
			saving_struct_to_file_main(my_addressbook);
			break;
		case 7:
			if (my_addressbook == NULL)
			{
				my_addressbook = init_struct_main(1);
				reading_struct_from_file_main(my_addressbook);
			}
			else if (my_addressbook != NULL && my_addressbook->size > 0)
			{
				printf("+----------------------------------------------------------------------+\n");
				printf("|    Please note that the Address Book has already active contacts!    |\n");
				printf("|                 Number of active contacs: %5d                      |\n", my_addressbook->size);
				printf("|               Continuing will result in data lost.                   |\n");
				printf("|            Would You like to save existing Address Book              |\n");
				printf("|                                and                                   |\n");
				printf("|                   Load with new Address Book                         |\n");
				printf("|                                or                                    |\n");
				printf("|            Add more conttacts to existing Address Book ?             |\n");
				printf("|                      Avaible options below:                          |\n");
				printf("|                       S --> Save and Replace                         |\n");
				printf("|                       A --> Add more Contatcs                        |\n");
				printf("+----------------------------------------------------------------------+\n");
				ASKING;
				char question;
				switch (question =get_letter())
				{
				case 'S':
					save_to_file_semicolon_my_addressbook(my_addressbook);
					reading_struct_from_file_main(my_addressbook);
					break;
				case 'A':
					reading_from_file_add_to_my_adddressbook(my_addressbook);
					break;
				default:
					printf("+---------------------------------------+\n");
					printf("|  I am leaving the reading options.    |\n");
					printf("|       Returning to Main Menu.         |\n");
					printf("+---------------------------------------+\n");
					Sleep(TIME_SLEEP);
				}
			}
			break;
		case 8:
			change_my_addressbook_name(my_addressbook);
		case 9:
			check_capacity_size(my_addressbook);
			break;
		default:
			WRONG;
			NEW_LINE;
			break;
		}
	}
	return 0;
}