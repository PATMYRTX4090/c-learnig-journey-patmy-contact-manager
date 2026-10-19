/*
	GLOBAL VARIABLES PROHIBITED !
*/

#include "contact_manager.h"

int main(void)
{
	bool working = true;
	AddressBook *my_addressbook = NULL;
	while (working)
	{
		printf("+---------------------------------------------------+\n");
		printf("| +-----------------------------------------------+ |\n");
		printf("| | +-------------------------------------------+ | |\n");
		printf("| | |     Welcome to the Address Book !         | | |\n");
		printf("| | |     Available options below:              | | |\n");
		printf("| | |                                           | | |\n");
		printf("| | |     1. Add contact                        | | |\n");
		printf("| | |     2. View contacts                      | | |\n");
		printf("| | |     3. Delete contacts                    | | |\n");
		printf("| | |     4. Search contacts                    | | |\n");
		printf("| | |     5. Edit contact                       | | |\n");
		printf("| | |     6. Write contacts to file             | | |\n");
		printf("| | |     7. Read contacts form file            | | |\n");
		printf("| | |     0. Exit                               | | |\n");
		printf("| | +-------------------------------------------+ | |\n");
		printf("| +-----------------------------------------------+ |\n");
		printf("+---------------------------------------------------+\n");
		ASKING;
		int options = taking_number();
		switch (options)
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
				my_addressbook = init_struct();
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
			my_addressbook = reading_struct_from_file_main();
			break;
		default:
			WRONG;
			break;
		}
	}
	return 0;
}