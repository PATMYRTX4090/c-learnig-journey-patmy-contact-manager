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
	for (int i = my_adressbook->size; i < my_adressbook->capacity; i++)
	{
		my_adressbook->contacts[i].active = false;
	}
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
	printf("Done.\n");
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
		printf("+-------------------------------------+\n");
		printf("| Do You want to add more contatcs ?  |\n");
		printf("|      Y - YES | N - NO               |\n");
		printf("+-------------------------------------+\n");
		ASKING;
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
		printf("ADDRESS BOOK FILE NAME: %s\n", my_addressbook->file_name);
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
		Sleep(TIME_SLEEP);
		return my_addressbook->contacts;
	}
	else
	{
		my_addressbook->contacts = ptr_temp;
		init_active(my_addressbook);
		Sleep(TIME_SLEEP);
		return my_addressbook->contacts;
	}
}

void delete_contact(AddressBook* my_addressbook)
{
	if (my_addressbook != NULL && my_addressbook->size > 0)
	{
		printf("+----------------------------+\n");
		printf("|  List of avaible contats:  |\n");
		printf("+----------------------------+\n");
		view_struct(my_addressbook);
		bool delete = true;
		//bool check = true;
		int id_delete;
		while (delete)
		{
			printf("To delelete contact, enter a ID number.\n");
			ASKING;
			id_delete = check_id(my_addressbook);
			printf("+---+--------------------+------------------------------+--------------------+--------------------------------------------+--------------------------+\n");
			printf("|%3d|%-20s|%-30s|%-20s|%-44s|%-26s|\n", 
				my_addressbook->contacts[id_delete - 1].ID,	
				my_addressbook->contacts[id_delete - 1].name, 
				my_addressbook->contacts[id_delete - 1].last_name, 
				my_addressbook->contacts[id_delete - 1].phone_number, 
				my_addressbook->contacts[id_delete - 1].email_address, 
				my_addressbook->contacts[id_delete - 1].company);
			printf("+---+--------------------+------------------------------+--------------------+--------------------------------------------+--------------------------+\n");
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
			if (my_addressbook->size > 0)
			{
				view_struct(my_addressbook);
				printf("+-----------------------------------------------+\n");
				printf("| Do You want to delete another contact ?       |\n");
				printf("|            Y - YES | N - NO                   |\n");
				printf("+-----------------------------------------------+\n");
				ASKING;
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
			else if (my_addressbook->size == 0)
			{
				printf("Address Book is empty!\n");
				printf("Returning to Main Menu.\n");
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

void search_contacts_main(AddressBook* my_addressbook)
{
	if (my_addressbook != NULL && my_addressbook->size > 0)
	{
		bool still_searching = true;
		while (still_searching)
		{
			printf("+------------------------------------------------+\n");
			printf("| +--------------------------------------------+ |\n");
			printf("| |     Search in Adress Book                  | |\n");
			printf("| |     Available options below:               | |\n");
			printf("| |                                            | |\n");
			printf("| |     1. Search by all                       | |\n");
			printf("| |     2. Search by name                      | |\n");
			printf("| |     3. Search by last name                 | |\n");
			printf("| |     4. Search by phone number              | |\n");
			printf("| |     5. Search by email address             | |\n");
			printf("| |     6. Search by company                   | |\n");
			printf("| |     0. Exit                                | |\n");
			printf("| +--------------------------------------------+ |\n");
			printf("+------------------------------------------------+\n");
			ASKING;
			int search_by = taking_number();
			switch (search_by)
			{
			case 0:
				printf("+--------------------------------------+\n");
				printf("|  I am leaving the search options.    |\n");
				printf("|  Returning to Main Menu.             |\n");
				printf("+--------------------------------------+\n");
				Sleep(TIME_SLEEP);
				still_searching = false;
				break;
			case 1:
				search_by_all_Contacts(my_addressbook, 0, ask_letter_case());
				break;
			case 2:
				search_by_Contacts(my_addressbook, 0, ask_letter_case());
				break;
			case 3:
				search_by_Contacts(my_addressbook, 1, ask_letter_case());
				break;
			case 4:
				search_by_Contacts(my_addressbook, 2, ask_letter_case());
				break;
			case 5:
				search_by_Contacts(my_addressbook, 3, ask_letter_case());
				break;
			case 6:
				search_by_Contacts(my_addressbook, 4, ask_letter_case());
				break;
			default:
				printf("+--------------------------------------+\n");
				printf("|    Please chose right option!        |\n");
				printf("+--------------------------------------+\n");
				break;
			}
		}
	}
	else
	{
		printf("+-------------------------------------+\n");
		printf("|    No contacts available.           |\n");
		printf("|    There is nothing to search.      |\n");
		printf("|    Returning to Main Menu.          |\n");
		printf("+-------------------------------------+\n");
		Sleep(TIME_SLEEP);
	}
}

char ask_letter_case(void)
{
	printf("+-----------------------------------+\n");
	printf("|  Should capitalization matter ?   |\n");
	printf("|        Y - YES | N - NO           |\n");
	printf("+-----------------------------------+\n");
	char ask;
	bool loop_me = true;
	while (loop_me)
	{
		if ((ask = get_letter()) == YES || ask == NO)
		{
			loop_me = false;
		}
		else
		{
			WRONG;
			NEW_LINE;
			TRY;
			NEW_LINE;
			ASKING;
		}
	}
	return ask;
}

void view_result_struct(const AddressBook* my_addressbook, int *ScoreBoard, int SizeScoreBoard)
{
	printf("LIST OF FOUND CONTACTS: %d\n", SizeScoreBoard);
	printf("+---+--------------------+------------------------------+--------------------+--------------------------------------------+--------------------------+\n");
	printf("|%3s|%-20s|%-30s|%-20s|%-44s|%-26s|\n", "ID ", "NAME", "LAST NAME", "PHONE NUMBER", "EMAIL ADRESS", "COMPANY");
	printf("+---+--------------------+------------------------------+--------------------+--------------------------------------------+--------------------------+\n");
	for (int i = 0; i < SizeScoreBoard; i++)
	{
		printf("|%3d|%-20s|%-30s|%-20s|%-44s|%-26s|\n", 
			my_addressbook->contacts[*(ScoreBoard + i)].ID, 
			my_addressbook->contacts[*(ScoreBoard + i)].name, 
			my_addressbook->contacts[*(ScoreBoard + i)].last_name, 
			my_addressbook->contacts[*(ScoreBoard + i)].phone_number, 
			my_addressbook->contacts[*(ScoreBoard + i)].email_address, 
			my_addressbook->contacts[*(ScoreBoard + i)].company);
		printf("+---+--------------------+------------------------------+--------------------+--------------------------------------------+--------------------------+\n");
	}
}

void search_by_Contacts(AddressBook *my_addressbook, int field_number, char letter_case)
{
	int SizeScoreBoard = 0;
	int* ScoreBoard = NULL;
	char* searched_structure_field = NULL;
	char strSearch[MAX_NAME];
	ScoreBoard = (int*)malloc(sizeof(int) * my_addressbook->size);
	if (ScoreBoard == NULL)
	{
		printf("+--------------------------------------+\n");
		printf("|    Error with malloc!                |\n");
		printf("|    Returning to Search Menu.         |\n");
		printf("+--------------------------------------+\n");
		Sleep(TIME_SLEEP);
	}
	else
	{
		printf("+-----------------------------------------------+\n");
		printf("|    Add string, that You want to search for:   |\n");
		printf("+-----------------------------------------------+\n");
		read_string(strSearch, MAX_NAME);
		if (letter_case == NO)
		{
			char* UpperStrSearch = (char*)malloc(sizeof(char) * (strlen(strSearch) + 1));
			char UpperContactName[MAX_NAME] = { '\0' };
			if (UpperStrSearch == NULL)
			{
				printf("+--------------------------------------+\n");
				printf("|    Error with malloc!                |\n");
				printf("|    Returning to Search Menu.         |\n");
				printf("+--------------------------------------+\n");
				Sleep(TIME_SLEEP);
				exit(EXIT_FAILURE);
			}
			else
			{
				for (int x = 0; x <= strlen(strSearch); x++)
				{
					UpperStrSearch[x] = toupper(*(strSearch + x));
				}
				for (int i = 0; i < my_addressbook->size; i++)
				{
					searched_structure_field = selecting_right_field(my_addressbook, field_number, i);
					for (int k = 0; k < strlen(searched_structure_field); k++)
					{
						UpperContactName[k] = toupper(searched_structure_field[k]);
					}
					if (strstr(UpperContactName, UpperStrSearch))
					{
						*(ScoreBoard + SizeScoreBoard) = i;
						SizeScoreBoard++;
					}
				}
			}
			free(UpperStrSearch);
		}
		else
		{
			for (int i = 0; i < my_addressbook->size; i++)
			{
				searched_structure_field = selecting_right_field(my_addressbook, field_number, i);
				if (strstr(searched_structure_field, strSearch))
				{
					*(ScoreBoard + SizeScoreBoard) = i;
					SizeScoreBoard++;
				}
			}
		}
		view_result_struct(my_addressbook, ScoreBoard, SizeScoreBoard);
	}
	free(ScoreBoard);
}

char* selecting_right_field(AddressBook* my_addressbook, int field_number, int i)
{
	char* ssf = NULL;
	switch (field_number)
	{
	case SEARCH_NAME:
		ssf = my_addressbook->contacts[i].name;
		break;
	case SEARCH_LAST_NAME:
		ssf = my_addressbook->contacts[i].last_name;
		break;
	case SEARCH_PHONE_NUMEBER:
		ssf = my_addressbook->contacts[i].phone_number;
		break;
	case SEARCH_EMAIL_ADDRESS:
		ssf = my_addressbook->contacts[i].email_address;
		break;
	case SEARCH_COMPANY:
		ssf = my_addressbook->contacts[i].company;
		break;
	}
	return ssf;
}

void search_by_all_Contacts(AddressBook* my_addressbook, int field_number, char letter_case)
{
	int SizeScoreBoard = 0;
	int* ScoreBoard = NULL;
	char* searched_structure_field = NULL;
	char strSearch[MAX_NAME];
	ScoreBoard = (int*)malloc(sizeof(int) * my_addressbook->size);
	if (ScoreBoard == NULL)
	{
		printf("+--------------------------------------+\n");
		printf("|    Error with malloc!                |\n");
		printf("|    Returning to Search Menu.         |\n");
		printf("+--------------------------------------+\n");
		Sleep(TIME_SLEEP);
	}
	else
	{
		printf("+-----------------------------------------------+\n");
		printf("|    Add string, that You want to search for:   |\n");
		printf("+-----------------------------------------------+\n");
		read_string(strSearch, MAX_NAME);
		if (letter_case == NO)
		{
			char* UpperStrSearch = (char*)malloc(sizeof(char) * (strlen(strSearch) + 1));
			char UpperContactName[MAX_NAME] = { '\0' };
			if (UpperStrSearch == NULL)
			{
				printf("+--------------------------------------+\n");
				printf("|    Error with malloc!                |\n");
				printf("|    Returning to Search Menu.         |\n");
				printf("+--------------------------------------+\n");
				Sleep(TIME_SLEEP);
				exit(EXIT_FAILURE);
			}
			else
			{
				for (int x = 0; x <= strlen(strSearch); x++)
				{
					UpperStrSearch[x] = toupper(*(strSearch + x));
				}
				for (int i = 0; i < my_addressbook->size; i++)
				{
					for (int y = 0; y < LIMIT_FIELDS; y++)
					{
						searched_structure_field = all_fields_in_array(my_addressbook, i, y);
						for (int k = 0; k < strlen(searched_structure_field); k++)
						{
							UpperContactName[k] = toupper(searched_structure_field[k]);
						}
						if (strstr(UpperContactName, UpperStrSearch))
						{
							*(ScoreBoard + SizeScoreBoard) = i;
							SizeScoreBoard++;
							break;
						}
					}
				}
			}
			free(UpperStrSearch);
		}
		else
		{
			for (int i = 0; i < my_addressbook->size; i++)
			{
				for (int field_number = SEARCH_NAME; field_number <= SEARCH_COMPANY; field_number++)
				{
					searched_structure_field = selecting_right_field(my_addressbook, field_number, i);
					if (strstr(searched_structure_field, strSearch))
					{
						*(ScoreBoard + SizeScoreBoard) = i;
						SizeScoreBoard++;
					}
				}
			}
		}
		view_result_struct(my_addressbook, ScoreBoard, SizeScoreBoard);
	}
	free(ScoreBoard);
}

char* all_fields_in_array(AddressBook* my_addressbook, int i, int y)
{
	char* ssf_name = my_addressbook->contacts[i].name;
	char* ssf_last_name = my_addressbook->contacts[i].last_name;
	char* ssf_phone_number = my_addressbook->contacts[i].phone_number;
	char* ssf_email_address = my_addressbook->contacts[i].email_address;
	char* ssf_company = my_addressbook->contacts[i].company;

	char* ssf_all[LIMIT_FIELDS] = { ssf_name, ssf_last_name, ssf_phone_number, ssf_email_address, ssf_company };
	return ssf_all[y];
}