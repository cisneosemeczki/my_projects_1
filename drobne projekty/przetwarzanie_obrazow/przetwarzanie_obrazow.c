#include <stdio.h>
#include <stdlib.h>


typedef struct obrazek
{
	int szerokosc, wysokosc, jasnosc;
	int **piksele;
	char nazwa_obrazu[100];
	int zaszumiony;
} obraz;

obraz *realokowanie_tablicy_struktur(obraz *tablica_struktur, int i)
{
	tablica_struktur = (obraz*)realloc(tablica_struktur, i*sizeof(obraz));
	return tablica_struktur;
}

obraz *tworzenie_tablicy_na_piksele(obraz *tablica_struktur, int i, int szerokosc, int wysokosc)
{
	int k;

	if (tablica_struktur != NULL)
	{
		tablica_struktur[i].piksele = (int**)calloc(wysokosc, sizeof(int));
		if ((tablica_struktur[i]).piksele != NULL)
		{
			for (k = 0; k < wysokosc; k++)
			{
				tablica_struktur[i].piksele[k] = (int*)calloc(szerokosc, sizeof(int));
			}
		}
	}
	else
	{
		free(tablica_struktur);
		return 0;
	}
	return tablica_struktur;
}

obraz *wczytywanie_obrazu(obraz *tablica_struktur, int numer_obrazu)
{
	FILE *plik;
	int szerokosc, wysokosc, jasnosc;
	int i, j;
	char nazwa_pliku[100], hmm[10], znaki[3];

	poczatek0:
	puts("Podaj nazwe pliku (bez .pgm): ");
	//fgets(nazwa_pliku, 100, stdin);
	scanf("%99s", nazwa_pliku);
	strcpy(hmm, ".pgm");
	strcat(nazwa_pliku, hmm);

	plik = fopen(nazwa_pliku, "r");
	if (plik != NULL)
	{
		if (fscanf(plik, "%2s", znaki) == 1 && znaki[0] == 'P' && (znaki[1] == '2' || znaki[1] == '5'))
		{
			szerokosc = sczytanie_wartosci(plik);
			wysokosc = sczytanie_wartosci(plik);
			jasnosc = sczytanie_wartosci(plik);
			tworzenie_tablicy_na_piksele(tablica_struktur, numer_obrazu, szerokosc, wysokosc);
			if (tablica_struktur != NULL)
			{
				tablica_struktur[numer_obrazu].szerokosc = szerokosc;
				tablica_struktur[numer_obrazu].wysokosc = wysokosc;
				tablica_struktur[numer_obrazu].jasnosc = jasnosc;
				tablica_struktur[numer_obrazu].zaszumiony = 0;
				strcpy(tablica_struktur[numer_obrazu].nazwa_obrazu, nazwa_pliku);

				for (i = 0; i < wysokosc; i++)
				{
					for (j = 0; j < szerokosc; j++)
						tablica_struktur[numer_obrazu].piksele[i][j] = sczytanie_wartosci(plik);
				} 
			}
		}
	}
	else
	{
		printf("Nie udalo sie otworzyc pliku!\n\n");
		goto poczatek0;
	}

	//printf("jasnosc wynosi %d\n", tablica_struktur[numer_obrazu].jasnosc);
	//printf("jakis piksel wynosi %d\n", tablica_struktur[numer_obrazu].piksele[0][1]);
	fclose(plik);
	
	return tablica_struktur;
}

void tworzenie_histogramu(obraz *tablica, int aktywny_obraz)
{
	FILE *plik;
	int i,j,d;
	int *tablica_kolorow;

	tablica_kolorow = (int*)calloc(256, sizeof(int));

	for (i = 0; i < tablica[aktywny_obraz].wysokosc; i++)
	{
		for (j = 0; j < tablica[aktywny_obraz].szerokosc; j++)
		{
			d = tablica[aktywny_obraz].piksele[i][j];
			tablica_kolorow[d] = tablica_kolorow[d] + 1;
		}
	}
	plik = fopen("histogram.csv", "w");
	for (i = 1; i<256; i++)
		fprintf(plik, "%d\n", tablica_kolorow[i]);
	fclose(plik);
	printf("Plik z histogramem zostal utworzony!\n \n");
	free(tablica_kolorow);
}

