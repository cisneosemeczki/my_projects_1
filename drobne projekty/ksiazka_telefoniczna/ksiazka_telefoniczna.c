#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct kontakty
{
	char imie[100];
	char nazwisko[100];
	char numer[100];
	char grupa[100];
} kontakt;

typedef struct elementy
{
	kontakt kontakcik;
	struct elementy *poprzedni;
	struct elementy *nastepny;
} element;

element *push(char imie1[100], char nazwisko1[100], char numer1[100], char grupa1[100], element *nowy)
{
	strcpy(nowy->kontakcik.imie, imie1);
	strcpy(nowy->kontakcik.nazwisko, nazwisko1);
	strcpy(nowy->kontakcik.numer, numer1);
	strcpy(nowy->kontakcik.grupa, grupa1);
	return nowy;
}

element *pop(element *gora)
{
	element *tymczasowy = gora->poprzedni;
	free(gora);
	gora = tymczasowy;
	return gora;
}

void sczytanie_z_pliku(element **pierwszy)
{
	element *nowy;
	element *aktualny;
	FILE *plik;
	char imie[50], nazwisko[50], numer[50], grupa[50];

	plik = fopen("plik.csv", "r");
	if (plik == NULL)
	{
		puts("Nie istnieje plik z kontaktami!\n");
		return 0;
	}

	aktualny = NULL;
	while (!feof(plik))
	{
		nowy = (element*)calloc(1, sizeof(element));
		fscanf(plik, "%[^;];%[^;];%[^;];%s\n", imie, nazwisko, numer, grupa);
		nowy = push(imie, nazwisko, numer, grupa, nowy);

		if (aktualny == NULL) (*pierwszy) = nowy;
		else (*aktualny).nastepny = nowy;
		(*nowy).poprzedni = aktualny;
		aktualny = nowy;
	}
	(*aktualny).nastepny = NULL;

	printf("Kontakty zostaly sczytane z pliku!\n\n");
	fclose(plik);
}

void wyswietlenie(element *aktywny)
{
	int i=0;
	while (aktywny != NULL)
	{
		puts("__________________________________________________________________");
		printf("Imie:%s Nazwisko:%s Numer:%s Grupa:%s\n", (*aktywny).kontakcik.imie, (*aktywny).kontakcik.nazwisko, (*aktywny).kontakcik.numer, (*aktywny).kontakcik.grupa);
		aktywny = (*aktywny).nastepny;
		i++;
	}
	puts(" ");
	//printf("Ilosc kontakow %d\n", i);
}

void sortowanie_imion(element **pierwszy)
{
	element *aktywny;
	int a = 1;

	while (a != 0)
	{
		aktywny = (*pierwszy);
		a = 0;
		while ((*aktywny).nastepny != NULL)
		{
			if (strcoll((*aktywny).kontakcik.imie, (*(*aktywny).nastepny).kontakcik.imie) == 1)
			{
				if ((*aktywny).poprzedni == NULL) (*pierwszy) = (*aktywny).nastepny;
				else (*(*aktywny).poprzedni).nastepny = (*aktywny).nastepny;
				(*(*aktywny).nastepny).poprzedni = (*aktywny).poprzedni;
				(*aktywny).poprzedni = (*aktywny).nastepny;
				(*aktywny).nastepny = (*(*aktywny).poprzedni).nastepny;
				(*(*aktywny).poprzedni).nastepny = aktywny;
				if ((*aktywny).nastepny != NULL) (*(*aktywny).nastepny).poprzedni = aktywny;
				a++;
			}
			else aktywny = (*aktywny).nastepny;
		}
	}
	//printf("Posortowales kontakty wg imienia!\n");
}

void sortowanie_nazwisk(element **pierwszy)
{
	element *aktywny;
	int a = 1;

	while (a != 0)
	{
		aktywny = (*pierwszy);
		a = 0;
		while ((*aktywny).nastepny != NULL)
		{
			if (strcoll((*aktywny).kontakcik.nazwisko, (*(*aktywny).nastepny).kontakcik.nazwisko) == 1)
			{
				if ((*aktywny).poprzedni == NULL) (*pierwszy) = (*aktywny).nastepny;
				else (*(*aktywny).poprzedni).nastepny = (*aktywny).nastepny;
				(*(*aktywny).nastepny).poprzedni = (*aktywny).poprzedni;
				(*aktywny).poprzedni = (*aktywny).nastepny;
				(*aktywny).nastepny = (*(*aktywny).poprzedni).nastepny;
				(*(*aktywny).poprzedni).nastepny = aktywny;
				if ((*aktywny).nastepny != NULL) (*(*aktywny).nastepny).poprzedni = aktywny;
				a++;
			}
			else aktywny = (*aktywny).nastepny;
		}
	}
	//printf("Posortowales kontakty wg nazwiska!\n");
}

