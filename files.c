#include "contact_manager.h"

AddressBook* init_struct_for_file()
{
	AddressBook* my_addressbook = (AddressBook*)malloc(sizeof(AddressBook));
	if (my_addressbook == NULL)
	{
		printf("Error with malloc() !\n");
		Sleep(TIME_SLEEP);
		exit(EXIT_FAILURE);
	}
	else
	{
		my_addressbook->contacts = (Contact*)malloc(sizeof(Contact) * START_CAPACITY);
		if (my_addressbook->contacts == NULL)
		{
			printf("Error with malloc() !\n");
			Sleep(TIME_SLEEP);
			exit(EXIT_FAILURE);
		}
		else
		{
			Sleep(TIME_SLEEP);
			printf("Success!\n");
		}
	}
	return my_addressbook;
}

void save_to_file_my_addressbook(AddressBook* my_addressbook)
{
	FILE* PLIK_TXT;
	if (fopen_s(&PLIK_TXT, FILE_NAME, "w+") != 0)
	{
		printf("Error!\n"); //---> DO ZMIANY...
		return;
	}
	fprintf(PLIK_TXT, "%-32s %-3d %-3d %-d\n", my_addressbook->file_name, my_addressbook->capacity, my_addressbook->size, my_addressbook->is_modifed);
	for (int i = 0; i < my_addressbook->size; i++)
	{

		fprintf(PLIK_TXT, "%-3d %-32s %-32s %-16s %-64s %-32s %-d\n",
			my_addressbook->contacts[i].ID, 
			my_addressbook->contacts[i].name, 
			my_addressbook->contacts[i].last_name, 
			my_addressbook->contacts[i].phone_number, 
			my_addressbook->contacts[i].email_address, 
			my_addressbook->contacts[i].company,
			my_addressbook->contacts[i].active);
	}
	fclose(PLIK_TXT);
}

AddressBook* read_from_file_my_addressbook()
{
	AddressBook* my_addressbook = init_struct_for_file();
	int temp_is_modifed;
	int temp_actvice;
	if (my_addressbook == NULL)
	{
		printf("Error!\n");
		exit(EXIT_FAILURE);
	}
	FILE* PLIK_TXT;
	if (fopen_s(&PLIK_TXT, FILE_NAME, "r") != 0)
	{
		printf("Error!\n"); //---> DO ZMIANY...
		exit(EXIT_FAILURE);
	}
	fscanf_s(PLIK_TXT, "%32s %3d %3d %d", my_addressbook->file_name, MAX_FILENAME, &my_addressbook->capacity, &my_addressbook->size, &temp_is_modifed);
	my_addressbook->is_modifed = temp_is_modifed;
	printf("+--------------------------------+\n");
	printf("| MY ADDRESS BOOK CAPACITY: %3d  |\n", my_addressbook->capacity); 
	printf("| MY ADDRESS BOOK SIZE    : %3d  |\n", my_addressbook->size);	   
	printf("+--------------------------------+\n");
	Sleep(TIME_SLEEP);
	for (int i = 0; i < my_addressbook->size; i++)
	{
		if (i == 0)
		{
			Contact* ptr_temp;
			ptr_temp = (Contact*)realloc(my_addressbook->contacts, my_addressbook->capacity * sizeof(Contact));
			if (ptr_temp == NULL)
			{
				printf("Error with realloc() !\n");
				Sleep(TIME_SLEEP);
				exit(EXIT_FAILURE);
			}
			else
			{
				my_addressbook->contacts = ptr_temp;
				Sleep(TIME_SLEEP);
			}
		}
		fscanf_s(PLIK_TXT, "%3d %32s %32s %16s %64s %32s %d\n",
			&my_addressbook->contacts[i].ID,
			my_addressbook->contacts[i].name, MAX_NAME,
			my_addressbook->contacts[i].last_name, MAX_NAME,
			my_addressbook->contacts[i].phone_number, MAX_PHONE,
			my_addressbook->contacts[i].email_address, MAX_EMAIL,
			my_addressbook->contacts[i].company, MAX_NAME,
			&temp_actvice);
		my_addressbook->contacts[i].active = temp_actvice;
	}
	fclose(PLIK_TXT);
	return my_addressbook;
}