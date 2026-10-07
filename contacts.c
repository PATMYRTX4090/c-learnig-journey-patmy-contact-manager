#include "contact_manager.h"


void enteroMania(void)
{
	while (getchar() != '\n')
	{
		continue;
	}
}

int taking_number(void)
{
	int Moja_Cyfra;
	while (scanf_s("%d", &Moja_Cyfra) != 1)
	{
		printf("Wprowadz prawidlowa cyfre!\n");
		printf("Kontynuj...\n");
		break;
	}
	enteroMania(); //Funkcja :)
	return Moja_Cyfra;
}

char* read_string(char* Tablica, int T_Size)
{
	char* Adres_Lancucha;
	Adres_Lancucha = fgets(Tablica, T_Size, stdin);
	if (Adres_Lancucha)
	{
		while (*Tablica != '\n' && *Tablica != '\0')
		{
			Tablica++;
		}
		if (*Tablica == '\n')
		{
			*Tablica = '\0';
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