obraz *nanoszenie_histogramu(obraz *tablica, int aktywny_obraz)
{
	int i, j, d; 
	int punkt_x, punkt_y, kolor_max = 0;
	int *tablica_kolorow;

	tablica_kolorow = (int*)calloc(256, sizeof(int));

	for (i = 0; i < tablica[aktywny_obraz].wysokosc; i++)
	{
		for (j = 0; j < tablica[aktywny_obraz].szerokosc; j++)
		{
			d = tablica[aktywny_obraz].piksele[i][j];
			tablica_kolorow[d] = tablica_kolorow[d] + 1;
		}
	}

	for (i = 0; i < tablica[aktywny_obraz].jasnosc + 1; i++)
	{
		if (tablica_kolorow[i] > kolor_max) kolor_max = tablica_kolorow[i];
	}

	for (i = 0; i < tablica[aktywny_obraz].szerokosc; i++)
	{
		punkt_x = i * tablica[aktywny_obraz].jasnosc;
		punkt_x = punkt_x / tablica[aktywny_obraz].szerokosc;
		punkt_y = tablica_kolorow[punkt_x];
		punkt_y = punkt_y * tablica[aktywny_obraz].wysokosc;
		punkt_y = punkt_y / kolor_max;
		punkt_y = tablica[aktywny_obraz].wysokosc - punkt_y;
		while (punkt_y > tablica[aktywny_obraz].wysokosc - 1) punkt_y--;
		//printf("%d", punkt_y);
		tablica[aktywny_obraz].piksele[punkt_y][i] = 255;
	}
	free(tablica_kolorow);
	printf("Naniesiono histogram na obraz!\n \n");
	return tablica;
}

obraz *rownanie_histogramu(obraz *tablica, int aktywny_obraz)
{
	FILE *plik;
	int i, j, d;
	int *tablica_kolorow;
	int *tab_dystrybuanty;
	double iloczyn1,iloczyn1_licznik,iloczyn1_mianownik;
	int iloczyn2,wartosc;

	tablica_kolorow = (int*)calloc(tablica[aktywny_obraz].jasnosc + 1, sizeof(int));
	tab_dystrybuanty = (int*)calloc(tablica[aktywny_obraz].jasnosc + 1, sizeof(int));

	for (i = 0; i < tablica[aktywny_obraz].wysokosc; i++)
	{
		for (j = 0; j < tablica[aktywny_obraz].szerokosc; j++)
		{
			d = tablica[aktywny_obraz].piksele[i][j];
			tablica_kolorow[d] = tablica_kolorow[d] + 1;
		}
	}

	tab_dystrybuanty[0] = tablica_kolorow[0];
	for (i = 1; i < tablica[aktywny_obraz].jasnosc+1; i++)
	{
		tab_dystrybuanty[i] = tab_dystrybuanty[i-1] + tablica_kolorow[i];
	}

	for (i = 0; i < tablica[aktywny_obraz].wysokosc; i++)
	{
		for (j = 0; j < tablica[aktywny_obraz].szerokosc; j++)
		{
			iloczyn1_licznik = (tab_dystrybuanty[tablica[aktywny_obraz].piksele[i][j]] - tab_dystrybuanty[0]);
			iloczyn1_mianownik = ((tablica[aktywny_obraz].wysokosc * tablica[aktywny_obraz].szerokosc) - tab_dystrybuanty[0]);
			iloczyn1 = iloczyn1_licznik / iloczyn1_mianownik;
			iloczyn2 = tablica[aktywny_obraz].jasnosc;
			wartosc = iloczyn1 * iloczyn2;
			tablica[aktywny_obraz].piksele[i][j] = wartosc;
		}
	}
	
	plik = fopen("dystrybuanta.csv", "w");
	for (i = 1; i<256; i++)
		fprintf(plik, "%d\n", tab_dystrybuanty[i]);
	fclose(plik);
	printf("Plik z dystrybuanta zostal utworzony! \n");
	printf("Wyrownano histogram!\n \n");
	free(tablica_kolorow);
	free(tab_dystrybuanty);

	return tablica;
}

