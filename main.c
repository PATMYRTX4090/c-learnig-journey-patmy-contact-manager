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
		printf("+--------------------------------------------+\n");
		printf("|     Welcome to the Address Book !          |\n");
		printf("|     Available options below:               |\n");
		printf("|                                            |\n");
		printf("|     1. Add contact                         |\n");
		printf("|     2. View contacts                       |\n");
		printf("|     0. Exit                                |\n");
		printf("+--------------------------------------------+\n");
		int options = taking_number();
		switch (options)
		{
		case 0:
			printf("Good bye !\n");
			Sleep(250);
			if (my_addressbook != NULL)
			{
				cleanup_struct(my_addressbook);
			}
			working = false;
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
			break;
		case 4:
			break;
		default:
			break;
		}
	}
	return 0;
}