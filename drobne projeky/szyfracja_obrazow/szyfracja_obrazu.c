#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct obrazek
{
	int szerokosc, wysokosc, jasnosc;
	int *piksele;
	char nazwa_obrazu[100];
} obraz;

obraz *tworzenie_tablicy_na_piksele(obraz *tablica_struktur, int i, int szerokosc, int wysokosc)
{
	int k;

	if (tablica_struktur != NULL)
	{
		tablica_struktur[i].piksele = (int*)calloc(wysokosc*szerokosc, sizeof(int));
	}
	else
	{
		free(tablica_struktur);
		return 0;
	}
	return tablica_struktur;
}

obraz *wczytywanie_obrazu(obraz *tablica_struktur, int numer_obrazu, int deszyfracja, int *wyjscie)
{
	FILE *plik;
	int szerokosc, wysokosc, jasnosc;
	int i, j, k = 0;
	char nazwa_pliku[100], nazwa_pliku_temp[100], hmm[10], znaki[3], cs[10];   //tablica cs->czy_szyfrowane, sprawdza czy plik byl szyfrowany
	char znak;

poczatek0:
	if (deszyfracja != 2)
	{
		puts("Podaj nazwe pliku (bez .ppm): ");
		scanf("%99s", nazwa_pliku);
		if (deszyfracja != 1) strcpy(tablica_struktur[numer_obrazu].nazwa_obrazu, nazwa_pliku);
	}
	if (deszyfracja == 2)
	{
		//strcpy(nazwa_pliku, tablica_struktur[0].nazwa_obrazu);
		strcpy(nazwa_pliku, "fiszowi");
		//strcpy(hmm, ".ppm");
		//strcat(nazwa_pliku, hmm);
		//plik = fopen(nazwa_pliku_temp, "r");
		//fscanf(plik, "%2s", znaki);
		//fscanf(plik, "%8s", cs);
		//fscanf(plik, "%99s", nazwa_pliku);
		//fclose(plik);
	}
	//fgets(nazwa_pliku, 100, stdin);
	strcpy(hmm, ".ppm");
	strcat(nazwa_pliku, hmm);

	plik = fopen(nazwa_pliku, "r");
	if (plik != NULL)
	{
		if (fscanf(plik, "%2s", znaki) == 1 && znaki[0] == 'P' && (znaki[1] == '3' || znaki[1] == '6'))
		{
			if (deszyfracja == 1)
			{
				if (fscanf(plik, "%9s", cs) == 1 && cs[0] == '#' && cs[1] == 's' && cs[2] == 'z' && cs[3] == 'y' && cs[4] == 'f' && cs[5] == 'r' && cs[6] == '@' && cs[7] == '@' && cs[8] == '@')
				{
					printf("Ten plik byl szyfrowany, zaraz nastapi proces deszyfracji!\n\n");
					fscanf(plik, " %c", &znak);
					fscanf(plik, "%99s", nazwa_pliku_temp);
					//printf("nazwa pliku: %s\n", nazwa_pliku_temp);
					strcpy(tablica_struktur->nazwa_obrazu, nazwa_pliku_temp);
					//printf("nazwa pliku: %s\n", tablica_struktur->nazwa_obrazu);
				}
				else
				{
					fclose(plik);
					printf("Ten plik nie byl szyfrowany!\n");
					(*wyjscie) = 1;
					return 0;
				}
			}
			szerokosc = sczytanie_wartosci(plik);
			szerokosc = 3 * szerokosc;
			wysokosc = sczytanie_wartosci(plik);
			jasnosc = sczytanie_wartosci(plik);
			tworzenie_tablicy_na_piksele(tablica_struktur, numer_obrazu, szerokosc, wysokosc);
			if (tablica_struktur != NULL)
			{
				tablica_struktur[numer_obrazu].szerokosc = szerokosc;
				tablica_struktur[numer_obrazu].wysokosc = wysokosc;
				tablica_struktur[numer_obrazu].jasnosc = jasnosc;
				//strcpy(tablica_struktur[numer_obrazu].nazwa_obrazu, nazwa_pliku);

				for (i = 0; i < wysokosc; i++)
				{
					for (j = 0; j < szerokosc; j++)
					{
						tablica_struktur[numer_obrazu].piksele[k] = sczytanie_wartosci(plik);
						k++;
					}
				}
			}
		}
	}
	else
	{
		printf("Nie udalo sie otworzyc pliku!\n\n");
		//goto poczatek0;
		(*wyjscie) = 1;
		return 0;
	}

	//printf("jasnosc wynosi %d\n", tablica_struktur[numer_obrazu].jasnosc);
	//printf("jakis piksel wynosi %d\n", tablica_struktur[numer_obrazu].piksele[0][1]);
	fclose(plik);

	return tablica_struktur;
}

