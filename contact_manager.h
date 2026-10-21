#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <Windows.h>
#include <ctype.h>


/*
	String: Your choose.
*/
#define ASKING printf("Your choose: ")

/*
	String: Wrong choice !
*/
#define WRONG printf("Wrong choice !")

/*
	String: Try again..
*/
#define TRY printf("Try again...")


/*
	Control sequence: '\n'
*/
#define NEW_LINE printf("\n")

/*
	Char value equal to 'Y' == 1.
*/
#define YES 'Y'

/*
	Char value equal to 'N' == 0.
*/
#define NO 'N'

/*
	Value defining size of the pointer array.
*/
#define LIMIT_FIELDS 5

/*
	Specifies the size of the structure field: name and last_name.
*/
#define MAX_NAME 32

/*
	Specifies the size of the file name for reading and writing.
*/
#define MAX_FILENAME 32

/*
	Specifies the size of the structure field: phone_number.
*/
#define MAX_PHONE 16

/*
	Specifies the size of the structure field: email_address.
*/
#define MAX_EMAIL 64

/*
	Initial size of the Contacts structure.
*/
#define START_CAPACITY 2

/*
	Memory data block equal to 1
*/
#define DATA_BLOCK 1

/*
	String for file names. 
*/
#define FILE_NAME "AddressBook.txt"
#define SEMICOLON_FILE_NAME "Semicolon_AddressBook.txt"
#define BIN_FILE_NAME "AddressBook.bin"
#define SEARCH_FILE_NAME "SearchResult.txt"

/*
	Value in ms, specifying the sleep duration for the Sleep() function.
*/
#define TIME_SLEEP 250
/*
	Value in ms, specifying the sleep duration for the Sleep() when error occured!
*/
#define ERROR_TIME_SLEEP 500

#ifndef CONTACT_H
#define CONTACT_H
typedef struct 
{
	int ID;
	char name[MAX_NAME];
	char last_name[MAX_NAME];
	char phone_number[MAX_PHONE];
	char email_address[MAX_EMAIL];
	char company[MAX_NAME];
	bool active;
}Contact;

#endif // !CONTACT_H

#ifndef ADRESSBOOK_H
#define ADRESSBOOK_H
typedef struct
{
	Contact* contacts;
	char file_name[MAX_FILENAME];
	int capacity;
	int size;
	bool is_modified;
}AddressBook;
#endif // !ADRESSBOOK_H

typedef enum 
{
	SEARCH_NAME,
	SEARCH_LAST_NAME,
	SEARCH_PHONE_NUMEBER,
	SEARCH_EMAIL_ADDRESS,
	SEARCH_COMPANY
}Enum_Struct_Fields;

/*
	Removing unwanted characters from stdin.
*/
void eat_char(void);

/*
	Allows reading a digit from stdin.
*/
int taking_number(void);

/*
	Allows reading character from stdin.
*/
char get_letter(void);

/*
	Allows to read a chain string from stdin. 
*/
char* read_string(char* Tablica, int T_Size);

/*
	Initializes the variable my_adressbook->contatc->active to false value.
*/
void init_active(AddressBook* my_adressbook);

/*
	Frees the memory of initialized pointers.
*/
void cleanup_struct(AddressBook *my_adressbook);

/*
	Function enables data entry into the structures. Usues the realloc() function to increase
	the allocated memory. Locates the end of the dynamic array. 
*/
void complete_struct(AddressBook *my_adressbook);

/*
	Function displays the contact structure. Includes a safegurad against an empty structure.
*/
void view_struct(const AddressBook *my_adressbook);

/*
	The function allocates additional memory for the Contact structure.
*/
Contact *more_contacts(AddressBook* my_addressbook);

/*
	Deleting contact and moving rest. 
*/
void delete_contact(AddressBook* my_addressbook);

/*
	Function that assists in determing the correct ID contact.
*/
int check_id(AddressBook* my_addressbook, bool EDIT_MODE);

/*
	Main menu for search function in contacts.
*/
void search_contacts_main(AddressBook* my_addressbook, bool EDIT_MODE);

/*
	Complements the search functions.
*/
char ask_letter_case(void);

/*
	Function displays all found contacts that match the searching string. Includes a safegurad against an empty structure.
*/
void view_result_struct(const AddressBook* my_addressbook, int* ScoreBoard, int SizeScoreBoard);

/*
	Function searching by structur fields - choosen by user. Enum.
*/
void search_by_Contacts(AddressBook* my_addressbook, int field_number, char letter_case);

/*
	Function allows to get right pointer to structur fields - choosen by user.
*/
char* selecting_right_field(AddressBook* my_addressbook, int field_number, int i);

/*
	Function searching by all structur fields. Enum and pointer array.
*/
void search_by_all_Contacts(AddressBook* my_addressbook, char letter_case);

/*
	Function is giving a pointer to structur fields, using pointer array.
*/
char* all_fields_in_array(AddressBook* my_addressbook, int i, int k);

/*
	Mian function taht introduce a edit contact.
*/
void edit_contacts_main(AddressBook* my_addressbook);

/*
	Function allow to chenge a specific field of the struct or all of them. 
*/
void edit_contact(AddressBook* my_addressbook, int edit_ID, int field_number, bool edit_all);

/*
	Functions check data sccuracy for struct fields: phone number and mail address.
	when: 
	check_field == 0 -> checking phone number,
	check_field == 1 -> checking email_address.
*/
void data_accuracy_mail_and_phone(Contact* wsk_current_contact, int check_field);

/*
	Main menu for saving struct.
*/
void saving_struct_to_file_main(AddressBook* my_addressbook);

/*
	Function allows to save Addressbook and Contacts to file in text mode.
*/
void save_to_file_my_addressbook(AddressBook* my_addressbook);

/*
	Function allows to save Addressbook and Contacts to file in text mode - fields separeted with semicolon.
*/
void save_to_file_semicolon_my_addressbook(AddressBook* my_addressbook);

/*
	Function allows to save a search results to file in text mode.
*/
void save_to_file_searched_contacts(AddressBook* my_addressbook, int* ScoreBoard, int SizeScoreBoard);

/*
	Function allows to save a search results to file in text mode, fields separated with semicolons.
*/
void save_to_file_searched_semicolon_contacts(AddressBook* my_addressbook, int* ScoreBoard, int SizeScoreBoard);

/*
 	Function allows to save Addressbook and Contacts to file in binary mode.
*/
void bin_save_file_my_addressbook(AddressBook* my_addressbook);

/*
	Check status of the AddressBook is modified.
*/
void is_struct_saved_to_file(AddressBook* my_addressbook);

/*
	Main menu for reading struct.
*/
AddressBook* reading_struct_from_file_main();

/*
	Function for reading struct from file in text mode.
*/
AddressBook* read_from_file_my_addressbook();

/*
	Function for reading struct from file in text mode - fields separeted with semicolon.
*/
AddressBook* read_from_file_semicolon_my_addressbook();

/*
	 Function for reading struct from file in binare mode.
*/
AddressBook* bin_read_from_file_my_addressbook();

/*
	All initialization function in one place.
	0 - for initialization during application startup!
	1 - for initialization during application reading file bin or txt!
*/
AddressBook* init_struct_main(int type_init);




