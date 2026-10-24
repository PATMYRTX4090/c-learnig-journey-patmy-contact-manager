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

AddressBook *init_struct_main(int type_init)
{
	AddressBook* my_addressbook = NULL;
	switch (type_init)
	{
	case 0:
		my_addressbook = (AddressBook*)malloc(sizeof(AddressBook));
		if (my_addressbook == NULL)
		{
			printf("+-------------------------------+\n");
			printf("|     Error with malloc() !     |\n");
			printf("|    Closing the application    |\n");
			printf("+-------------------------------+\n");
			Sleep(TIME_SLEEP);
			exit(EXIT_FAILURE);
		}
		else
		{
			my_addressbook->contacts = (Contact*)malloc(sizeof(Contact) * START_CAPACITY);
			if (my_addressbook->contacts == NULL)
			{
				printf("+-------------------------------+\n");
				printf("|     Error with malloc() !     |\n");
				printf("|    Closing the application    |\n");
				printf("+-------------------------------+\n");
				Sleep(TIME_SLEEP);
				exit(EXIT_FAILURE);
			}
			else
			{
				my_addressbook->size = 0;
				my_addressbook->capacity = START_CAPACITY;
				my_addressbook->is_modified = false;
				strcpy_s(my_addressbook->file_name, MAX_FILENAME, FILE_NAME);
				init_active(my_addressbook);
				printf("+---------------------------------------+\n");
				printf("|    Success with memory allocation!    |\n");
				printf("+---------------------------------------+\n");
				Sleep(TIME_SLEEP);
			}
		}
		break;
	case 1:
		my_addressbook = (AddressBook*)malloc(sizeof(AddressBook));
		if (my_addressbook == NULL)
		{
			printf("+-------------------------------+\n");
			printf("|     Error with malloc() !     |\n");
			printf("|    Closing the application    |\n");
			printf("+-------------------------------+\n");
			Sleep(TIME_SLEEP);
			exit(EXIT_FAILURE);
		}
		else
		{
			my_addressbook->contacts = (Contact*)malloc(sizeof(Contact) * START_CAPACITY);
			if (my_addressbook->contacts == NULL)
			{
				printf("+-------------------------------+\n");
				printf("|     Error with malloc() !     |\n");
				printf("|    Closing the application    |\n");
				printf("+-------------------------------+\n");
				Sleep(TIME_SLEEP);
				exit(EXIT_FAILURE);
			}
			else
			{
				printf("+---------------------------------------+\n");
				printf("|    Success with memory allocation!    |\n");
				printf("+---------------------------------------+\n");
				Sleep(TIME_SLEEP);
			}
		}
		break;
	default:
		printf("+--------------------------------------------------------------------------+\n");
		printf("|    Wrong number:                                                         |\n");
		printf("|    0 - for initialization during application startup!                    |\n");
		printf("|    1 - for initialization during application reading file bin or txt!    |\n");
		printf("+--------------------------------------------------------------------------+\n");
		break;
	}
	return my_addressbook;
}

void init_active(AddressBook* my_addressbook)
{
	for (int i = my_addressbook->size; i < my_addressbook->capacity; i++)
	{
		my_addressbook->contacts[i].active = false;
	}
}

void cleanup_struct(AddressBook *my_addressbook)
{
	free(my_addressbook->contacts);
	my_addressbook->contacts = NULL;
	free(my_addressbook);
	my_addressbook = NULL;
	printf("+--------------------------------------+\n");
	printf("|    DEALLOCATION:                     |\n");
	printf("|     1.my_addressbook->contacts,      |\n");
	printf("|     2.my_addressbook                 |\n");
	printf("|    DONE.                             |\n");
	printf("+--------------------------------------+\n");
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
		my_addressbook->is_modified = true;
		wsk_current_contacts->ID = my_addressbook->size;
		printf("ID contact number: %d\n", wsk_current_contacts->ID);
		printf("Please enter name:\n");
		printf("------------------\n");
		read_string(wsk_current_contacts->name, MAX_NAME);
		printf("Please enter last name:\n");
		printf("-----------------------\n");
		read_string(wsk_current_contacts->last_name, MAX_NAME);
		printf("Please enter phone number:\n");
		printf("--------------------------\n");
		read_string(wsk_current_contacts->phone_number, MAX_PHONE);
		data_accuracy_mail_and_phone(wsk_current_contacts, 0);
		printf("Please enter email adress:\n");
		printf("--------------------------\n");
		read_string(wsk_current_contacts->email_address, MAX_EMAIL);
		data_accuracy_mail_and_phone(wsk_current_contacts, 1);
		printf("Please enter company name:\n");
		printf("--------------------------\n");
		read_string(wsk_current_contacts->company, MAX_NAME);
		wsk_current_contacts->active = true;
		printf("+-----------------------------------+\n");
		printf("|    Contact have been activated !  |\n");
		printf("+-----------------------------------+\n");
		NEW_LINE;
		printf("+------------------------------------------+\n");
		printf("|    Do You want to add more contatcs ?    |\n");
		printf("|          Y - YES | N - NO                |\n");
		printf("+------------------------------------------+\n");
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
	printf("+-------------------------------------+\n");
	printf("|    Contacts adding is completed !   |\n");
	printf("+-------------------------------------+\n");
	Sleep(TIME_SLEEP);
}