obraz* zwalnianie_pamieci_pikseli(obraz *tablica, int ilosc_obrazow)
{
	int i, j;

	for (j = 0; j < ilosc_obrazow; j++)
	{
		free(tablica->piksele);
	}
	free(tablica);
	tablica = NULL;
	return tablica;
}

int sczytanie_wartosci(FILE *plik)
{
	int wartosc;
	char znak[2];

	while (1)
	{
		if (fscanf(plik, "%d", &wartosc) == 1)
			return wartosc;
		if (fscanf(plik, "%1s", znak) == 1 && znak[0] == '#')
			fscanf(plik, "%*[^\n]");
		//else return -1;
	}
}

int zamiana_dziesietnych_na_binarne(int liczba, int *tab)
{
	//int *tab;
	int i = 7, j;

	tab = calloc(8, sizeof(int));

	//printf("Zamiana z systemu dziesietnego na binarny\n");
	//printf("Wprowadz liczbe w systemie dziesietnym: ");
	//scanf("%d", &liczba);

	while (liczba>0)
	{
		tab[i--] = liczba % 2;
		liczba = liczba / 2;
	}
	//for (j = i - 1; j >= 0; j--)
	/*for (j = 0; j<8; j++)
	{
		printf("%d", tab[j]);
	}*/
	return tab;
}

int zamiana_binarnych_na_dziesietne(int *tab)
{
	int liczba;

	liczba = tab[7] * 1 + tab[6] * 2 + tab[5] * 4 + tab[4] * 8 + tab[3] * 16 + tab[2] * 32 + tab[1] * 64 + tab[0] * 128;
	return liczba;
}

void zapis_obrazu_do_pliku(obraz *tablica, int aktywny_obraz, int szyfracja)
{
	FILE *plik;
	int i, j, k=0;
	char nazwa_pliku[100], hmm[10];

	if (szyfracja == 0)
	{
		strcpy(nazwa_pliku, tablica[0].nazwa_obrazu);
		strcpy(hmm, ".ppm");
		strcat(nazwa_pliku, hmm);
	}
	else
	{
		puts("Podaj jak ma sie nazywac zaszyfrowany plik (bez .ppm): ");
		//fgets(nazwa_pliku, 100, stdin);
		scanf("%99s", nazwa_pliku);
		strcpy(hmm, ".ppm");
		strcat(nazwa_pliku, hmm);
	}

	plik = fopen(nazwa_pliku, "w");
	fprintf(plik, "P3\n");
	if (szyfracja == 1)
	{
		fprintf(plik, "#szyfr@@@\n");
		//fprintf(plik, "#s\n");
		fprintf(plik, "#%s\n", tablica->nazwa_obrazu);
	}
	fprintf(plik, "%d %d\n", (tablica[aktywny_obraz].szerokosc)/3, tablica[aktywny_obraz].wysokosc);
	fprintf(plik, "%d\n", tablica[aktywny_obraz].jasnosc);
	for (i = 0; i < tablica[aktywny_obraz].wysokosc; i++)
	{
		for (j = 0; j < tablica[aktywny_obraz].szerokosc; j++)
		{
			fprintf(plik, "%d ", tablica[aktywny_obraz].piksele[k]);
			k++;
		}
		fprintf(plik, "\n");
	}
	fclose(plik);
	printf("Pliczek zostal utworzony!\n \n");
}