void szukanie_kontaktu(element *pierwszy)
{
	element *aktywny;
	char szukaj[50];
	int i,ilosc_znakow,a=0,b=0;

	puts("Szukaj posrod kontaktow: ");
	scanf("%49s", szukaj);
	//puts(" ");

	aktywny = pierwszy;
	while (aktywny != NULL)
	{
		if (strstr((*aktywny).kontakcik.imie, szukaj) != NULL || strstr((*aktywny).kontakcik.nazwisko, szukaj) != NULL || strstr((*aktywny).kontakcik.grupa, szukaj) != NULL || strstr((*aktywny).kontakcik.numer, szukaj) != NULL)
		{
			puts("__________________________________________________________________");
			printf("Imie:%s Nazwisko:%s Numer:%s Grupa:%s\n", (*aktywny).kontakcik.imie, (*aktywny).kontakcik.nazwisko, (*aktywny).kontakcik.numer, (*aktywny).kontakcik.grupa);
			a = 1;
		}
		aktywny = (*aktywny).nastepny;
	}
	szukaj[0] = szukaj[0] - 32;
	ilosc_znakow = strlen(szukaj);
	for (i = 1; i < ilosc_znakow; i++)
	{
		if (szukaj[i]<96) szukaj[i] = szukaj[i] + 32;
	}
	aktywny = pierwszy;
	while (aktywny != NULL)
	{
		if (strstr((*aktywny).kontakcik.imie, szukaj) != NULL || strstr((*aktywny).kontakcik.nazwisko, szukaj) != NULL || strstr((*aktywny).kontakcik.grupa, szukaj) != NULL)
		{
			if (a == 0) puts("__________________________________________________________________");
			if (a == 0) printf("Imie:%s Nazwisko:%s Numer:%s Grupa:%s\n", (*aktywny).kontakcik.imie, (*aktywny).kontakcik.nazwisko, (*aktywny).kontakcik.numer, (*aktywny).kontakcik.grupa);
			b = 1;
		}
		aktywny = (*aktywny).nastepny;
	}
	for (i = 0; i < ilosc_znakow; i++)
	{
		if(szukaj[i]<96) szukaj[i] = szukaj[i] + 32;
	}
	aktywny = pierwszy;
	while (aktywny != NULL)
	{
		if (strstr((*aktywny).kontakcik.imie, szukaj) != NULL || strstr((*aktywny).kontakcik.nazwisko, szukaj) != NULL || strstr((*aktywny).kontakcik.grupa, szukaj) != NULL)
		{
			if (a != 1 && b != 1) puts("__________________________________________________________________");
			if (a != 1 && b != 1) printf("Imie:%s Nazwisko:%s Numer:%s Grupa:%s\n", (*aktywny).kontakcik.imie, (*aktywny).kontakcik.nazwisko, (*aktywny).kontakcik.numer, (*aktywny).kontakcik.grupa);
		}
		aktywny = (*aktywny).nastepny;
	}
	puts(" ");
}

void dodawanie_kontaktu(element **pierwszy)
{
	element *nowy;
	element *aktualny;
	char imie[100], nazwisko[100], numer[100], grupa[100];

	puts("Podaj imie: ");
	scanf("%99s", imie);
	puts("Podaj nazwisko: ");
	scanf("%99s", nazwisko);
	puts("Podaj numer: ");
	scanf("%99s", numer);
	puts("Podaj grupe: ");
	scanf("%99s", grupa);
	
	nowy = (element*)calloc(1, sizeof(element));
	nowy = push(imie, nazwisko, numer, grupa, nowy);

	aktualny = (*pierwszy);
	if (aktualny == NULL)
	{
		(*pierwszy) = nowy;
		(*pierwszy)->nastepny = NULL;
		puts("Dodales kontakt!\n");
		return 0;
	}
	
	while ((*aktualny).nastepny != NULL) aktualny = (*aktualny).nastepny;
	(*aktualny).nastepny = nowy;
	(*nowy).poprzedni = aktualny;
	(*nowy).nastepny = NULL;
	puts("Dodales kontakt!\n");
}

void usuwanie_kontaktu(element **pierwszy)
{
	element *aktywny;
	char numer[100];
	int nr,i,a=0;

	aktywny = (*pierwszy);
	while (aktywny != NULL)
	{
		aktywny = (*aktywny).nastepny;
		a++;
	}
	printf("Ilosc kontaktow: %d\n",a);

	poczatek2:
	puts("Wybierz numer kontaktu do usuniecia: ");
	rewind(stdin);
	fgets(numer, 100, stdin);
	nr = atoi(numer);
	if ((nr < 1) || (nr > a))
	{
		puts("Nie ma takiego kontaktu na liscie!\n");
		goto poczatek2;
	}
	
	aktywny = (*pierwszy);
	for(i = 1; i < nr; i++) aktywny = (*aktywny).nastepny;

	if (nr == 1)
	{
		free(aktywny);
		(*pierwszy) = NULL;
	}
	else if ((*aktywny).poprzedni == NULL)
	{
		(*pierwszy) = (*aktywny).nastepny;
		(*(*aktywny).nastepny).poprzedni = NULL;
		free(aktywny);
	}
	else if ((*aktywny).nastepny == NULL)
	{
		(*(*aktywny).poprzedni).nastepny = NULL;
		free(aktywny);
	}
	else
	{
		(*(*aktywny).poprzedni).nastepny = (*aktywny).nastepny;
		(*(*aktywny).nastepny).poprzedni = (*aktywny).poprzedni;
	}
	printf("Usunales %d kontakt!\n\n", nr);
}