void view_struct(const AddressBook *my_addressbook)
{
	if (my_addressbook == NULL)
	{
		printf("+------------------------------+\n");
		printf("|    No contacts available.    |\n");
		printf("+------------------------------+\n");
		Sleep(TIME_SLEEP);
	}
	else
	{
		printf("LIST OF %d CONTACTS\n", my_addressbook->size);
		NEW_LINE;
		printf("+-----+--------------------+------------------------------+--------------------+--------------------------------------------+--------------------------+\n");
		printf("|%3s  |%-20s|%-30s|%-20s|%-44s|%-26s|\n", "ID ", "NAME", "LAST NAME", "PHONE NUMBER", "EMAIL ADRESS", "COMPANY");
		printf("+-----+--------------------+------------------------------+--------------------+--------------------------------------------+--------------------------+\n");
		for (int i = 0; i < my_addressbook->size; i++)
		{
			printf("|%-5d|%-20s|%-30s|%-20s|%-44s|%-26s|\n", my_addressbook->contacts[i].ID, my_addressbook->contacts[i].name, my_addressbook->contacts[i].last_name, my_addressbook->contacts[i].phone_number, my_addressbook->contacts[i].email_address, my_addressbook->contacts[i].company);
			printf("+-----+--------------------+------------------------------+--------------------+--------------------------------------------+--------------------------+\n");
		}
		printf("+----------------------------------------------------+\n");
		printf("|    ADDRESS BOOK FILE NAME: %s         |\n", my_addressbook->file_name);
		printf("+----------------------------------------------------+\n");
	}
}

Contact *more_contacts(AddressBook* my_addressbook)
{
	Contact* ptr_temp;
	my_addressbook->capacity *= 2;
	ptr_temp = (Contact*)realloc(my_addressbook->contacts, my_addressbook->capacity * sizeof(Contact));
	if (ptr_temp == NULL)
	{
		printf("+------------------------------+\n");
		printf("|    Error with realloc() !    |\n");
		printf("+------------------------------+\n");
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
		printf("+-----------------------------+\n");
		printf("|  List of avaible contacts:  |\n");
		printf("+-----------------------------+\n");
		view_struct(my_addressbook);
		bool delete = true;
		int id_delete;
		while (delete)
		{
			printf("+-----------------------------------------------+\n");
			printf("|    To delelete contact, enter a ID number.    |\n");
			printf("+-----------------------------------------------+\n");
			ASKING;
			id_delete = check_id(my_addressbook, false);
			printf("+-----+--------------------+------------------------------+--------------------+--------------------------------------------+--------------------------+\n");
			printf("|  %5d|%-20s|%-30s|%-20s|%-44s|%-26s|\n", 
				my_addressbook->contacts[id_delete - 1].ID,	
				my_addressbook->contacts[id_delete - 1].name, 
				my_addressbook->contacts[id_delete - 1].last_name, 
				my_addressbook->contacts[id_delete - 1].phone_number, 
				my_addressbook->contacts[id_delete - 1].email_address, 
				my_addressbook->contacts[id_delete - 1].company);
			printf("+-----+--------------------+------------------------------+--------------------+--------------------------------------------+--------------------------+\n");
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
				my_addressbook->is_modified = true;
				printf("+-------------------------------------------------+\n");
				printf("|    Do You want to delete another contact ?      |\n");
				printf("|              Y - YES | N - NO                   |\n");
				printf("+-------------------------------------------------+\n");
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
				printf("+-------------------------------+\n");
				printf("|    Address Book is empty!     |\n");
				printf("|    Returning to Main Menu.    |\n");
				printf("+-------------------------------+\n");
				my_addressbook->is_modified = false;
				delete = false;
			}
		}
	}
	else
	{
		printf("+-------------------------------+\n");
		printf("|    No contacts available.     |\n");
		printf("|    Returning to Main Menu.    |\n");
		printf("+-------------------------------+\n");
		Sleep(TIME_SLEEP);
	}
}

