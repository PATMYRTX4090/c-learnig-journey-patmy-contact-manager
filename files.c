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
	char file_name[FILENAME_MAX] = { '\0' };
	if (fopen_s(&PLIK_TXT, making_or_reading_a_file_name(file_name, " ", 1), "w+") != 0)
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
		fprintf(PLIK_TXT, "%260s %d %d %d\n", 
			my_addressbook->file_name, 
			my_addressbook->capacity, 
			my_addressbook->size, 
			my_addressbook->is_modified);
		for (int i = 0; i < my_addressbook->size; i++)
		{

			fprintf(PLIK_TXT, "%d %-32s %-32s %-16s %-64s %-32s %d\n",
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
		NEW_LINE;
		Sleep(TIME_SLEEP);
	}
}

void save_to_file_semicolon_my_addressbook(AddressBook* my_addressbook)
{
	FILE* PLIK_TXT_SEMICOLON;
	char file_name[FILENAME_MAX] = { '\0' };
	if (fopen_s(&PLIK_TXT_SEMICOLON, making_or_reading_a_file_name(file_name, " ", 1), "w+") != 0)
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
		for (int i = 0; i < my_addressbook->size; i++)
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

void save_to_file_searched_contacts(AddressBook* my_addressbook, int *ScoreBoard, int SizeScoreBoard, char SearchedStr[])
{
	FILE* SEARCH_PLIK_TXT;
	char file_name[FILENAME_MAX] = { '\0' };
	if (fopen_s(&SEARCH_PLIK_TXT, making_or_reading_a_file_name(file_name, SearchedStr, 4), "w+") != 0)
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
		fprintf(SEARCH_PLIK_TXT, "%-260s %d %d %d\n", 
			file_name, 
			SizeScoreBoard, 
			SizeScoreBoard, 
			1);
		for (int i = 0; i < SizeScoreBoard; i++)
		{

			fprintf(SEARCH_PLIK_TXT, "%d %-32s %-32s %-16s %-64s %-32s %d\n",
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

void save_to_file_searched_semicolon_contacts(AddressBook* my_addressbook, int* ScoreBoard, int SizeScoreBoard, char SearchedStr[])
{
	FILE* SEARCH_PLIK_TXT_SEMICOLON;
	char file_name[FILENAME_MAX] = { '\0' };
	if (fopen_s(&SEARCH_PLIK_TXT_SEMICOLON, making_or_reading_a_file_name(file_name, SearchedStr, 4), "w+") != 0)
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
			file_name,
			SizeScoreBoard,
			SizeScoreBoard,
			1);
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
	char file_name[FILENAME_MAX] = { '\0' };
	if (fopen_s(&PLIK_BIN, making_or_reading_a_file_name(file_name, " ", 0), "wb+") != 0)
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

void reading_struct_from_file_main(AddressBook* my_addressbook)
{
	bool write = true;
	while (write)
	{
		printf("+------------------------------------------------+\n");
		printf("| +--------------------------------------------+ |\n");
		printf("| |     Reading a Address Book                 | |\n");
		printf("| |     Available options below:               | |\n");
		printf("| |                                            | |\n");
		printf("| |    1. Read from bin file.                  | |\n");
		printf("| |    2. Read from txt file.                  | |\n");
		printf("| |    3. Read from txt file with semicolon.   | |\n");
		printf("| |    0. Exit                                 | |\n");
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
			bin_read_from_file_my_addressbook(my_addressbook);
			my_addressbook->is_modified = false;
			write = false;
			break;
		case 2:
			read_from_file_my_addressbook(my_addressbook);
			my_addressbook->is_modified = false;
			write = false;
			break;
		case 3:
			read_from_file_semicolon_my_addressbook(my_addressbook);
			my_addressbook->is_modified = false;
			write = false;
			break;
		default:
			printf("+--------------------------------------+\n");
			printf("|    Please chose right option!        |\n");
			printf("+--------------------------------------+\n");
			TRY;
			NEW_LINE;
			break;
		}
	}
}

void read_from_file_my_addressbook(AddressBook *my_addressbook)
{
	int temp_is_modified;
	int temp_actvice;
	FILE* PLIK_TXT;
	char file_name[FILENAME_MAX] = { '\0' };
	if (fopen_s(&PLIK_TXT, making_or_reading_a_file_name(file_name, " ", 2), "r") != 0)
	{
		printf("+----------------------------------------------+\n");
		printf("|    There was a problem with file opening.    |\n");
		printf("|      CHECK THE FILE NAME AND EXTENSION       |\n");
		printf("|         Returning to Read Menu               |\n");
		printf("|           Please try again !                 |\n");
		printf("+----------------------------------------------+\n");
		Sleep(ERROR_TIME_SLEEP);
	}
	else if (check_if_file_empty(PLIK_TXT, file_name))
	{
		fscanf_s(PLIK_TXT, "%32s %d %d %d",
			my_addressbook->file_name, FILENAME_MAX,
			&my_addressbook->capacity,
			&my_addressbook->size,
			&temp_is_modified);
		my_addressbook->is_modified = temp_is_modified;
		printf("+---------------------------------------------------+\n");
		printf("| MY ADDRESS BOOK FILE NAME: %-23s|\n", my_addressbook->file_name);
		printf("| MY ADDRESS BOOK CAPACITY : %-23d|\n", my_addressbook->capacity);
		printf("| MY ADDRESS BOOK SIZE     : %-23d|\n", my_addressbook->size);
		printf("+---------------------------------------------------+\n");
		Sleep(TIME_SLEEP);
		for (int i = 0; i < my_addressbook->size; i++)
		{
			if (i == 0)
			{
				Contact* ptr_temp;
				ptr_temp = (Contact*)realloc(my_addressbook->contacts, my_addressbook->capacity * sizeof(Contact));
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
			fscanf_s(PLIK_TXT, "%d %32s %32s %16s %64s %32s %d\n",
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
	}
}

void read_from_file_semicolon_my_addressbook(AddressBook* my_addressbook)
{
	int temp_is_modified;
	int temp_actvice;
	FILE* PLIK_SEMICOLON_TXT;
	char file_name[FILENAME_MAX] = { '\0' };
	if (fopen_s(&PLIK_SEMICOLON_TXT, making_or_reading_a_file_name(file_name, " ", 2), "r") != 0)
	{
		printf("+----------------------------------------------+\n");
		printf("|    There was a problem with file opening.    |\n");
		printf("|      CHECK THE FILE NAME AND EXTENSION       |\n");
		printf("|         Returning to Read Menu               |\n");
		printf("|           Please try again !                 |\n");
		printf("+----------------------------------------------+\n");
		Sleep(ERROR_TIME_SLEEP);
	}
	else if (check_if_file_empty(PLIK_SEMICOLON_TXT, file_name))
	{
		fscanf_s(PLIK_SEMICOLON_TXT, "%[^;];%d;%d;%d",
			my_addressbook->file_name, FILENAME_MAX,
			&my_addressbook->capacity,
			&my_addressbook->size,
			&temp_is_modified);
		my_addressbook->is_modified = temp_is_modified;
		printf("+---------------------------------------------------+\n");
		printf("| MY ADDRESS BOOK FILE NAME: %-23s|\n", my_addressbook->file_name);
		printf("| MY ADDRESS BOOK CAPACITY : %-23d|\n", my_addressbook->capacity);
		printf("| MY ADDRESS BOOK SIZE     : %-23d|\n", my_addressbook->size);
		printf("+---------------------------------------------------+\n");
		Sleep(TIME_SLEEP);
		for (int i = 0; i < my_addressbook->size; i++)
		{
			if (i == 0)
			{
				Contact* ptr_temp;
				ptr_temp = (Contact*)realloc(my_addressbook->contacts, my_addressbook->capacity * sizeof(Contact));
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
	}
}

void bin_read_from_file_my_addressbook(AddressBook* my_addressbook)
{
	FILE* PLIK_BIN;
	char file_name[FILENAME_MAX] = { '\0' };
	if (fopen_s(&PLIK_BIN, making_or_reading_a_file_name(file_name, " ", 2), "rb+") != 0)
	{
		printf("+----------------------------------------------+\n");
		printf("|    There was a problem with file opening.    |\n");
		printf("|      CHECK THE FILE NAME AND EXTENSION       |\n");
		printf("|         Returning to Read Menu               |\n");
		printf("|           Please try again !                 |\n");
		printf("+----------------------------------------------+\n");
		Sleep(ERROR_TIME_SLEEP);
	}
	else if (check_if_file_empty(PLIK_BIN, file_name))
	{	
		fread_s(&my_addressbook->file_name, FILENAME_MAX, FILENAME_MAX, 1, PLIK_BIN);
		fread_s(&my_addressbook->capacity, sizeof(int), sizeof(int), 1, PLIK_BIN);
		fread_s(&my_addressbook->size, sizeof(int), sizeof(int), 1, PLIK_BIN);
		if (my_addressbook->capacity < my_addressbook->size)
		{
			my_addressbook->capacity = my_addressbook->size;
		}
		fread_s(&my_addressbook->is_modified, sizeof(bool), sizeof(bool), 1, PLIK_BIN);
		printf("+---------------------------------------------------+\n");
		printf("| MY ADDRESS BOOK FILE NAME: %-23s|\n", my_addressbook->file_name);
		printf("| MY ADDRESS BOOK CAPACITY : %-23d|\n", my_addressbook->capacity);
		printf("| MY ADDRESS BOOK SIZE     : %-23d|\n", my_addressbook->size);
		printf("+---------------------------------------------------+\n");
		Sleep(TIME_SLEEP);
		Contact* ptr_temp;
		ptr_temp = (Contact*)realloc(my_addressbook->contacts, my_addressbook->capacity * sizeof(Contact));
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
				fread_s(&my_addressbook->contacts[i], (my_addressbook->size * sizeof(Contact)), sizeof(Contact), 1, PLIK_BIN);
			}
			fclose(PLIK_BIN);
			printf("+-------------------------+\n");
			printf("|    READING SUCCESS !    |\n");
			printf("+-------------------------+\n");
			Sleep(TIME_SLEEP);
		}
	}
}

char* making_or_reading_a_file_name(char* file_name,char *Searched_String, int bin_txt)
{
	switch (bin_txt)
	{
	case 0:
		printf("+-----------------------------------------------------------------+\n");
		printf("|            Please provide name of the file in which,            |\n");
		printf("|                 the address book will be saved !                |\n");
		printf("|                   Name only, without extension.                 |\n");
		printf("|      Default extension: .bin and will be added automatically.   |\n");
		printf("+-----------------------------------------------------------------+\n");
		NEW_LINE;
		ASKING;
		read_string(file_name, FILENAME_MAX);
		char* file_name_bin = ".bin";
		strcat_s(file_name, FILENAME_MAX, file_name_bin);
		break;
	case 1:
		printf("+-----------------------------------------------------------------+\n");
		printf("|             Please provide name of the file in which,           |\n");
		printf("|                 the address book will be saved !                |\n");
		printf("|                   Name only, without extension.                 |\n");
		printf("|     Default extension: .txt and will be added automatically.    |\n");
		printf("+-----------------------------------------------------------------+\n");
		NEW_LINE;
		ASKING;
		read_string(file_name, FILENAME_MAX);
		char* file_name_txt = ".txt";
		strcat_s(file_name, FILENAME_MAX, file_name_txt);
		break;
	case 2:
		printf("+---------------------------------------------------------------+\n");
		printf("|          Enter name of the file you want to read !            |\n");
		printf("|              File name including the extension.               |\n");
		printf("+---------------------------------------------------------------+\n");
		NEW_LINE;
		ASKING;
		read_string(file_name, FILENAME_MAX);
		break;
	case 4:
		char* name_result = "Search_Result_For_";
		char* ground = "_On_";
		char* f_txt = ".txt";
		char current_time[FILENAME_MAX] = { '\0' };
		time_t ct;
		time(&ct);
		strcat_s(file_name, FILENAME_MAX, name_result);
		strcat_s(file_name, FILENAME_MAX, Searched_String);
		strcat_s(file_name, FILENAME_MAX, ground);
		ctime_s(current_time, FILENAME_MAX, &ct);
		strcat_s(file_name, FILENAME_MAX, current_time);
		for (int i = 0; i < strlen(file_name); i++)
		{
			if (file_name[i] == ' ' || file_name[i] == ':')
			{
				file_name[i] = '_';
			}
			else if (file_name[i] == '\n')
			{
				file_name[i] = '\0';
			}
		}
		strcat_s(file_name, FILENAME_MAX, f_txt);
		printf("FILE NAME: %s\n", file_name);
		break;
	case 5:
		printf("+---------------------------------------------------------------+\n");
		printf("|              Enter name of the Address Book !                 |\n");
		printf("+---------------------------------------------------------------+\n");
		NEW_LINE;
		ASKING;
		read_string(file_name, FILENAME_MAX);
		break;
	}
	return file_name;
}

void reading_from_file_add_to_my_adddressbook(AddressBook* my_addressbook)
{
	bool write = true;
	while (write)
	{
		printf("+--------------------------------------------------------+\n");
		printf("| +----------------------------------------------------+ |\n");
		printf("| |    Reading and adding to existing Address Book     | |\n");
		printf("| |                                                    | |\n");
		printf("| |          Available options below:                  | |\n");
		printf("| |                                                    | |\n");
		printf("| |      1. Read and Add from bin file.                | |\n");
		printf("| |      2. Read and Add from txt file.                | |\n");
		printf("| |      3. Read and Add from txt file with semicolon. | |\n");
		printf("| |      0. Exit                                       | |\n");
		printf("| +----------------------------------------------------+ |\n");
		printf("+--------------------------------------------------------+\n");
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
			FILE * PLIK_BIN;
			char file_name[FILENAME_MAX] = { '\0' };
			if (fopen_s(&PLIK_BIN, making_or_reading_a_file_name(file_name, " ", 2), "rb+") != 0)
			{
				printf("+----------------------------------------------+\n");
				printf("|    There was a problem with file opening.    |\n");
				printf("|      CHECK THE FILE NAME AND EXTENSION       |\n");
				printf("|         Returning to Read Menu               |\n");
				printf("|           Please try again !                 |\n");
				printf("+----------------------------------------------+\n");
				Sleep(ERROR_TIME_SLEEP);
			}
			else
			{
				int r_capacity;
				int r_size;
				char r_name_file[FILENAME_MAX];
				fread_s(&r_name_file, FILENAME_MAX, FILENAME_MAX, 1, PLIK_BIN);
				fread_s(&r_capacity, sizeof(int), sizeof(int), 1, PLIK_BIN);
				fread_s(&r_size, sizeof(int), sizeof(int), 1, PLIK_BIN);
				fread_s(&my_addressbook->is_modified, sizeof(bool), sizeof(bool), 1, PLIK_BIN);
				printf("+-------------------------------------------------------------+\n");
				printf("| MY ADDRESS BOOK FROM FILE: FILE NAME: %-22s|\n", r_name_file);
				printf("| MY ADDRESS BOOK FROM FILE: CAPACITY : %-22d|\n", r_capacity);
				printf("| MY ADDRESS BOOK FROM FILE: SIZE     : %-22d|\n", r_size);
				printf("+-------------------------------------------------------------+\n");
				Sleep(TIME_SLEEP);
				int target_size = my_addressbook->size + r_size;
				int target_capacity = target_size + (int)(target_size * 0.1);
				if (my_addressbook->capacity > target_size)
				{
					for (int i = my_addressbook->size; i < target_size; i++)
					{
						fread_s(&my_addressbook->contacts[i], (r_size * sizeof(Contact)), sizeof(Contact), 1, PLIK_BIN);
					}
					fclose(PLIK_BIN);
					printf("+-------------------------+\n");
					printf("|    READING SUCCESS !    |\n");
					printf("+-------------------------+\n");
					my_addressbook->size = target_size;
					my_addressbook->is_modified = true;
					organize_id(my_addressbook);
					fclose(PLIK_BIN);
					Sleep(TIME_SLEEP);
				}
				else if (my_addressbook->capacity == target_size || my_addressbook->capacity < target_size)
				{
					Contact* ptr_temp;
					ptr_temp = (Contact*)realloc(my_addressbook->contacts, target_capacity * sizeof(Contact));
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
						for (int i = my_addressbook->size; i < target_size; i++)
						{
							fread_s(&my_addressbook->contacts[i], (r_size * sizeof(Contact)), sizeof(Contact), 1, PLIK_BIN);
						}
						printf("+-------------------------+\n");
						printf("|    READING SUCCESS !    |\n");
						printf("+-------------------------+\n");
						my_addressbook->size = target_size;
						my_addressbook->capacity = target_capacity;
						my_addressbook->is_modified = true;
						organize_id(my_addressbook);
						fclose(PLIK_BIN);
						Sleep(TIME_SLEEP);
					}
				}
			}
			write = false;
			break;
		case 2:
			int temp_is_modified_2;
			int temp_actvice_2;
			FILE* PLIK_TXT;
			char file_name_2[FILENAME_MAX] = { '\0' };
			if (fopen_s(&PLIK_TXT, making_or_reading_a_file_name(file_name_2, " ", 2), "r") != 0)
			{
				printf("+----------------------------------------------+\n");
				printf("|    There was a problem with file opening.    |\n");
				printf("|      CHECK THE FILE NAME AND EXTENSION       |\n");
				printf("|         Returning to Read Menu               |\n");
				printf("|           Please try again !                 |\n");
				printf("+----------------------------------------------+\n");
				Sleep(ERROR_TIME_SLEEP);
			}
			else
			{
				int r_capacity;
				int r_size;
				char r_name_file[FILENAME_MAX];
				fscanf_s(PLIK_TXT, "%260s %d %d %d",
					r_name_file, FILENAME_MAX,
					&r_capacity,
					&r_size,
					&temp_is_modified_2);
				my_addressbook->is_modified = temp_is_modified_2;
				printf("+-------------------------------------------------------------+\n");
				printf("| MY ADDRESS BOOK FROM FILE: FILE NAME: %-22s|\n", r_name_file);
				printf("| MY ADDRESS BOOK FROM FILE: CAPACITY : %-22d|\n", r_capacity);
				printf("| MY ADDRESS BOOK FROM FILE: SIZE     : %-22d|\n", r_size);
				printf("+-------------------------------------------------------------+\n");
				Sleep(TIME_SLEEP);
				int target_size = my_addressbook->size + r_size;
				int target_capacity = target_size + (int)(target_size * 0.1);
				if (my_addressbook->capacity > target_size)
				{
					for (int i = my_addressbook->size; i < target_size; i++)
					{
						fscanf_s(PLIK_TXT, "%d %32s %32s %16s %64s %32s %d\n",
							&my_addressbook->contacts[i].ID,
							my_addressbook->contacts[i].name, MAX_NAME,
							my_addressbook->contacts[i].last_name, MAX_NAME,
							my_addressbook->contacts[i].phone_number, MAX_PHONE,
							my_addressbook->contacts[i].email_address, MAX_EMAIL,
							my_addressbook->contacts[i].company, MAX_NAME,
							&temp_actvice_2);
						my_addressbook->contacts[i].active = temp_actvice_2;
					}
					printf("+-------------------------+\n");
					printf("|    READING SUCCESS !    |\n");
					printf("+-------------------------+\n");
					my_addressbook->size = target_size;
					my_addressbook->capacity = target_capacity;
					organize_id(my_addressbook);
					Sleep(TIME_SLEEP);
				}
				else if (my_addressbook->capacity == target_size || my_addressbook->capacity < target_size)
				{
					Contact* ptr_temp;
					ptr_temp = (Contact*)realloc(my_addressbook->contacts, target_capacity * sizeof(Contact));
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
						for(int i = my_addressbook->size; i < target_size; i++)
						{
							fscanf_s(PLIK_TXT, "%d %32s %32s %16s %64s %32s %d\n",
								&my_addressbook->contacts[i].ID,
								my_addressbook->contacts[i].name, MAX_NAME,
								my_addressbook->contacts[i].last_name, MAX_NAME,
								my_addressbook->contacts[i].phone_number, MAX_PHONE,
								my_addressbook->contacts[i].email_address, MAX_EMAIL,
								my_addressbook->contacts[i].company, MAX_NAME,
								&temp_actvice_2);
							my_addressbook->contacts[i].active = temp_actvice_2;
						}
						printf("+-------------------------+\n");
						printf("|    READING SUCCESS !    |\n");
						printf("+-------------------------+\n");
						fclose(PLIK_TXT);
						my_addressbook->size = target_size;
						my_addressbook->capacity = target_capacity;
						organize_id(my_addressbook);
						Sleep(TIME_SLEEP);
					}
				}
				my_addressbook->is_modified = true;
				fclose(PLIK_TXT);
				write = false;
				break;
			}
		case 3:
			int temp_is_modified_3;
			int temp_actvice_3;
			FILE* PLIK_SEMICOLON_TXT;
			char file_name_3[FILENAME_MAX] = { '\0' };
			if (fopen_s(&PLIK_SEMICOLON_TXT, making_or_reading_a_file_name(file_name_3, " ", 2), "r") != 0)
			{
				printf("+----------------------------------------------+\n");
				printf("|    There was a problem with file opening.    |\n");
				printf("|      CHECK THE FILE NAME AND EXTENSION       |\n");
				printf("|         Returning to Read Menu               |\n");
				printf("|           Please try again !                 |\n");
				printf("+----------------------------------------------+\n");
				Sleep(ERROR_TIME_SLEEP);
			}
			else
			{
				int r_capacity;
				int r_size;
				char r_name_file[FILENAME_MAX];
				fscanf_s(PLIK_SEMICOLON_TXT, "%[^;];%d;%d;%d",
					r_name_file, FILENAME_MAX,
					&r_capacity,
					&r_size,
					&temp_is_modified_3);
				my_addressbook->is_modified = temp_is_modified_3;
				printf("+-------------------------------------------------------------+\n");
				printf("| MY ADDRESS BOOK FROM FILE: FILE NAME: %-22s|\n", r_name_file);
				printf("| MY ADDRESS BOOK FROM FILE: CAPACITY : %-22d|\n", r_capacity);
				printf("| MY ADDRESS BOOK FROM FILE: SIZE     : %-22d|\n", r_size);
				printf("+-------------------------------------------------------------+\n");
				Sleep(TIME_SLEEP);
				int target_size = my_addressbook->size + r_size;
				int target_capacity = target_size + (int)(target_size * 0.1);
				if (my_addressbook->capacity > target_size)
				{
					for (int i = my_addressbook->size; i < target_size; i++)
					{
						fscanf_s(PLIK_SEMICOLON_TXT, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d\n",
							&my_addressbook->contacts[i].ID,
							my_addressbook->contacts[i].name, MAX_NAME,
							my_addressbook->contacts[i].last_name, MAX_NAME,
							my_addressbook->contacts[i].phone_number, MAX_PHONE,
							my_addressbook->contacts[i].email_address, MAX_EMAIL,
							my_addressbook->contacts[i].company, MAX_NAME,
							&temp_actvice_3);
						my_addressbook->contacts[i].active = temp_actvice_3;
					}
					
					printf("+-------------------------+\n");
					printf("|    READING SUCCESS !    |\n");
					printf("+-------------------------+\n");
					my_addressbook->size = target_size;
					my_addressbook->capacity = target_capacity;
					organize_id(my_addressbook);
					Sleep(TIME_SLEEP);
				}
				else if (my_addressbook->size == target_size || my_addressbook->size < target_size)
				{
					Contact* ptr_temp;
					ptr_temp = (Contact*)realloc(my_addressbook->contacts, target_capacity * sizeof(Contact));
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
						for (int i = my_addressbook->size; i < target_size; i++)
						{
							fscanf_s(PLIK_SEMICOLON_TXT, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d\n",
								&my_addressbook->contacts[i].ID,
								my_addressbook->contacts[i].name, MAX_NAME,
								my_addressbook->contacts[i].last_name, MAX_NAME,
								my_addressbook->contacts[i].phone_number, MAX_PHONE,
								my_addressbook->contacts[i].email_address, MAX_EMAIL,
								my_addressbook->contacts[i].company, MAX_NAME,
								&temp_actvice_3);
							my_addressbook->contacts[i].active = temp_actvice_3;
						}
						printf("+-------------------------+\n");
						printf("|    READING SUCCESS !    |\n");
						printf("+-------------------------+\n");
						my_addressbook->size = target_size;
						my_addressbook->capacity = target_capacity;
						organize_id(my_addressbook);
						Sleep(TIME_SLEEP);
					}
				}
			}
			my_addressbook->is_modified = true;
			fclose(PLIK_SEMICOLON_TXT);
			write = false;
			break;
		default:
			printf("+--------------------------------------+\n");
			printf("|    Please chose right option!        |\n");
			printf("+--------------------------------------+\n");
			TRY;
			NEW_LINE;
			break;
		}
	}
}

bool check_if_file_empty(FILE* FILE_CHECK, char* file_name)
{
	bool result = false;
	rewind(FILE_CHECK);
	fseek(FILE_CHECK, 0, SEEK_END);
	long FILE_SIZE = ftell(FILE_CHECK);
	rewind(FILE_CHECK);
	if (FILE_SIZE == 0)
	{
		printf("+----------------------------------------------------------------+\n");
		printf("|    The size of the opened file is zero - the file is empty.    |\n");
		printf("|                     It cannot be read.                         |\n");
		printf("|                  The file will be closed                       |\n");
		printf("|                   Returning to the Menu.                       |\n");
		printf("+----------------------------------------------------------------+\n");
		result = false;
	}
	else if (FILE_SIZE > 0)
	{
		NEW_LINE;
		printf("+---------------------------------------------------------------+\n");
		printf("+---------------------------------------------------------------+\n");
		printf("|        PLEASE BE CAREFULL WITH OPENING AND READING FILE.      |\n");
		printf("|    DATA IN FILE COULD BE INCORECT, CORRUPTED OR INCOMPLETE !  |\n");
		printf("|                      FILE SIZE: %10d                    |\n", FILE_SIZE);
		printf("+---------------------------------------------------------------+\n");
		printf("+---------------------------------------------------------------+\n");
		NEW_LINE;
		result = true;
	}
	
	return result;
}

void check_capacity_size(AddressBook* my_addressbook)
{
	if (my_addressbook != NULL)
	{
		printf("+---------------------------------------------------+\n");
		printf("+---------------------------------------------------+\n");
		printf("+---------------------------------------------------+\n");
		printf("| MY ADDRESS BOOK NAME     : %-23s|\n", my_addressbook->file_name);
		printf("| MY ADDRESS BOOK CAPACITY : %-23d|\n", my_addressbook->capacity);
		printf("| MY ADDRESS BOOK SIZE     : %-23d|\n", my_addressbook->size);
		printf("+---------------------------------------------------+\n");
		printf("+---------------------------------------------------+\n");
		printf("+---------------------------------------------------+\n");
	}
	else
	{
		printf("my_addressbook == NULL\n");
	}
}