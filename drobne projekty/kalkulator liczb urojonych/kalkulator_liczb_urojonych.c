#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct elementy
{
	double czesc_rzeczywista;
	double czesc_urojona;
	struct elementy *poprzedni;
} element;

element *push(double nowa_gora_rz, double nowa_gora_u, element *gora)
{
	element *nowy;
	nowy = (element*)malloc(sizeof(element));
	nowy->czesc_rzeczywista = nowa_gora_rz;
	nowy->czesc_urojona = nowa_gora_u;
	nowy->poprzedni = gora;
	gora = &nowy[0];
	return gora;
}

element *pop(element *gora)
{
	element *tymczasowy = gora->poprzedni;
	free(gora);
	gora = tymczasowy;
	return gora;
}

element *dodawanko(element *gora)
{
	double skladnik1, skladnik1_ur, skladnik2, skladnik2_ur,wyniczek,wyniczek_urojony;
	
	skladnik1 = gora->czesc_rzeczywista;
	skladnik1_ur = gora->czesc_urojona;
	gora = pop(gora);
	skladnik2 = gora->czesc_rzeczywista;
	skladnik2_ur = gora->czesc_urojona;
	gora = pop(gora);
	wyniczek = skladnik1 + skladnik2;
	wyniczek_urojony = skladnik1_ur + skladnik2_ur;
	gora = push(wyniczek, wyniczek_urojony, gora);
	return gora;
}

element *odejmowanko(element *gora)
{
	double skladnik1, skladnik1_ur, skladnik2, skladnik2_ur, wyniczek, wyniczek_urojony;

	skladnik1 = gora->czesc_rzeczywista;
	skladnik1_ur = gora->czesc_urojona;
	gora = pop(gora);
	skladnik2 = gora->czesc_rzeczywista;
	skladnik2_ur = gora->czesc_urojona;
	gora = pop(gora);
	wyniczek = skladnik1 - skladnik2;
	wyniczek_urojony = skladnik1_ur - skladnik2_ur;
	gora = push(wyniczek, wyniczek_urojony, gora);
	return gora;
}

element *mnozonko(element *gora)
{
	double skladnik1, skladnik1_ur, skladnik2, skladnik2_ur, wyniczek, wyniczek_urojony;

	skladnik1 = gora->czesc_rzeczywista;
	skladnik1_ur = gora->czesc_urojona;
	gora = pop(gora);
	skladnik2 = gora->czesc_rzeczywista;
	skladnik2_ur = gora->czesc_urojona;
	gora = pop(gora);
	wyniczek = skladnik1 * skladnik2 - skladnik1_ur * skladnik2_ur;
	wyniczek_urojony = skladnik1 * skladnik2_ur + skladnik1_ur * skladnik2;
	gora = push(wyniczek, wyniczek_urojony, gora);
	return gora;
}

element *dzielonko(element *gora)
{
	double skladnik1, skladnik1_ur, skladnik2, skladnik2_ur, wyniczek, wyniczek_urojony;
	
	skladnik1 = gora->czesc_rzeczywista;
	skladnik1_ur = gora->czesc_urojona;
	gora = pop(gora);
	skladnik2 = gora->czesc_rzeczywista;
	skladnik2_ur = gora->czesc_urojona;
	gora = pop(gora);
	wyniczek = (skladnik1 * skladnik2 + skladnik1_ur * skladnik2_ur) / (skladnik2*skladnik2 + skladnik2_ur*skladnik2_ur);
	wyniczek_urojony = (skladnik1_ur * skladnik2 - skladnik1 * skladnik2_ur) / (skladnik2*skladnik2 + skladnik2_ur*skladnik2_ur);
	gora = push(wyniczek, wyniczek_urojony, gora);
	return gora;
}

