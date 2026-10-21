#include "contact_manager.h"

void is_struct_saved_to_file(AddressBook* my_addressbook)
{
	if (my_addressbook->is_modified == true)
	{
		printf("+-------------------------------------+\n");
		printf("|    Changes have not been saved !    |\n");
		printf("|    Would You like to save them ?    |\n");
		printf("|          Y - YES | N - NO           |\n");
		printf("+-------------------------------------+\n");
		ASKING;
		char ask_user;
		if ((ask_user = get_letter()) == YES)
		{
			saving_struct_to_file_main(my_addressbook);
		}
	}
}

void saving_struct_to_file_main(AddressBook* my_addressbook)
{
	if (my_addressbook != NULL)
	{
		bool write = true;
		while (write)
		{
			printf("+------------------------------------------------+\n");
			printf("| +--------------------------------------------+ |\n");
			printf("| |     Saving a Adress Book                   | |\n");
			printf("| |     Available options below:               | |\n");
			printf("| |                                            | |\n");
			printf("| |      1. Save as bin file.                  | |\n");
			printf("| |      2. Save as txt file.                  | |\n");
			printf("| |      3. Save as txt file with semicolon.   | |\n");
			printf("| |      0. Exit                               | |\n");
			printf("| +--------------------------------------------+ |\n");
			printf("+------------------------------------------------+\n");
			ASKING;
			int writing_by = taking_number();
			switch (writing_by)
			{
			case 0:
				printf("+--------------------------------------+\n");
				printf("|  I am leaving the saving options.    |\n");
				printf("|       Returning to Main Menu.        |\n");
				printf("+--------------------------------------+\n");
				Sleep(TIME_SLEEP);
				write = false;
				break;
			case 1:
				bin_save_file_my_addressbook(my_addressbook);
				my_addressbook->is_modified = false;
				break;
			case 2:
				save_to_file_my_addressbook(my_addressbook);
				my_addressbook->is_modified = false;
				break;
			case 3:
				save_to_file_semicolon_my_addressbook(my_addressbook);
				my_addressbook->is_modified = false;
				break;
			default:
				printf("+--------------------------------------+\n");
				printf("|    Please chose right option!        |\n");
				printf("+--------------------------------------+\n");
				TRY;
				break;
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

void save_to_file_my_addressbook(AddressBook* my_addressbook)
{
	FILE* PLIK_TXT;
	if (fopen_s(&PLIK_TXT, FILE_NAME, "w+") != 0)
	{
		printf("+----------------------------------------------+\n");
		printf("|    There was a problem with file opening.    |\n");
		printf("|	   CHECK THE FILE NAME AND EXTENSION       |\n");
		printf("|         Returning to Read Menu               |\n");
		printf("|           Please try again !                 |\n");
		printf("+----------------------------------------------+\n");
		Sleep(ERROR_TIME_SLEEP);
		return;
	}
	else
	{
		fprintf(PLIK_TXT, "%-32s %-3d %-3d %-d\n", 
			my_addressbook->file_name, 
			my_addressbook->capacity, 
			my_addressbook->size, 
			my_addressbook->is_modified);
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
		printf("+----------------------+\n");
		printf("|    SAVE SUCCESS !    |\n");
		printf("+----------------------+\n");
		Sleep(TIME_SLEEP);
	}
}

void save_to_file_semicolon_my_addressbook(AddressBook* my_addressbook)
{
	FILE* PLIK_TXT_SEMICOLON;
	if (fopen_s(&PLIK_TXT_SEMICOLON, SEMICOLON_FILE_NAME, "w+") != 0)
	{
		printf("+----------------------------------------------+\n");
		printf("|    There was a problem with file opening.    |\n");
		printf("|	   CHECK THE FILE NAME AND EXTENSION       |\n");
		printf("|         Returning to Read Menu               |\n");
		printf("|           Please try again !                 |\n");
		printf("+----------------------------------------------+\n");
		Sleep(ERROR_TIME_SLEEP);
		return;
	}
	else
	{
		fprintf(PLIK_TXT_SEMICOLON, "%s;%d;%d;%d\n", 
			my_addressbook->file_name, 
			my_addressbook->capacity, 
			my_addressbook->size, 
			my_addressbook->is_modified);
		for (int i = 0; i < DATA_BLOCK; i++)
		{

			fprintf(PLIK_TXT_SEMICOLON, "%d;%s;%s;%s;%s;%s;%d\n",
				my_addressbook->contacts[i].ID,
				my_addressbook->contacts[i].name,
				my_addressbook->contacts[i].last_name,
				my_addressbook->contacts[i].phone_number,
				my_addressbook->contacts[i].email_address,
				my_addressbook->contacts[i].company,
				my_addressbook->contacts[i].active);
		}
		fclose(PLIK_TXT_SEMICOLON);
		printf("+----------------------+\n");
		printf("|    SAVE SUCCESS !    |\n");
		printf("+----------------------+\n");
		Sleep(TIME_SLEEP);
	}
}

void save_to_file_searched_contacts(AddressBook* my_addressbook, int *ScoreBoard, int SizeScoreBoard)
{
	FILE* SEARCH_PLIK_TXT;
	if (fopen_s(&SEARCH_PLIK_TXT, SEARCH_FILE_NAME, "w+") != 0)
	{
		printf("+----------------------------------------------+\n");
		printf("|    There was a problem with file opening.    |\n");
		printf("|	   CHECK THE FILE NAME AND EXTENSION       |\n");
		printf("|         Returning to Read Menu               |\n");
		printf("|           Please try again !                 |\n");
		printf("+----------------------------------------------+\n");
		Sleep(ERROR_TIME_SLEEP);
		return;
	}
	else
	{
		fprintf(SEARCH_PLIK_TXT, "%-32s %-3d %-3d %-3d\n", 
			my_addressbook->file_name, 
			my_addressbook->capacity, 
			my_addressbook->size, 
			SizeScoreBoard);
		for (int i = 0; i < SizeScoreBoard; i++)
		{

			fprintf(SEARCH_PLIK_TXT, "%-3d %-32s %-32s %-16s %-64s %-32s %-d\n",
				my_addressbook->contacts[*(ScoreBoard + i)].ID,
				my_addressbook->contacts[*(ScoreBoard + i)].name,
				my_addressbook->contacts[*(ScoreBoard + i)].last_name,
				my_addressbook->contacts[*(ScoreBoard + i)].phone_number,
				my_addressbook->contacts[*(ScoreBoard + i)].email_address,
				my_addressbook->contacts[*(ScoreBoard + i)].company,
				my_addressbook->contacts[*(ScoreBoard + i)].active);
		}
		fclose(SEARCH_PLIK_TXT);
		printf("+----------------------+\n");
		printf("|    SAVE SUCCESS !    |\n");
		printf("+----------------------+\n");
		Sleep(TIME_SLEEP);
	}
}

void save_to_file_searched_semicolon_contacts(AddressBook* my_addressbook, int* ScoreBoard, int SizeScoreBoard)
{
	FILE* SEARCH_PLIK_TXT_SEMICOLON;
	if (fopen_s(&SEARCH_PLIK_TXT_SEMICOLON, "NO_SEMICOLON.txt", "w+") != 0)
	{
		printf("+----------------------------------------------+\n");
		printf("|    There was a problem with file opening.    |\n");
		printf("|	   CHECK THE FILE NAME AND EXTENSION       |\n");
		printf("|         Returning to Read Menu               |\n");
		printf("|           Please try again !                 |\n");
		printf("+----------------------------------------------+\n");
		Sleep(ERROR_TIME_SLEEP);
		return;
	}
	else
	{

		fprintf(SEARCH_PLIK_TXT_SEMICOLON, "%s;%d;%d;%d\n",
			my_addressbook->file_name,
			my_addressbook->capacity,
			my_addressbook->size,
			SizeScoreBoard);
		for (int i = 0; i < SizeScoreBoard; i++)
		{

			fprintf(SEARCH_PLIK_TXT_SEMICOLON, "%d;%s;%s;%s;%s;%s;%d\n",
				my_addressbook->contacts[*(ScoreBoard + i)].ID,
				my_addressbook->contacts[*(ScoreBoard + i)].name,
				my_addressbook->contacts[*(ScoreBoard + i)].last_name,
				my_addressbook->contacts[*(ScoreBoard + i)].phone_number,
				my_addressbook->contacts[*(ScoreBoard + i)].email_address,
				my_addressbook->contacts[*(ScoreBoard + i)].company,
				my_addressbook->contacts[*(ScoreBoard + i)].active);
		}
		fclose(SEARCH_PLIK_TXT_SEMICOLON);
		printf("+----------------------+\n");
		printf("|    SAVE SUCCESS !    |\n");
		printf("+----------------------+\n");
		Sleep(TIME_SLEEP);
	}
}

void bin_save_file_my_addressbook(AddressBook* my_addressbook)
{
	FILE* PLIK_BIN;
	if (fopen_s(&PLIK_BIN, BIN_FILE_NAME, "wb+") != 0)
	{
		printf("+----------------------------------------------+\n");
		printf("|    There was a problem with file opening.    |\n");
		printf("|	   CHECK THE FILE NAME AND EXTENSION       |\n");
		printf("|         Returning to Read Menu               |\n");
		printf("|           Please try again !                 |\n");
		printf("+----------------------------------------------+\n");
		Sleep(ERROR_TIME_SLEEP);
		return;
	}
	else
	{
		fwrite(&my_addressbook->file_name, sizeof(my_addressbook->file_name), 1, PLIK_BIN);
		fwrite(&my_addressbook->capacity, sizeof(my_addressbook->capacity), 1, PLIK_BIN);
		fwrite(&my_addressbook->size, sizeof(my_addressbook->size), 1, PLIK_BIN);
		fwrite(&my_addressbook->is_modified, sizeof(my_addressbook->is_modified), 1, PLIK_BIN);
		for (int i = 0; i < DATA_BLOCK; i++)
		{
			fwrite(&my_addressbook->contacts[0], sizeof(Contact), my_addressbook->size, PLIK_BIN);
		}
		fclose(PLIK_BIN);
		printf("+----------------------+\n");
		printf("|    SAVE SUCCESS !    |\n");
		printf("+----------------------+\n");
		Sleep(TIME_SLEEP);
	}
}

AddressBook* reading_struct_from_file_main()
{
	AddressBook* my_addressbook = NULL;
	bool write = true;
	while (write)
	{
		printf("+------------------------------------------------+\n");
		printf("| +--------------------------------------------+ |\n");
		printf("| |     Reading a Adress Book                  | |\n");
		printf("| |     Available options below:               | |\n");
		printf("| |                                            | |\n");
		printf("| |     1. Read from bin file.                 | |\n");
		printf("| |     2. Read from txt file.                 | |\n");
		printf("| |     3. Read from txt file with semicolon.  | |\n");
		printf("| |     0. Exit                                | |\n");
		printf("| +--------------------------------------------+ |\n");
		printf("+------------------------------------------------+\n");
		ASKING;
		int writing_by;
		switch (writing_by = taking_number())
		{
		case 0:
			printf("+---------------------------------------+\n");
			printf("|  I am leaving the reading options.    |\n");
			printf("|       Returning to Main Menu.         |\n");
			printf("+---------------------------------------+\n");
			Sleep(TIME_SLEEP);
			write = false;
			break;
		case 1:
			my_addressbook = bin_read_from_file_my_addressbook();
			if (my_addressbook == NULL)
			{
				write = true;
			}
			else
			{
				my_addressbook->is_modified = false;
				write = false;
			}
			break;
		case 2:
			my_addressbook = read_from_file_my_addressbook();
			if (my_addressbook == NULL)
			{
				write = true;
			}
			else
			{
				my_addressbook->is_modified = false;
				write = false;
			}
			break;
		case 3:
			my_addressbook = read_from_file_semicolon_my_addressbook();
			if (my_addressbook == NULL)
			{
				write = true;
			}
			else
			{
				my_addressbook->is_modified = false;
				write = false;
			}
			break;
		default:
			printf("+--------------------------------------+\n");
			printf("|    Please chose right option!        |\n");
			printf("+--------------------------------------+\n");
			TRY;
			break;
		}
	}
	return my_addressbook;
}

AddressBook* read_from_file_my_addressbook()
{
	AddressBook* my_addressbook = init_struct_main(1);
	int temp_is_modified;
	int temp_actvice;
	if (my_addressbook == NULL)
	{
		printf("+-------------------------------+\n");
		printf("|     Error with malloc() !     |\n");
		printf("|    Closing the application    |\n");
		printf("+-------------------------------+\n");
		Sleep(TIME_SLEEP);
		exit(EXIT_FAILURE);
	}
	FILE* PLIK_TXT;
	if (fopen_s(&PLIK_TXT, FILE_NAME, "r") != 0)
	{
		printf("+----------------------------------------------+\n");
		printf("|    There was a problem with file opening.    |\n");
		printf("|	   CHECK THE FILE NAME AND EXTENSION       |\n");
		printf("|         Returning to Read Menu               |\n");
		printf("|           Please try again !                 |\n");
		printf("+----------------------------------------------+\n");
		Sleep(ERROR_TIME_SLEEP);
		return my_addressbook = NULL;
	}
	else
	{
		fscanf_s(PLIK_TXT, "%32s %3d %3d %d", 
			my_addressbook->file_name, MAX_FILENAME, 
			&my_addressbook->capacity, 
			&my_addressbook->size, 
			&temp_is_modified);
		my_addressbook->is_modified = temp_is_modified;
		printf("+--------------------------------------------------+\n");
		printf("| MY ADDRESS BOOK FILE NAME: %s       |\n", my_addressbook->file_name);													    
		printf("| MY ADDRESS BOOK CAPACITY : %3d                   |\n", my_addressbook->capacity); 														    
		printf("| MY ADDRESS BOOK SIZE     : %3d                   |\n", my_addressbook->size);	   
		printf("+--------------------------------------------------+\n");
		Sleep(TIME_SLEEP);
		for (int i = 0; i < my_addressbook->size; i++)
		{
			if (i == 0)
			{
				Contact* ptr_temp;
				ptr_temp = (Contact*)realloc(my_addressbook->contacts, my_addressbook->capacity *	sizeof(Contact));
				if (ptr_temp == NULL)
				{
					printf("+-------------------------------+\n");
					printf("|     Error with realloc() !    |\n");
					printf("|    Closing the application    |\n");
					printf("+-------------------------------+\n");
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
		printf("+-------------------------+\n");
		printf("|    READING SUCCESS !    |\n");
		printf("+-------------------------+\n");
		fclose(PLIK_TXT);
		Sleep(TIME_SLEEP);
		return my_addressbook;
	}
}

AddressBook* read_from_file_semicolon_my_addressbook()
{
	AddressBook* my_addressbook = init_struct_main(1);
	int temp_is_modified;
	int temp_actvice;
	if (my_addressbook == NULL)
	{
		printf("+-------------------------------+\n");
		printf("|     Error with malloc() !     |\n");
		printf("|    Closing the application    |\n");
		printf("+-------------------------------+\n");
		exit(EXIT_FAILURE);
	}
	FILE* PLIK_SEMICOLON_TXT;
	if (fopen_s(&PLIK_SEMICOLON_TXT, SEMICOLON_FILE_NAME, "r") != 0)
	{
		printf("+----------------------------------------------+\n");
		printf("|    There was a problem with file opening.    |\n");
		printf("|	   CHECK THE FILE NAME AND EXTENSION       |\n");
		printf("|         Returning to Read Menu               |\n");
		printf("|           Please try again !                 |\n");
		printf("+----------------------------------------------+\n");
		Sleep(ERROR_TIME_SLEEP);
		return my_addressbook = NULL;
	}
	else
	{
		fscanf_s(PLIK_SEMICOLON_TXT, "%[^;];%d;%d;%d", 
			my_addressbook->file_name, MAX_FILENAME,
			&my_addressbook->capacity, 
			&my_addressbook->size, 
			&temp_is_modified);
		my_addressbook->is_modified = temp_is_modified;
		printf("+--------------------------------------------------+\n");
		printf("| MY ADDRESS BOOK FILE NAME: %s       |\n", my_addressbook->file_name);
		printf("| MY ADDRESS BOOK CAPACITY : %3d                   |\n", my_addressbook->capacity);
		printf("| MY ADDRESS BOOK SIZE     : %3d                   |\n", my_addressbook->size);
		printf("+--------------------------------------------------+\n");
		Sleep(TIME_SLEEP);
		for (int i = 0; i < my_addressbook->size; i++)
		{
			if (i == 0)
			{
				Contact* ptr_temp;
				ptr_temp = (Contact*)realloc(my_addressbook->contacts, my_addressbook->capacity * sizeof	(Contact));
				if (ptr_temp == NULL)
				{
					printf("+-------------------------------+\n");
					printf("|     Error with realloc() !    |\n");
					printf("|    Closing the application    |\n");
					printf("+-------------------------------+\n");
					Sleep(TIME_SLEEP);
					exit(EXIT_FAILURE);
				}
				else
				{
					my_addressbook->contacts = ptr_temp;
					Sleep(TIME_SLEEP);
				}
			}
			fscanf_s(PLIK_SEMICOLON_TXT, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d\n",
				&my_addressbook->contacts[i].ID,
				my_addressbook->contacts[i].name, MAX_NAME,
				my_addressbook->contacts[i].last_name, MAX_NAME,
				my_addressbook->contacts[i].phone_number, MAX_PHONE,
				my_addressbook->contacts[i].email_address, MAX_EMAIL,
				my_addressbook->contacts[i].company, MAX_NAME,
				&temp_actvice);
			my_addressbook->contacts[i].active = temp_actvice;
		}
		fclose(PLIK_SEMICOLON_TXT);
		printf("+-------------------------+\n");
		printf("|    READING SUCCESS !    |\n");
		printf("+-------------------------+\n");
		Sleep(TIME_SLEEP);
		return my_addressbook;
	}
}

AddressBook* bin_read_from_file_my_addressbook()
{
	AddressBook* my_addressbook = init_struct_main(1);
	if (my_addressbook == NULL)
	{
		printf("+-------------------------------+\n");
		printf("|     Error with malloc() !     |\n");
		printf("|    Closing the application    |\n");
		printf("+-------------------------------+\n");
		exit(EXIT_FAILURE);
	}
	FILE* PLIK_BIN;
	if (fopen_s(&PLIK_BIN, BIN_FILE_NAME, "rb+") != 0)
	{
		printf("+----------------------------------------------+\n");
		printf("|    There was a problem with file opening.    |\n");
		printf("|	   CHECK THE FILE NAME AND EXTENSION       |\n");
		printf("|         Returning to Read Menu               |\n");
		printf("|           Please try again !                 |\n");
		printf("+----------------------------------------------+\n");
		Sleep(ERROR_TIME_SLEEP);
		return my_addressbook = NULL;
	}
	else
	{
		fread_s(&my_addressbook->file_name, MAX_NAME, MAX_NAME, 1, PLIK_BIN);
		fread_s(&my_addressbook->capacity, sizeof(int), sizeof(int), 1, PLIK_BIN);
		fread_s(&my_addressbook->size, sizeof(int), sizeof(int), 1, PLIK_BIN);
		fread_s(&my_addressbook->is_modified, sizeof(bool), sizeof(bool), 1, PLIK_BIN);
		printf("+--------------------------------------------------+\n");
		printf("| MY ADDRESS BOOK FILE NAME: %-13s       |\n", my_addressbook->file_name);
		printf("| MY ADDRESS BOOK CAPACITY : %3d                   |\n", my_addressbook->capacity);
		printf("| MY ADDRESS BOOK SIZE     : %3d                   |\n", my_addressbook->size);
		printf("+--------------------------------------------------+\n");
		Sleep(TIME_SLEEP);
		Contact* ptr_temp;
		ptr_temp = (Contact*)realloc(my_addressbook->contacts, my_addressbook->capacity * sizeof	(Contact));
		if (ptr_temp == NULL)
		{
			printf("+-------------------------------+\n");
			printf("|     Error with realloc() !    |\n");
			printf("|    Closing the application    |\n");
			printf("+-------------------------------+\n");
			Sleep(TIME_SLEEP);
			exit(EXIT_FAILURE);
		}
		else
		{
			my_addressbook->contacts = ptr_temp;
			Sleep(TIME_SLEEP);
			for (int i = 0; i < my_addressbook->size; i++)
			{
				fread_s(&my_addressbook->contacts[i], (my_addressbook->size * sizeof(Contact)),		sizeof  (Contact), 1, PLIK_BIN);
			}
			fclose(PLIK_BIN);
			printf("+-------------------------+\n");
			printf("|    READING SUCCESS !    |\n");
			printf("+-------------------------+\n");
			Sleep(TIME_SLEEP);
			return my_addressbook;
		}
	}
}