void czyszczenie(element **pierwszy)
{
	element *aktywny;
	int nr=0,i,j,k;

	aktywny = (*pierwszy);
	while (aktywny != NULL)
	{
		aktywny = (*aktywny).nastepny;
		nr++;
	}
	k = nr;

	for (j = 1; j < nr; j++)
	{
		aktywny = (*pierwszy);
		for (i = 1; i < k; i++) aktywny = (*aktywny).nastepny;

		if (k == 1)
		{
			free(aktywny);
			(*pierwszy) = NULL;
		}
		else if ((*aktywny).nastepny == NULL)
		{
			(*(*aktywny).poprzedni).nastepny = NULL;
			free(aktywny);
		}
		k--;
	}
	printf("Wyczysciles kontakty!\n", nr);
}

void main(void)
{
	element *pierwszy;
	char opcja1[100], opcja2[100];
	int opcja, a=0,b=0;

	pierwszy = NULL;

	printf("[PATRYK FISCHER 237403]\n");
	printf("[Menu programu]\n");
	printf("1. Wczytanie kontaktow z pliku.\n");
	printf("2. Wyswietlenie listy kontaktow.\n");
	printf("3. Sortowanie kontaktow.\n");
	printf("4. Szukanie kontaktow.\n");
	printf("5. Dodanie kontaktu.\n");
	printf("6. Usuniecie kontaktu.\n");
	printf("7. Wyjscie z programu.\n \n");

	while (1)
	{
		poczatek3:
		puts("Opcja programu: ");
		rewind(stdin);
		fgets(opcja1, 100, stdin);
		opcja = atoi(opcja1);
		switch (opcja)
		{
		case 1: {
			sczytanie_z_pliku(&pierwszy);
			a = 0;
			b = 1;
		}; break;
		case 2: {
			if (b == 0)
			{
				puts("Nie masz zadnych kontaktow!\n\n");
				goto poczatek3;
			}
			wyswietlenie(pierwszy);
		}; break;
		case 3: {
			if (b == 0)
			{
				puts("Nie masz zadnych kontaktow!\n\n");
				goto poczatek3;
			}
			printf("1. Sortowanie wg imienia.\n");
			printf("2. Sortowanie wg nazwiska.\n");
			poczatek1:
			puts("Opcja sortowania: ");
			rewind(stdin);
			fgets(opcja2, 100, stdin);
			opcja = atoi(opcja2);
			switch (opcja)
			{
			case 1: {
				sortowanie_imion(&pierwszy);
				printf("Posortowales kontakty wg imienia!\n\n");
				a = 1;
			}; break;
			case 2: {
				sortowanie_nazwisk(&pierwszy);
				printf("Posortowales kontakty wg nazwiska!\n\n");
				a = 2;
			}; break;
			default: {
				if ((opcja < 1) || (opcja > 2))
				{
					printf("Nie ma takiej opcji!\n\n");
					goto poczatek1;
				}
			}; break;
			}
		}; break;
		case 4: {
			if (b == 0)
			{
				puts("Nie masz zadnych kontaktow!\n\n");
				goto poczatek3;
			}
			szukanie_kontaktu(pierwszy);
		}; break;
		case 5: {
			if (a == 0) dodawanie_kontaktu(&pierwszy);
			if (a == 1)
			{
				dodawanie_kontaktu(&pierwszy);
				sortowanie_imion(&pierwszy);
			}
			if (a == 2)
			{
				dodawanie_kontaktu(&pierwszy);
				sortowanie_nazwisk(&pierwszy);
			}
			b = 1;
		}; break;
		case 6: {
			if (b == 0)
			{
				puts("Nie masz zadnych kontaktow!\n\n");
				goto poczatek3;
			}
			usuwanie_kontaktu(&pierwszy);
			if (pierwszy == NULL) b = 0;
		}; break;
		case 7: {
			//free(pierwszy);
			czyszczenie(&pierwszy);
			system("PAUSE");
			exit(0);
		}; break;
		default: {
			if ((opcja < 1) || (opcja > 7))
			{
				printf("Nie ma takiej opcji!\n\n");
			}
		}; break;
		}
	}

	system("PAUSE");
}