void main(void)
{
	element *gora;
	element *pierwszy;
	FILE *plik;
	char tablica[100];
	char *tab;
	int i, a = 0, b = 0, c = 0;
	double wartosc, wartosc_ur;
	char znak, wyjscie[4];

	//pierwszy = (element*)malloc(sizeof(element));
	//pierwszy->czesc_rzeczywista = 0;
	//pierwszy->czesc_urojona = 0;
	gora = (element*)malloc(sizeof(element));
	//pierwszy->poprzedni = NULL;
	gora->poprzedni = NULL;
	//gora = &pierwszy[0];

	printf("WITAJ W KALKULATORZE LICZB ZESPOLONYCH!\n\n");
	printf("Formula liczby: (czesc_rzeczywista) i(czesc_urojona)\n");
	printf("Najpierw podaj liczby odzielone spacjami, a potem symbole dzialan!\n");
	printf("Symbole dzialan: s - sumowanie  o - odejmowanie  m - mnozenie  d - dzielenie\n");
	printf("Jesli chcesz wyjsc napisz 'exit'!\n\n");

	while (1)
	{
		poczatek0:
		printf("Podaj dzialanie: ");
		fgets(tablica, 100, stdin);
		tab = &tablica;

		if (sscanf(tab, "%4s", &wyjscie) == 1 && wyjscie[0] == 'e' && wyjscie[1] == 'x' && wyjscie[2] == 'i' && wyjscie[3] == 't')
		{
			printf("\nTWORCY JEST MILO ZE SKORZYSTALES!\n");
			//free(pierwszy);
			free(gora);
			system("PAUSE");
			exit(0);
		}

		plik = fopen("tajny_pliczek.hehe", "w");
		fprintf(plik, "%s", tab);
		fclose(plik);

		plik = fopen("tajny_pliczek.hehe", "r");

		if (sscanf(tab, " %c", &znak) != 1)
		{
			puts("HEHE, no ja nie wiem co Ty chciales wprowadzic!\n");
			remove("tajny_pliczek.hehe");
			goto poczatek0;
		}

		while (fscanf(plik, " %c", &znak) == 1 && znak != 's' && znak != 'o' && znak != 'd' && znak != 'm')
		{
			fseek(plik, -1, SEEK_CUR);

			if (fscanf(plik, " %c", &znak) == 1 && znak != 'i' && znak != '0' && znak != '1' && znak != '2' && znak != '3' && znak != '4' && znak != '5' && znak != '6' && znak != '7' && znak != '8' && znak != '9' && znak != '-')
			{
				puts("HEHE, no ja nie wiem co Ty chciales wprowadzic!\n");
				c = 1;
				break;
			}
			else fseek(plik, -1, SEEK_CUR);

			if (fscanf(plik, "%lf", &wartosc) == 1)
			{
				if (fscanf(plik, " %c", &znak) == 1 && znak == 'i')
				{
					fscanf(plik, "%lf", &wartosc_ur);
				}
				else
				{
					wartosc_ur = 0;
					fseek(plik, -1, SEEK_CUR);
				}
				gora = push(wartosc, wartosc_ur, gora);
				a++;
			}
			else
			{
				fseek(plik, -1, SEEK_CUR);
				if (fscanf(plik, " %c", &znak) == 1 && znak == 'i')
				{
					fscanf(plik, "%lf", &wartosc_ur);
					wartosc = 0;
					gora = push(wartosc, wartosc_ur, gora);
					a++;
				}
			}
		}

		fseek(plik, -1, SEEK_CUR);
		for (i = 0; i < a - 1; i++)
		{
			b = 1;
			fscanf(plik, " %c", &znak);
			if (znak == 's') gora = dodawanko(gora);
			else if (znak == 'o') gora = odejmowanko(gora);
			else if (znak == 'm') gora = mnozonko(gora);
			else if (znak == 'd') gora = dzielonko(gora);
			else
			{
				if (c == 0) puts("HEHE, no ja nie wiem co Ty chciales wprowadzic!\n");
				c = 1;
				gora = pop(gora);
				break;
			}
		}

		fclose(plik);
		remove("tajny_pliczek.hehe");
		if (c == 0) printf("Wynik wynosi: %lf i%lf!\n\n", gora->czesc_rzeczywista, gora->czesc_urojona);
		if (b == 0) for (i = 0; i < a; i++) gora = pop(gora);
		c = 0;
		b = 0;
		a = 0;
	}

	free(pierwszy);
	system("PAUSE");
}