obraz *progowanie(obraz *tablica, int aktywny_obraz)
{
	int i,j,prog;
	int tab_prog[100];

	poczatek5:
	puts("Podaj prog podzialu: ");
	fgets(tab_prog, 100, stdin);
	prog = atoi(tab_prog);
	//prog = sczytywanie_int();
	if ((prog > tablica[aktywny_obraz].jasnosc) || (prog < 0))
	{
		puts("Nie ma takiej wartosci do progowania!\n");
		goto poczatek5;
	}
	for (i = 0; i < tablica[aktywny_obraz].wysokosc; i++)
	{
		for (j = 0; j < tablica[aktywny_obraz].szerokosc; j++)
		{
			if (tablica[aktywny_obraz].piksele[i][j] < prog)
				tablica[aktywny_obraz].piksele[i][j] = 0;
			else tablica[aktywny_obraz].piksele[i][j] = tablica[aktywny_obraz].jasnosc;
		}
	}
	printf("Progowanie o progu %d zostalo wykonane!\n\n", prog);
	return tablica;
}

obraz *negatyw(obraz *tablica, int aktywny_obraz)
{
	int i,j;
	
	for (i = 0; i < tablica[aktywny_obraz].wysokosc; i++)
	{
		for (j = 0; j < tablica[aktywny_obraz].szerokosc; j++)
		{
			tablica[aktywny_obraz].piksele[i][j] = tablica[aktywny_obraz].jasnosc - tablica[aktywny_obraz].piksele[i][j];
		}
	}
	printf("Negatyw zostal wykonany!\n\n");
	return tablica;
}

obraz *zaszumianie(obraz *tablica, int aktywny_obraz)
{
	int szum_wys, szum_sz, wartosc, i;
	int ilosc;
	char tab_ilosc[100];

	poczatek7:
	printf("Ile losowych pikseli ma byc zaszumionych?\n");
	fgets(tab_ilosc, 100, stdin);
	ilosc = atoi(tab_ilosc);
	if ((ilosc > (tablica[aktywny_obraz].szerokosc * tablica[aktywny_obraz].wysokosc)) || (ilosc < 1))
	{
		puts("Nie ma tylu pikseli na obrazie!\n");
		goto poczatek7;
	}
	for (i = 0; i < ilosc; i++)
	{
		szum_sz = rand() %tablica[aktywny_obraz].szerokosc;
		szum_wys = rand() % tablica[aktywny_obraz].wysokosc;
		wartosc = rand() % 2;
		if (wartosc == 0) tablica[aktywny_obraz].piksele[szum_wys][szum_sz] = 0;
		if (wartosc == 1) tablica[aktywny_obraz].piksele[szum_wys][szum_sz] = tablica[aktywny_obraz].jasnosc;
	}
	tablica[aktywny_obraz].zaszumiony = 1;
	puts("Twoj obraz zostal zaszumiony!\n");
	return tablica;
}

obraz *odszumianie_mediana(obraz *tablica, int aktywny_obraz)
{
	int i, j, k, l, temp, a;
	int *sort;

	for (i = 0; i < tablica[aktywny_obraz].wysokosc - 3; i++)
	{
		for (j = 0; j < tablica[aktywny_obraz].szerokosc - 3; j++)
		{
			sort = (int*)calloc(9, sizeof(int));
			sort[0] = tablica[aktywny_obraz].piksele[i][j];
			sort[1] = tablica[aktywny_obraz].piksele[i][j + 1];
			sort[2] = tablica[aktywny_obraz].piksele[i][j + 2];
			sort[3] = tablica[aktywny_obraz].piksele[i + 1][j];
			sort[4] = tablica[aktywny_obraz].piksele[i + 1][j + 1];
			sort[5] = tablica[aktywny_obraz].piksele[i + 1][j + 2];
			sort[6] = tablica[aktywny_obraz].piksele[i + 2][j];
			sort[7] = tablica[aktywny_obraz].piksele[i + 2][j + 1];
			sort[8] = tablica[aktywny_obraz].piksele[i + 2][j + 2];

			for (k = 0; k < 9; k++)
			{
				a = 0;
				for (l = 0; l < 8; l++)
				{
					if (sort[l] > sort[l + 1])
					{
						temp = sort[l];
						sort[l] = sort[l + 1];
						sort[l + 1] = temp;
						a = 1;
					}
				}
				if (a == 0) break;
			}
			tablica[aktywny_obraz].piksele[i + 1][j + 1] = sort[4];
			free(sort);
		}
	}
	puts("Twoj obraz zostal odszumiony filtrem medianowym!\n");
	return tablica;
}

