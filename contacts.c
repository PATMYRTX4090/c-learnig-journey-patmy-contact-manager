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
			init_active(my_addressbook);
		}
	}
	return my_addressbook;
}

void init_active(AddressBook* my_adressbook)
{
	int j = 0;
	for (int i = my_adressbook->size; i < my_adressbook->capacity; i++)
	{
		my_adressbook->contacts[i].active = false;
		j++;
	}
	printf("Count of my_adressbook->contacts[i].active = false: %d\n", j);
}

void cleanup_struct(AddressBook *my_addressbook)
{
	free(my_addressbook->contacts);
	my_addressbook->contacts = NULL;
	free(my_addressbook);
	my_addressbook = NULL;
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
				wsk_current_contacts = more_contacts(my_addressbook);
			}
			else
			{
				wsk_current_contacts++;
				add = true;
			}
		}
		else
		{
			if (my_addressbook->size == my_addressbook->capacity)
			{
				wsk_current_contacts = more_contacts(my_addressbook);
			}
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

Contact *more_contacts(AddressBook* my_addressbook)
{
	Contact* ptr_temp;
	my_addressbook->capacity *= 2;
	ptr_temp = (Contact*)realloc(my_addressbook->contacts, my_addressbook->capacity * sizeof(Contact));
	if (ptr_temp == NULL)
	{
		printf("Error with realloc() !\n");
		return my_addressbook->contacts;
		Sleep(TIME_SLEEP);
	}
	else
	{
		my_addressbook->contacts = ptr_temp;
		init_active(my_addressbook);
		return my_addressbook->contacts;
		Sleep(TIME_SLEEP);
	}
}

void delete_contact(AddressBook* my_addressbook)
{
	if (my_addressbook != NULL && my_addressbook->size > 0)
	{
		printf("List of avaible contats:\n");
		view_struct(my_addressbook);
		bool delete = true;
		//bool check = true;
		int id_delete;
		while (delete)
		{
			printf("To delelete contact, enter a ID number:\n");
			id_delete = check_id(my_addressbook);
			printf("+---+--------------------+------------------------------+--------------------   +--------------------------------------------+--------------------------+\n");
			printf("|%3d|%-20s|%-30s|%-20s|%-44s|%-26s|\n", 
				my_addressbook->contacts[id_delete - 1].ID,	
				my_addressbook->contacts[id_delete - 1].name, 
				my_addressbook->contacts[id_delete - 1].last_name, 
				my_addressbook->contacts[id_delete - 1].phone_number, 
				my_addressbook->contacts[id_delete - 1].email_address, 
				my_addressbook->contacts[id_delete - 1].company);
			printf("+---+--------------------+------------------------------+--------------------   +--------------------------------------------+--------------------------+\n");
			for (int i = (id_delete - 1); i < my_addressbook->size - 1; i++)
			{
				memcpy_s(&my_addressbook->contacts[i], sizeof(Contact), &my_addressbook->contacts[i +	1], sizeof(Contact));
			}
			my_addressbook->contacts[my_addressbook->size - 1].active = false;
			my_addressbook->size -= 1;
			for (int i = 0, j = 1; i < my_addressbook->size; i++, j++)
			{
				my_addressbook->contacts[i].ID = j;
			}
			view_struct(my_addressbook);
			printf("Do You want to delete another contact ?\n");
			printf("Y - YES | N - NO \n");
			char ask;
			if ((ask = get_letter()) == 'Y')
			{
				delete = true;
			}
			else
			{
				delete = false;
			}
		}
	}
	else
	{
		printf("No contacts available.\n");
		printf("Returning to Main Menu.\n");
		Sleep(TIME_SLEEP);
	}
}

int check_id(AddressBook *my_addressbook)
{
	int id_delete = taking_number();
	bool check = true;
	while (check)
	{
		if (id_delete > 0 && id_delete <= my_addressbook->size)
		{
			printf("This contact will be deleted:\n");
			check = false;
		}
		else
		{
			printf("Enter valid ID number !\n");
			id_delete = taking_number();
			continue;
		}
	}
	return id_delete;
}