int check_id(AddressBook *my_addressbook, bool EDIT_MODE)
{
	ASKING;
	int id_delete = taking_number();
	bool check = true;
	while (check)
	{
		if (id_delete > 0 && id_delete <= my_addressbook->size)
		{
			if (EDIT_MODE == true)
			{
				printf("+-------------------------------------+\n");
				printf("|    This contact will be changed:    |\n");
				printf("+-------------------------------------+\n");
				check = false;
			}
			else
			{
				printf("+-------------------------------------+\n");
				printf("|    This contact will be deleted:    |\n");
				printf("+-------------------------------------+\n");
				check = false;

			}
		}
		else
		{
			printf("+------------------------------+\n");
			printf("|    Enter valid ID number !   |\n");
			printf("+------------------------------+\n");
			ASKING;
			id_delete = taking_number();
			continue;
		}
	}
	return id_delete;
}

void search_contacts_main(AddressBook* my_addressbook, bool EDIT_MODE)
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
				search_by_all_Contacts(my_addressbook, ask_letter_case());
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
			if (EDIT_MODE == true)
			{
				still_searching = false;
			}
		}
	}
	else
	{
		printf("+-------------------------------------+\n");
		printf("|       No contacts available.        |\n");
		printf("|    There is nothing to search.      |\n");
		printf("|      Returning to Main Menu.        |\n");
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
	ASKING;
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
	printf("+-----+--------------------+------------------------------+--------------------+--------------------------------------------+--------------------------+\n");
	printf("|%3s  |%-20s|%-30s|%-20s|%-44s|%-26s|\n", "ID ", "NAME", "LAST NAME", "PHONE NUMBER", "EMAIL ADRESS", "COMPANY");
	printf("+-----+--------------------+------------------------------+--------------------+--------------------------------------------+--------------------------+\n");
	for (int i = 0; i < SizeScoreBoard; i++)
	{
		printf("|%5d|%-20s|%-30s|%-20s|%-44s|%-26s|\n", 
			my_addressbook->contacts[*(ScoreBoard + i)].ID, 
			my_addressbook->contacts[*(ScoreBoard + i)].name, 
			my_addressbook->contacts[*(ScoreBoard + i)].last_name, 
			my_addressbook->contacts[*(ScoreBoard + i)].phone_number, 
			my_addressbook->contacts[*(ScoreBoard + i)].email_address, 
			my_addressbook->contacts[*(ScoreBoard + i)].company);
		printf("+-----+--------------------+------------------------------+--------------------+--------------------------------------------+--------------------------+\n");
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
		printf("+-------------------------------+\n");
		printf("|     Error with malloc() !     |\n");
		printf("|    Closing the application    |\n");
		printf("+-------------------------------+\n");
		Sleep(TIME_SLEEP);
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("+-----------------------------------------------+\n");
		printf("|    Add string, that You want to search for:   |\n");
		printf("+-----------------------------------------------+\n");
		read_string(strSearch, MAX_EMAIL);
		if (letter_case == NO)
		{
			char* UpperStrSearch = (char*)malloc(sizeof(char) * (strlen(strSearch) + 1));
			char UpperContactName[MAX_EMAIL] = { '\0' };
			if (UpperStrSearch == NULL)
			{
				printf("+-------------------------------+\n");
				printf("|     Error with malloc() !     |\n");
				printf("|    Closing the application    |\n");
				printf("+-------------------------------+\n");
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
		NEW_LINE;
		printf("+---------------------------------------------------+\n");
		printf("|    Would You like to save the search results ?    |\n");
		printf("|                Y - YES | N - NO                   |\n");
		printf("+---------------------------------------------------+\n");
		ASKING;
		char ask_search_save;
		if ((ask_search_save = get_letter()) == YES)
		{
			printf("+---------------------------------------+\n");
			printf("|    Select file format:                |\n");
			printf("|     A - No formating.                 |\n");
			printf("|     B - Separation with semicolon.    |\n");
			printf("+---------------------------------------+\n");
			ASKING;
			switch ((ask_search_save = get_letter()))
			{
			case 'A':
				save_to_file_searched_contacts(my_addressbook, ScoreBoard, SizeScoreBoard, strSearch);
				break;
			case 'B':
				save_to_file_searched_semicolon_contacts(my_addressbook, ScoreBoard, SizeScoreBoard, strSearch);
				break;
			default:
				printf("Incorrect format!\n");
				break;
			}
		}
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

void search_by_all_Contacts(AddressBook* my_addressbook, char letter_case)
{
	int SizeScoreBoard = 0;
	int* ScoreBoard = NULL;
	char* searched_structure_field = NULL;
	char strSearch[MAX_NAME];
	ScoreBoard = (int*)malloc(sizeof(int) * my_addressbook->size);
	if (ScoreBoard == NULL)
	{
		printf("+--------------------------------------------------+\n");
		printf("|               Error with malloc!                 |\n");
		printf("|    Allocating memory for ID array of results.    |\n");
		printf("|            Returning to Search Menu.             |\n");
		printf("+--------------------------------------------------+\n");
		Sleep(ERROR_TIME_SLEEP);
	}
	else
	{
		printf("+-----------------------------------------------+\n");
		printf("|    Add string, that You want to search for:   |\n");
		printf("+-----------------------------------------------+\n");
		read_string(strSearch, MAX_EMAIL);
		if (letter_case == NO)
		{
			char* UpperStrSearch = (char*)malloc(sizeof(char) * (strlen(strSearch) + 1));
			char UpperContactName[MAX_EMAIL] = { '\0' };
			if (UpperStrSearch == NULL)
			{
				printf("+--------------------------------------+\n");
				printf("|        Error with malloc!            |\n");
				printf("|        Closing application.          |\n");
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
		NEW_LINE;
		printf("+---------------------------------------------------+\n");
		printf("|    Would You like to save the search results ?    |\n");
		printf("|                Y - YES | N - NO                   |\n");
		printf("+---------------------------------------------------+\n");
		ASKING;
		char ask_search_save;
		if ((ask_search_save = get_letter()) == YES)
		{
			printf("+---------------------------------------+\n");
			printf("|    Select file format:                |\n");
			printf("|     A - No formating.                 |\n");
			printf("|     B - Separation with semicolon.    |\n");
			printf("+---------------------------------------+\n");
			ASKING;
			switch ((ask_search_save = get_letter()))
			{
			case 'A':
				save_to_file_searched_contacts(my_addressbook, ScoreBoard, SizeScoreBoard, strSearch);
				break;
			case 'B':
				save_to_file_searched_semicolon_contacts(my_addressbook, ScoreBoard, SizeScoreBoard,	strSearch);
				break;
			default:
				printf("Incorrect format!\n");
				break;
			}
		}
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

void edit_contacts_main(AddressBook* my_addressbook)
{
	bool editing = true;
	if (my_addressbook != NULL && my_addressbook->size > 0)
	{
		char ask;
		printf("+--------------------------------------------------------------------+\n");
		printf("|  Before editing, Do You want to search for a right Contact ?       |\n");
		printf("|                    Y - YES | N - NO                                |\n");
		printf("+--------------------------------------------------------------------+\n");
		ASKING;
		if ((ask = get_letter()) == YES)
		{
			bool end_searching = false;
			char asking;
			while (end_searching == false)
			{
				search_contacts_main(my_addressbook, true);
				printf("+--------------------------------------------------------+\n");
				printf("|    Did You find the contact intended for editing ?     |\n");
				printf("|                 Y - YES | N - NO                       |\n");
				printf("+--------------------------------------------------------+\n");
				if ((asking = get_letter()) == YES)
				{
					printf("+-----------------------------+\n");
					printf("|    Remember contact ID !    |\n");
					printf("+-----------------------------+\n");
					end_searching = true;
				}
				else
				{
					TRY;
					Sleep(TIME_SLEEP);
				}
			}
		}
		printf("+---------------------------+\n");
		printf("|                           |\n");
		printf("|  Please enter the ID:     |\n");
		printf("|                           |\n");
		printf("+---------------------------+\n");
		ASKING;
		int edit_ID = check_id(my_addressbook, true);
		NEW_LINE;
		while (editing)
		{
			printf("+------------------------------------------------+\n");
			printf("| +--------------------------------------------+ |\n");
			printf("| |     Editing Adress Book                    | |\n");
			printf("| |     Available options below:               | |\n");
			printf("| |                                            | |\n");
			printf("| |      1. Change all                         | |\n");
			printf("| |      2. Change name                        | |\n");
			printf("| |      3. Change last name                   | |\n");
			printf("| |      4. Change phone number                | |\n");
			printf("| |      5. Change email address               | |\n");
			printf("| |      6. Change company                     | |\n");
			printf("| |      0. Exit                               | |\n");
			printf("| +--------------------------------------------+ |\n");
			printf("+------------------------------------------------+\n");
			ASKING;
			int search_by = taking_number();
			switch (search_by)
			{
			case 0:
				printf("+--------------------------------------+\n");
				printf("|  I am leaving the editing options.   |\n");
				printf("|  Returning to Main Menu.             |\n");
				printf("+--------------------------------------+\n");
				Sleep(TIME_SLEEP);
				editing = false;
				break;
			case 1:
				edit_contact(my_addressbook, edit_ID, 0, true);
				my_addressbook->is_modified = true;
				break;
			case 2:
				edit_contact(my_addressbook, edit_ID, 0, false);
				my_addressbook->is_modified = true;
				break;
			case 3:
				edit_contact(my_addressbook, edit_ID, 1, false);
				my_addressbook->is_modified = true;
				break;
			case 4:
				edit_contact(my_addressbook, edit_ID, 2, false);
				my_addressbook->is_modified = true;
				break;
			case 5:
				edit_contact(my_addressbook, edit_ID, 3, false);
				my_addressbook->is_modified = true;
				break;
			case 6:
				edit_contact(my_addressbook, edit_ID, 4, false);
				my_addressbook->is_modified = true;
				break;
			default:
				printf("+--------------------------------------+\n");
				printf("|    Please choose right option!       |\n");
				printf("+--------------------------------------+\n");
				break;
			}
		}
	}
	else
	{
		printf("+------------------------------------------+\n");
		printf("|    No contacts available for editing.    |\n");
		printf("+------------------------------------------+\n");
		Sleep(TIME_SLEEP);
	}
}

void edit_contact(AddressBook* my_addressbook, int edit_ID, int field_number, bool edit_all)
{
	char* Field_Names[LIMIT_FIELDS] = { "Name", "Last name", "Phone number", "Email address", "Company" };
	int Field_Sizes[LIMIT_FIELDS] = { MAX_NAME, MAX_NAME, MAX_PHONE, MAX_EMAIL, MAX_NAME };
	if (edit_all == false)
	{
		printf("Let's start editing constact: %s\n", Field_Names[field_number]);
		printf("-----------------------------\n");
		read_string(all_fields_in_array(my_addressbook, edit_ID - 1, field_number), Field_Sizes[field_number]);
		if (field_number == 2)
		{
			data_accuracy_mail_and_phone((my_addressbook->contacts), 0);
		}
		else if (field_number == 3)
		{
			data_accuracy_mail_and_phone((my_addressbook->contacts), 1);
		}
	}
	else
	{
		for (int i = SEARCH_NAME; i <= SEARCH_COMPANY; i++)
		{
			printf("Editing constact: %s\n", Field_Names[i]);
			printf("-----------------n");
			read_string(all_fields_in_array(my_addressbook, edit_ID - 1, i), Field_Sizes[i]);
			if (field_number == 2)
			{
				data_accuracy_mail_and_phone(my_addressbook->contacts, 0);
			}
			else if (field_number == 3)
			{
				data_accuracy_mail_and_phone((my_addressbook->contacts), 1);
			}
		}
	}
	printf("+---------------------------------------+\n");
	printf("|    Editing successfully completed.    |\n");
	printf("+---------------------------------------+\n");
}

void data_accuracy_mail_and_phone(Contact* wsk_current_contact, int check_field)
{
	char* domains[] = { "@gmail.com", "@onet.pl", "@op.pl", "@wp.pl", "@o2.pl", "@int.pl", "@interia.pl", "@poczta.fm", "@outlook.com", "@hotmail.com", "@icloud.com", "@yahoo.com"};
	switch (check_field)
	{
	case 0:
		int i = 0;
		while (wsk_current_contact->phone_number[i] != '\0')
		{
			if (wsk_current_contact->phone_number[i] == ' ')
			{
				wsk_current_contact->phone_number[i] = '-';
				i++;
			}
			else
			{
				i++;
			}
		}
		break;
	case 1:
		bool end = false;
		int domain_check_OK = 0;
		int domain_check_NOK = 0;
		while (end == false)
		{
			for (int i = 0; i < _countof(domains); i++)
			{
				if (strstr(wsk_current_contact->email_address, domains[i]) != NULL)
				{
					domain_check_OK++;
				}
				else
				{
					domain_check_NOK++;
				}
			}
			if (domain_check_OK == 1 )
			{
				end = true;
				domain_check_OK = 0;
			}
			else if (domain_check_NOK != 1)
			{
				printf("+---------------------------------------------+\n");
				printf("|    An invalid email address was entered.    |\n");
				printf("|       Please check the address domain.      |\n");
				printf("|           Enter correct address.            |\n");
				printf("+---------------------------------------------+\n");
				read_string(wsk_current_contact->email_address, MAX_EMAIL);
				domain_check_NOK = 0;
			}
		}
		break;
	}
}