obraz *odszumianie_srednia(obraz *tablica, int aktywny_obraz)
{
	int i, j, suma, srednia;
	int *sort;

	for (i = 0; i < tablica[aktywny_obraz].wysokosc - 3; i++)
	{
		for (j = 0; j < tablica[aktywny_obraz].szerokosc - 3; j++)
		{
			sort = (int*)calloc(9, sizeof(int));
			sort[0] = tablica[aktywny_obraz].piksele[i][j];
			sort[1] = tablica[aktywny_obraz].piksele[i][j + 1];
			sort[2] = tablica[aktywny_obraz].piksele[i][j + 2];
			sort[3] = tablica[aktywny_obraz].piksele[i + 1][j];
			sort[4] = tablica[aktywny_obraz].piksele[i + 1][j + 1];
			sort[5] = tablica[aktywny_obraz].piksele[i + 1][j + 2];
			sort[6] = tablica[aktywny_obraz].piksele[i + 2][j];
			sort[7] = tablica[aktywny_obraz].piksele[i + 2][j + 1];
			sort[8] = tablica[aktywny_obraz].piksele[i + 2][j + 2];

			suma = (sort[0] + 2*sort[1] + sort[2] + 2*sort[3] + 4*sort[4] + 2*sort[5] + sort[6] + 2*sort[7] + sort[8]);
			srednia = suma / 16;

			tablica[aktywny_obraz].piksele[i + 1][j + 1] = srednia;
			free(sort);
		}
	}
	puts("Twoj obraz zostal odszumiony filtrem Gaussa!\n");
	return tablica;
}

obraz *obrot(obraz *tablica, int aktywny_obraz)
{
	int i, j, nowa_szerokosc, nowa_wysokosc;
	int **temp_piksele;

	nowa_szerokosc = tablica[aktywny_obraz].wysokosc;
	nowa_wysokosc = tablica[aktywny_obraz].szerokosc;

	temp_piksele = (int**)calloc(nowa_wysokosc, sizeof(int*));
	for (i = 0; i < nowa_wysokosc; i++)
		temp_piksele[i] = (int*)calloc(nowa_szerokosc, sizeof(int));

	for (i = 0; i < nowa_szerokosc; i++)
	{
		for (j = 0; j < nowa_wysokosc; j++)
			temp_piksele[j][nowa_szerokosc-(i+1)] = tablica[aktywny_obraz].piksele[i][j];
	}
	
	for (i = 0; i < tablica[aktywny_obraz].wysokosc; i++)
		free(tablica[aktywny_obraz].piksele[i]);
	free(tablica[aktywny_obraz].piksele);

	tablica[aktywny_obraz].piksele = temp_piksele;
	tablica[aktywny_obraz].wysokosc = nowa_wysokosc;
	tablica[aktywny_obraz].szerokosc = nowa_szerokosc;

	return tablica;
}

