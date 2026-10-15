#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <Windows.h>
#include <ctype.h>


#define ASKING printf("Your choose: ")
#define WRONG printf("Wrong choice !")
#define TRY printf("Try again...")
#define NEW_LINE printf("\n")

#define YES 'Y'
#define NO 'N'
#define LIMIT_FIELDS 5

#define MAX_PHONE 16
#define MAX_NAME 32
#define MAX_FILENAME 32
#define MAX_EMAIL 64

#define START_CAPACITY 2

#define FILE_NAME "AdressBook.txt"

#define TIME_SLEEP 250

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
	bool is_modifed;
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
	Allows for the initialization of struct pointers.
*/
AddressBook *init_struct();

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
int check_id(AddressBook* my_addressbook);

/*
	Main menu for search function in contacts.
*/
void search_contacts_main(AddressBook* my_addressbook);

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
void search_by_all_Contacts(AddressBook* my_addressbook, int field_number, char letter_case);

/*
	Function is giving a pointer to structur fields, using pointer array.
*/
char* all_fields_in_array(AddressBook* my_addressbook, int i, int k);