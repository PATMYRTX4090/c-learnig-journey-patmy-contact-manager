#include "contact_manager.h"

void eat_char(void)
{
	while (getchar() != '\n')
	{
		continue;
	}
}

int taking_number(void)
{
	int Number;
	while (scanf_s("%d", &Number) != 1)
	{
		printf("Enter a digit!\n");
	}
	eat_char();
	return Number;
}

char get_letter(void)
{
	int ch;
	ch = getchar();
	eat_char();
	return ch;
}

char* read_string(char* Table, int T_Size)
{
	char* Adres_Lancucha;
	Adres_Lancucha = fgets(Table, T_Size, stdin);
	if (Adres_Lancucha)
	{
		while (*Table != '\n' && *Table != '\0')
		{
			Table++;
		}
		if (*Table == '\n')
		{
			*Table = '\0';
		}
		else
		{
			while (getchar() != '\n')
			{
				continue;
			}
		}
	}
	return Adres_Lancucha;
}

AddressBook* init_struct()
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
			printf("Success!\n");
			my_addressbook->size = 0;
			my_addressbook->capacity = START_CAPACITY;
			my_addressbook->is_modifed = false;
			strcpy_s(my_addressbook->file_name, MAX_FILENAME, FILE_NAME);
		}
	}
	return my_addressbook;
}

void cleanup_struct(AddressBook *my_addressbook)
{
	free(my_addressbook->contacts);
	free(my_addressbook);
	printf("Deallocation: \n");
	printf("my_addressbook->contacts,\n");
	printf("my_addressbook\n");
	printf("complete.\n");
	Sleep(TIME_SLEEP);
}

void complete_struct(AddressBook *my_addressbook)
{
	char ask = 'N';
	bool add = false;
	Contact* wsk_current_contacts;
	wsk_current_contacts = my_addressbook->contacts;
	do
	{
		while (wsk_current_contacts->active == true)
		{
			wsk_current_contacts++;
		}
		my_addressbook->size++;
		my_addressbook->is_modifed = true;
		wsk_current_contacts->ID = my_addressbook->size;
		printf("ID contact number: %d\n", wsk_current_contacts->ID);
		printf("Please enter name:\n");
		read_string(wsk_current_contacts->name, MAX_NAME);
		printf("Please enter last name:\n");
		read_string(wsk_current_contacts->last_name, MAX_NAME);
		printf("Please enter phone number:\n");
		read_string(wsk_current_contacts->phone_number, MAX_PHONE);
		printf("Please enter email adress:\n");
		read_string(wsk_current_contacts->email_address, MAX_EMAIL);
		printf("Please enter company name:\n");
		read_string(wsk_current_contacts->company, MAX_NAME);
		wsk_current_contacts->active = true;
		printf("Contact have been activated !\n");
		printf("Do You want to add more contatcs ?\n");
		printf("Y - YES | N - NO \n");
		if ((ask = get_letter()) == 'Y')
		{
			if (my_addressbook->size == my_addressbook->capacity)
			{
				my_addressbook->capacity = START_CAPACITY * my_addressbook->size;
				my_addressbook->contacts = (Contact*)realloc(my_addressbook->contacts, my_addressbook->capacity * sizeof(Contact));
				wsk_current_contacts = my_addressbook->contacts;
				add = true;
				if (my_addressbook->contacts == NULL)
				{
					printf("Error with realloc() !\n");
					Sleep(TIME_SLEEP);
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				wsk_current_contacts++;
				add = true;
			}
		}
		else
		{
			add = false;
		}

	} while (add);
	printf("Contacts adding is completed\n");
	Sleep(TIME_SLEEP);
}

void view_struct(const AddressBook *my_addressbook)
{
	if (my_addressbook == NULL)
	{
		printf("No contacts available.\n");
		Sleep(TIME_SLEEP);
	}
	else
	{
		printf("LIST OF %d CONTACTS\n", my_addressbook->size);
		printf("+---+--------------------+------------------------------+--------------------+--------------------------------------------+--------------------------+\n");
		printf("|%3s|%-20s|%-30s|%-20s|%-44s|%-26s|\n", "ID ", "NAME", "LAST NAME", "PHONE NUMBER", "EMAIL ADRESS", "COMPANY");
		printf("+---+--------------------+------------------------------+--------------------+--------------------------------------------+--------------------------+\n");
		for (int i = 0; i < my_addressbook->size; i++)
		{
			printf("|%3d|%-20s|%-30s|%-20s|%-44s|%-26s|\n", my_addressbook->contacts[i].ID, my_addressbook->contacts[i].name, my_addressbook->contacts[i].last_name, my_addressbook->contacts[i].phone_number, my_addressbook->contacts[i].email_address, my_addressbook->contacts[i].company);
			printf("+---+--------------------+------------------------------+--------------------+--------------------------------------------+--------------------------+\n");
		}
		printf("%s\n", my_addressbook->file_name);
	}
}