obraz *odbicie(obraz *tablica, int aktywny_obraz)
{
	int i, j, od, opcja;
	char tab_opcja[100];
	int **temp_piksele;

	temp_piksele = (int**)calloc(tablica[aktywny_obraz].wysokosc, sizeof(int*));
	for (i = 0; i < tablica[aktywny_obraz].wysokosc; i++)
		temp_piksele[i] = (int*)calloc(tablica[aktywny_obraz].szerokosc, sizeof(int));

	for (i = 0; i < tablica[aktywny_obraz].wysokosc; i++)
	{
		for (j = 0; j < tablica[aktywny_obraz].szerokosc; j++)
			temp_piksele[i][j] = tablica[aktywny_obraz].piksele[i][j];
	}

	printf("Opcje odbicia: \n");
	printf("1. Odbicie w pione.\n");
	printf("2. Odbicie w poziomie.\n");
	poczatek8:
	puts("Wybierz opcje: ");
	fgets(tab_opcja, 100, stdin);
	opcja = atoi(tab_opcja);
	if (opcja == 1)
	{
		for (i = 0; i < tablica[aktywny_obraz].wysokosc; i++)
		{
			for (j = 0; j < tablica[aktywny_obraz].szerokosc; j++)
			{
				od = tablica[aktywny_obraz].wysokosc - (i + 1);
				tablica[aktywny_obraz].piksele[i][j] = temp_piksele[od][j];
			}
		}

	}
	else if (opcja == 2)
	{
		for (i = 0; i < tablica[aktywny_obraz].wysokosc; i++)
		{
			for (j = 0; j < tablica[aktywny_obraz].szerokosc; j++)
			{
				od = tablica[aktywny_obraz].szerokosc - (j + 1);
				tablica[aktywny_obraz].piksele[i][j] = temp_piksele[i][od];
			}
		}
	}
	else 
	{
		puts("Nie ma takiego opcji!\n");
		goto poczatek8;
	}

	for (i = 0; i < tablica[aktywny_obraz].wysokosc; i++)
		free(temp_piksele[i]);
	free(temp_piksele);

	puts("Wykonano odbicie lustrzane!\n");
	return tablica;
}

void zapis_obrazu_do_pliku(obraz *tablica, int aktywny_obraz)
{
	FILE *plik;
	int i, j;
	char nazwa_pliku[100], hmm[10];

	puts("Podaj nazwe pliku (bez .pgm): ");
	//fgets(nazwa_pliku, 100, stdin);
	scanf("%99s", nazwa_pliku);
	strcpy(hmm, ".pgm");
	strcat(nazwa_pliku, hmm);
	
	plik = fopen(nazwa_pliku, "w");
	fprintf(plik, "P2\n");
	fprintf(plik, "#hehe\n");
	fprintf(plik, "%d %d\n", tablica[aktywny_obraz].szerokosc, tablica[aktywny_obraz].wysokosc);
	fprintf(plik, "%d\n", tablica[aktywny_obraz].jasnosc);
	for (i = 0; i < tablica[aktywny_obraz].wysokosc; i++)
	{
		for (j = 0; j < tablica[aktywny_obraz].szerokosc; j++)
			fprintf(plik, "%d ", tablica[aktywny_obraz].piksele[i][j]);
		fprintf(plik,"\n");
	}
	fclose(plik);
	printf("Obrazek zostal utworzony!\n \n");
}

