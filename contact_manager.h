#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <Windows.h>

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