void szyfracja_obrazu()
{
	obraz* tablica_struktur = NULL;
	int ilosc_pikseli,dlugosc_szyfru,asci,asci_p;
	int ilosc_liter_szyfru_max;
	char *szyfr,buff[1];
	int i,j,k=0,l;
	int *tab_asci,*tab_asci_p;
	int *wyjscie = 0;

	tablica_struktur = (obraz*)calloc(1, sizeof(obraz));

	tablica_struktur = wczytywanie_obrazu(tablica_struktur, 0, 0, &wyjscie);
	if (wyjscie == 1) return 0;
	printf("Wczytano obraz o nazwie %s!\n\n", tablica_struktur[0].nazwa_obrazu);

	fgets(buff, 1, stdin);
	rewind(stdin);

	ilosc_pikseli = tablica_struktur->szerokosc*tablica_struktur->wysokosc;
	ilosc_liter_szyfru_max = ilosc_pikseli / 24;

	printf("MAX liter szyfru wynosi: %d\n", ilosc_liter_szyfru_max);

	szyfr = malloc(ilosc_liter_szyfru_max * sizeof(char));

	printf("Podaj tekst jaki chcesz zaszyfrowac: ");
	fgets(szyfr, ilosc_liter_szyfru_max, stdin);

	dlugosc_szyfru = strlen(szyfr);
	//printf("Dlugosc szyfru wynosi: %d\n", dlugosc_szyfru);

	for (i = 2; i < (dlugosc_szyfru-1) * 24; i = i + 24)
	{
		asci = (int)szyfr[k];
		tab_asci = calloc(8, sizeof(int));
		tab_asci = zamiana_dziesietnych_na_binarne(asci, tab_asci);
		/*for (j = 0; j < 8; j++)
		{
			printf("%d", tab_asci[j]);
		}
		printf("\n");
		system("PAUSE");*/
		l = 0;
		for (j = i; j < i + 24; j = j + 3)
		{
			asci_p = (int)tablica_struktur->piksele[j];
			tab_asci_p = calloc(8, sizeof(int));
			tab_asci_p = zamiana_dziesietnych_na_binarne(asci_p, tab_asci_p);
			//printf("%d\n", tab_asci[l]);
			tab_asci_p[7] = tab_asci[l];
			tablica_struktur->piksele[j] = zamiana_binarnych_na_dziesietne(tab_asci_p);
			//printf("%d\n", tablica_struktur->piksele[j]);
			l++;
			free(tab_asci_p);
		}
		free(tab_asci);
		k++;
	}
	//printf("i wynosi: %d\n", i);
	//printf("k wynosi: %d\n", k);
	for (j = i; j < i + 24; j = j + 3)
	{
		asci_p = (int)tablica_struktur->piksele[j];
		tab_asci_p = calloc(8, sizeof(int));
		tab_asci_p = zamiana_dziesietnych_na_binarne(asci_p, tab_asci_p);
		tab_asci_p[7] = 0;
		tablica_struktur->piksele[j] = zamiana_binarnych_na_dziesietne(tab_asci_p);
		free(tab_asci_p);
	}

	printf("Udalo Ci sie zaszyfrowac tekst w obrazie!\n\n");
	zapis_obrazu_do_pliku(tablica_struktur, 0, 1);

	tablica_struktur = zwalnianie_pamieci_pikseli(tablica_struktur, 1);

}