obraz* zwalnianie_pamieci_pikseli(obraz *tablica, int ilosc_obrazow)
{
	int i,j;
	
	for (j = 0; j < ilosc_obrazow; j++)
	{
		for (i = 0; i < tablica[j].wysokosc; i++)
			free(tablica[j].piksele[i]);
		free(tablica[j].piksele);
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

int main()
{
	obraz* tablica_struktur=NULL;
	int aktywny_obraz = 0;
	int ilosc_obrazow = 0;
	int i=0,j=0,a=0,opcja,usun,val;
	char opcja1[100],opcja2[100],tab_opcja[100];
	char tab_usun[100],tab_aktywny_obraz[100];

	tablica_struktur = (obraz*)calloc(1, sizeof(obraz));
	
	printf("[PATRYK FISCHER 237403]\n");
	poczatek4:
	printf("[Menu programu]\n");
	printf("1. Wczytanie obrazu.\n");
	printf("2. Usuniecie wybranego obrazu.\n");
	printf("3. Wybranie aktywnego obrazu.\n");
	printf("4. Bardziej doglebne cuda z obrazem.\n");
	printf("5. Wyjscie z programu.\n \n");

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
			if (ilosc_obrazow>0) tablica_struktur = realokowanie_tablicy_struktur(tablica_struktur, ilosc_obrazow+1);
			tablica_struktur = wczytywanie_obrazu(tablica_struktur, ilosc_obrazow);
			printf("Wczytano obraz o nazwie %s!\n\n", tablica_struktur[ilosc_obrazow].nazwa_obrazu);
			ilosc_obrazow++;
		}; break;
		case 2: {
			if (ilosc_obrazow == 0)
			{
				puts("Nie masz wczytanego zadnego obrazu!\n");
				goto poczatek3;
			}
			puts("Oto lista obrazow: ");
			for (i = 0; i < ilosc_obrazow; i++)
			{
				printf("%d - %s\n", i + 1, tablica_struktur[i].nazwa_obrazu);
			}
			poczatek1:
			printf("Wybierz obraz do usuniecia: ");
			fgets(tab_usun, 100, stdin);
			usun = atoi(tab_usun);
			//usun = sczytywanie_int();
			//scanf("%d", &usun);
			if ((usun > ilosc_obrazow)||(usun < 1))
			{
				puts("Nie ma takiego obrazu na liscie!\n");
				goto poczatek1;
			}
			if (ilosc_obrazow == 1)
			{
				tablica_struktur = zwalnianie_pamieci_pikseli(tablica_struktur,ilosc_obrazow);
				tablica_struktur = (obraz*)calloc(1, sizeof(obraz));
				ilosc_obrazow--;
				printf("Usunales %d obraz!\n", 1);
				puts("Teraz nie masz zadnego wczytanego obrazu!\n");
				a = 0;
			}
			else if (usun == ilosc_obrazow)
			{
				tablica_struktur = realokowanie_tablicy_struktur(tablica_struktur, ilosc_obrazow - 1);
				ilosc_obrazow--;
				printf("Usunales %d obraz!\n\n", usun);
			}
			else 
			{
				for (i = usun; i < ilosc_obrazow; i++)
				{
					tablica_struktur[usun-1] = tablica_struktur[usun];
				}
				tablica_struktur = realokowanie_tablicy_struktur(tablica_struktur, ilosc_obrazow - 1);
				ilosc_obrazow--;
				printf("Usunales %d obraz!\n\n", usun);
			}
			if (aktywny_obraz == (usun - 1)) aktywny_obraz = 0;
		}; break;
		case 3: {
			if (ilosc_obrazow == 0)
			{
				puts("Nie masz wczytanego zadnego obrazu!\n");
				goto poczatek3;
			}
			puts("Oto lista obrazow: ");
			for (i = 0; i < ilosc_obrazow; i++)
			{
				printf("%d - %s\n", i + 1, tablica_struktur[i].nazwa_obrazu);
			}
			poczatek2:
			puts("Wybierz aktywny obraz: ");
			fgets(tab_aktywny_obraz, 100, stdin);
			aktywny_obraz = atoi(tab_aktywny_obraz);
			aktywny_obraz--;
			//aktywny_obraz = sczytywanie_int();
			//scanf("%d", &aktywny_obraz);
			if ((aktywny_obraz > ilosc_obrazow-1) || (aktywny_obraz < 0))
			{
				puts("Nie ma takiego obrazu na liscie!\n");
				goto poczatek2;
			}
			printf("Wybrales aktywny obraz: %s!\n\n", tablica_struktur[aktywny_obraz].nazwa_obrazu);
			a = 1;
		}; break;
		case 4: {
			if (ilosc_obrazow == 0)
			{
				puts("Nie masz wczytanego zadnego obrazu!\n");
				goto poczatek3;
			}
			if (a == 0)
			{
				printf("Nie wybrales aktywnego obrazu!\n");
				puts("Domyslnie pracujesz na 1 obrazie z listy!");
			}
			puts(" ");
			printf("[Menu podrzedne]\n");
			printf("1. Tworzenie histogramu.\n");
			printf("2. Rownanie histogramu.\n");
			printf("3. Naniesienie histogramu na obraz.\n");
			printf("4. Progowanie.\n");
			printf("5. Negatyw.\n");
			printf("6. Szum sol i pieprz.\n");
			printf("7. Odszumianie medianowe.\n");
			printf("8. Odszumianie Gaussa.\n");
			printf("9. Obrot obrazu.\n");
			printf("10. Odbicie lustrzane obrazu.\n");
			printf("11. Zapis obrazu do pliku pgm.\n");
			printf("12. Wyjscie do glownego menu.\n \n");
			while (1)
			{
				poczatek9:
				puts("Opcja podrzedna: ");
				//fflush(stdin);
				rewind(stdin);
				fgets(opcja2, 100, stdin);
				opcja = atoi(opcja2);
				//scanf("%99s", opcja2);
				switch (opcja)
				{
				case 1: {
					tworzenie_histogramu(tablica_struktur, aktywny_obraz);
				}; break;
				case 2: {
					rownanie_histogramu(tablica_struktur, aktywny_obraz);
				}; break;
				case 3: {
					nanoszenie_histogramu(tablica_struktur, aktywny_obraz);
				}; break;
				case 4: {
					tablica_struktur = progowanie(tablica_struktur, aktywny_obraz);
				}; break;
				case 5: {
					tablica_struktur = negatyw(tablica_struktur, aktywny_obraz);
				}; break;
				case 6: {
					zaszumianie(tablica_struktur, aktywny_obraz);
				}; break;
				case 7: {
					if (tablica_struktur[aktywny_obraz].zaszumiony == 0)
					{
						puts("Hehe no nie zaszumiles obrazu!\n");
						goto poczatek9;
					}
					odszumianie_mediana(tablica_struktur, aktywny_obraz);
				}; break;
				case 8: {
					if (tablica_struktur[aktywny_obraz].zaszumiony == 0)
					{
						puts("Hehe no nie zaszumiles obrazu!\n");
						goto poczatek9;
					}
					odszumianie_srednia(tablica_struktur, aktywny_obraz);
				}; break;
				case 9: {
					printf("Opcje obrotu: \n");
					printf("1. Obrot o 90 stopni.\n");
					printf("2. Obrot o 180 stopni.\n");
					printf("3. Obrot o 270 stopni.\n");
					poczatek10:
					puts("Wybierz opcje: ");
					fgets(tab_opcja, 100, stdin);
					opcja = atoi(tab_opcja);
					if (opcja == 1)
					{
						tablica_struktur=obrot(tablica_struktur, aktywny_obraz);
						puts("Obrazek zostal obrocony o 90 stopni!\n");
					}
					else if (opcja == 2)
					{
						tablica_struktur=obrot(tablica_struktur, aktywny_obraz);
						tablica_struktur=obrot(tablica_struktur, aktywny_obraz);
						puts("Obrazek zostal obrocony o 180 stopni!\n");
					}
					else if (opcja == 3)
					{
						tablica_struktur=obrot(tablica_struktur, aktywny_obraz);
						tablica_struktur=obrot(tablica_struktur, aktywny_obraz);
						tablica_struktur=obrot(tablica_struktur, aktywny_obraz);
						puts("Obrazek zostal obrocony o 270 stopni!\n");
					}
					else
					{
						puts("Nie ma takiej opcji!\n");
						goto poczatek10;
					}
				}; break;
				case 10: {
					odbicie(tablica_struktur, aktywny_obraz);
				}; break;
				case 11: {
					zapis_obrazu_do_pliku(tablica_struktur, aktywny_obraz);
				}; break;
				case 12: {
					puts(" ");
					goto poczatek4;
				}; break;
				default: {
					//val = atoi(opcja2);
					if ((opcja < 1) || (opcja > 12))
						printf("Nie ma takiej opcji!\n\n");
				}; break; 
				}
			}
		}; break;
		case 5: {
			tablica_struktur = zwalnianie_pamieci_pikseli(tablica_struktur, ilosc_obrazow);
			system("PAUSE");
			exit(0);
		}; break;
		default: {
			//val = atoi(opcja);
			if ((opcja < 1) || (opcja > 5))
			{
				printf("Nie ma takiej opcji!\n\n");
			}
		}; break;
		}
	}

	system("PAUSE");
	return 0;
}
