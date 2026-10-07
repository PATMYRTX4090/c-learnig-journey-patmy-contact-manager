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

#ifndef CONTACT_H
#define CONTACT_H

typedef struct 
{
	int ID;
	char name[MAX_NAME];
	char last_name[MAX_NAME];
	char phone_number[MAX_PHONE];
	char email_adress[MAX_EMAIL];
	bool active;
}Contact;

#endif // !CONTACT_H

#ifndef ADRESSBOOK_H
#define ADRESSBOOK_H
typedef struct
{
	Contact* contats;
	int capacitAB;
	int sizeAB;
	char file_name[MAX_FILENAME];
	bool is_modifedAB;
}AdressBook;
#endif // !ADRESSBOOK_H



void enteroMania(void);
int taking_number(void);
char* read_string(char* Tablica, int T_Size);