void deszyfracja_obrazu()
{
	obraz* tablica_struktur = NULL;
	obraz* tablica_struktur_2 = NULL;
	int ilosc_obrazow = 2;
	int asci=97,dlugosc_szyfru;
	int i = 2,j,k,l=0,m;
	int *tab_asci, *tab_asci_p;  //tab_asci_p -> tablica kodu ascii piksela w postaci binarnej
	char *szyfr,ole;
	int *wyjscie = 0;

	tablica_struktur = (obraz*)calloc(1, sizeof(obraz));
	//tablica_struktur_2 = (obraz*)calloc(1, sizeof(obraz));

	tablica_struktur = wczytywanie_obrazu(tablica_struktur, 0, 1, &wyjscie);
	if (wyjscie == 1) return 0;
		//printf("nazwa pliku: %s\n", tablica_struktur[0].nazwa_obrazu);
		/*for (j = i; j < i + 24; j = j + 3)
		{
			printf("%d\n", tablica_struktur->piksele[j]);
		}
		system("PAUSE");*/
		//tablica_struktur = wczytywanie_obrazu(tablica_struktur_2, 0, 2);

	szyfr = calloc(1,sizeof(char));

	printf("Szyfr: ");

	while (asci != 0)
	{
		//if (l == 0) szyfr = malloc(sizeof(char));
		if (l!=0) szyfr = realloc(szyfr, (l + 1) * sizeof(char));
		
		tab_asci = calloc(8, sizeof(int));
		k = 0;

		for (j = i; j < i + 24; j = j + 3)
		{
			tab_asci_p = calloc(8, sizeof(int));
			//printf("%d\n", tablica_struktur->piksele[j]);
			tab_asci_p = zamiana_dziesietnych_na_binarne(tablica_struktur->piksele[j], tab_asci_p);
			/*for (m = 0; m < 8; m++)
			{
				printf("%d", tab_asci_p[m]);
			}
			printf("\n");*/
			tab_asci[k] = tab_asci_p[7];
			//printf("%d\n", tab_asci[k]);
			//system("PAUSE");
			//tablica_struktur[0].piksele[j] = tablica_struktur_2[0].piksele[j];
			k++;
			free(tab_asci_p);
		}
		asci = zamiana_binarnych_na_dziesietne(tab_asci);
		//printf("%d\n", asci);
		//system("PAUSE");

		if (asci==0) realloc(szyfr, l * sizeof(char));
		else 
		{
			szyfr[l] = (char)asci;
			printf("%c", szyfr[l]);
			l++;
		}

		i = i + 24;
		free(tab_asci);
	}

	printf("\n\n");
	/*dlugosc_szyfru = strlen(szyfr);
	printf("Dlugosc szyfru wynosi: %d\n", dlugosc_szyfru);


	printf("Szyfr: ");
	for (m = 0; m < l+1; m++)
	{
		printf("%c", szyfr[l]);
	}
	printf("\n");
	//printf("Szyfr: %s\n", szyfr); */

	//zapis_obrazu_do_pliku(tablica_struktur, 0, 0);
	tablica_struktur = zwalnianie_pamieci_pikseli(tablica_struktur, 1);
	//tablica_struktur_2 = zwalnianie_pamieci_pikseli(tablica_struktur_2, 1);

}

int main()
{
	//obraz* tablica_struktur = NULL;
	int aktywny_obraz = 0;
	int ilosc_obrazow = 0;
	int i = 0, j = 0, a = 0, opcja, usun, val;
	char opcja1[100], opcja2[100], tab_opcja[100];

	//tablica_struktur = (obraz*)calloc(1, sizeof(obraz));

	printf("[PATRYK FISCHER 237403]\n");
	poczatek4:
	printf("[Menu programu]\n");
	printf("1. Szyfracja w obrazie.\n");
	printf("2. Deszyfracja z obrazu.\n");
	printf("3. Wyjscie z programu.\n \n");

	while (1)
	{
		poczatek3:
		puts("Opcja programu: ");
		rewind(stdin);
		//fflush(stdin);
		//while (getchar() != '\n');
		fgets(opcja1, 100, stdin);
		opcja = atoi(opcja1);
		//scanf("%99s", opcja);
		switch (opcja)
		{
		case 1: {
			szyfracja_obrazu();
		}; break;
		case 2: {
			deszyfracja_obrazu();
		}; break;
		case 3: {
			//tablica_struktur = zwalnianie_pamieci_pikseli(tablica_struktur, ilosc_obrazow);
			system("PAUSE");
			exit(0);
		}; break;
		default: {
			//val = atoi(opcja);
			if ((opcja < 1) || (opcja > 3))
			{
				printf("Nie ma takiej opcji!\n\n");
			}
		}; break;
		}
	}

	system("PAUSE");
	return 0;
}

