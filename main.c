#include "contact_manager.h"

int main(void)
{
	printf("Welcome to the Address Book !\n");
	printf("Available options below:\n");
	printf("\n");
	printf("1. Add contact \n");
	printf("2. View contacts\n");
	printf("0. Exit\n");
	int options = taking_number();
	switch (options)
	{
	case 0:
		printf("Good bye !\n");
		Sleep(125);
		exit(EXIT_SUCCESS);
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}
	return 0;
}