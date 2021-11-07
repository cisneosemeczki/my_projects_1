#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

//double cos(double x);
double* utworz_tablice(int);
double* wypelnianie_tablicy_poczatkowych_danych(int);
double liczenie_dx(double, double, int);
void wypelnianie_tablicy_x(double *, double, double, int, int);
void wypelnianie_tablicy_y(double*, double*, double, double, int, int);
void wypelnianie_tablicy_y_zaszumionych(double*, double*, int, int);
void wypelnianie_tablicy_y_odszumionych_mediana(double*, double*, int, int);
void wypelnianie_tablicy_y_odszumionych_srednia(double*, double*, int, int);
void zapis_do_pliku(double*, double*, double*, double*, int);
double* realokacja_tablicy(double*, int);
void odczyt_z_pliku();
int sczytywanie_int();
double sczytywanie_double();
void generacja_wykresu(double*, double*, int);

int main()
{
	int elementy_tab_0 = 0, elementy_tab_1, elementy_tab_2;
	int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, val = 0;
	char opcja[20],opcja2[20];
	//double poczatek_zakresu, koniec_zakresu, iloczyn, przesuniecie,dx;
	double *tablica_pocz_danych;
	double *tablica_x, *tablica_y, *tablica_zaszumionych, *tablica_odszumionych;
	setlocale(LC_ALL, "");

    printf("Witamy w programie do generowania funkcji!\n");
    printf("Program bedzie przedstawial cosinus polowkowy.\n");
    printf("Na poczatku bedziemy podawac poczatkowe dane.\n");
	poczatek4:
	printf("Podaj ilosc elementow tablicy: ");
	elementy_tab_1 = sczytywanie_int();
	//scanf("%d", &elementy_tab_1);
	if (elementy_tab_1 < 0) 
	{
		puts("Ilosc elementow tablicy nie moze byc mniejsza od 0!\n");
		goto poczatek4;
	}
    tablica_pocz_danych = wypelnianie_tablicy_poczatkowych_danych(elementy_tab_1);

	tablica_x = utworz_tablice(elementy_tab_1);
	tablica_y = utworz_tablice(elementy_tab_1);
	tablica_zaszumionych = utworz_tablice(elementy_tab_1);
	tablica_odszumionych = utworz_tablice(elementy_tab_1);
	wypelnianie_tablicy_x(tablica_x, tablica_pocz_danych[4], tablica_pocz_danych[0], elementy_tab_0, elementy_tab_1);

	printf("Menu programu:\n");
	printf("1. Generowanie sygnalu.\n");
	printf("2. Zaszumianie sygnalu.\n");
	printf("3. Odszumianie sygnalu.\n");
	printf("4. Realokowanie danych.\n");
	printf("5. Zapis danych do pliku.\n");
	printf("6. Odczyt danych z pliku.\n");
	printf("7. Podanie nowych danych.\n");
	printf("8. Wyjscie z programu.\n");

	while(1)
    {
        poczatek0:
		printf("Opcja programu: ");
        scanf("%19s", opcja);
		val = 0;
        switch(opcja[0])
        {
            case '1': {
                //tablica_y = utworz_tablice(elementy_tab_1);
                wypelnianie_tablicy_y(tablica_x, tablica_y, tablica_pocz_danych[2], tablica_pocz_danych[3], elementy_tab_0, elementy_tab_1);
				//tablica_zaszumionych = utworz_tablice(elementy_tab_1);
				//tablica_odszumionych = utworz_tablice(elementy_tab_1);
                puts("Wygenerowano sygnal w podanym przez Cb zakresie!\n");
				d = 1;
            }; break;
            case '2': {
                if (d==0)
                {
                    puts("Nie utworzono tablicy y!\n");
					goto poczatek0;
                }
				else
				{
					//tablica_zaszumionych = utworz_tablice(elementy_tab_1);
					wypelnianie_tablicy_y_zaszumionych(tablica_y, tablica_zaszumionych, elementy_tab_0, elementy_tab_1);
					puts("Twoj sygnal zostal zaszumiony!\n");
					b = 1;
				}
            }; break;
            case '3': {
                if (b==0)
                {
                    puts("Nie zaszumiono danych!\n");
					goto poczatek0;
                }
				else
				{
					//tablica_odszumionych = utworz_tablice(elementy_tab_1);
					printf("Odszumianie medianowe czy srednie? M/S :");
					poczatek6:
					scanf("%19s", opcja2);
					switch (opcja2[0]) 
					{
						case 'M': {
							wypelnianie_tablicy_y_odszumionych_mediana(tablica_zaszumionych, tablica_odszumionych, elementy_tab_0, elementy_tab_1);
							puts("Twoj sygnal zostal odszumiony!\n");
							f = 1;
							c = 1;
						}; break;
						case 'S': {
							wypelnianie_tablicy_y_odszumionych_srednia(tablica_zaszumionych, tablica_odszumionych, elementy_tab_0, elementy_tab_1);
							puts("Twoj sygnal zostal odszumiony!\n");
							f = 2;
							c = 1;
						}; break;
						default: {
							printf("Nie ma takiej opcji!\n");
							printf("Wybierz M/S :");
							goto poczatek6;
						}; break;	
					}
				}
            }; break;
            case '4': {
				if (d == 0)
				{
					puts("Prosze najpierw wygenerowac sygnal!\n");
					goto poczatek0;
				}
				poczatek5:
				printf("Podaj nowa ilosc elementow tablicy: ");
				elementy_tab_2 = sczytywanie_int();
                //scanf("%d", &elementy_tab_2);
				if (elementy_tab_2 < 0)
				{
					puts("Ilosc elementow tablicy nie moze byc mniejsza od 0!\n");
					goto poczatek5;
				}

                if (c==1)
                {
                    tablica_x = realokacja_tablicy(tablica_x, elementy_tab_2);
                    wypelnianie_tablicy_x(tablica_x, tablica_pocz_danych[4], tablica_pocz_danych[0], elementy_tab_1, elementy_tab_2);
                    tablica_y = realokacja_tablicy(tablica_y, elementy_tab_2);
                    wypelnianie_tablicy_y(tablica_x, tablica_y, tablica_pocz_danych[2], tablica_pocz_danych[3], elementy_tab_1, elementy_tab_2);
                    tablica_zaszumionych = realokacja_tablicy(tablica_zaszumionych, elementy_tab_2);
					if (elementy_tab_2 < elementy_tab_1)
					{
						wypelnianie_tablicy_y_zaszumionych(tablica_y, tablica_zaszumionych, elementy_tab_0, elementy_tab_2);
					}
					else
					{
						wypelnianie_tablicy_y_zaszumionych(tablica_y, tablica_zaszumionych, elementy_tab_1, elementy_tab_2);
					}
                    tablica_odszumionych = realokacja_tablicy(tablica_odszumionych, elementy_tab_2);
					if (elementy_tab_2 > elementy_tab_1)
					{
						if (f == 1) wypelnianie_tablicy_y_odszumionych_mediana(tablica_zaszumionych, tablica_odszumionych, elementy_tab_1, elementy_tab_2);
						if (f == 2) wypelnianie_tablicy_y_odszumionych_srednia(tablica_zaszumionych, tablica_odszumionych, elementy_tab_1, elementy_tab_2);
					}
					puts("Pomyslnie wykonano realokacje!\n");
                    a=1;
                }
                if ((c==0)&&(b==1))
                {
                    tablica_x = realokacja_tablicy(tablica_x, elementy_tab_2);
                    wypelnianie_tablicy_x(tablica_x, tablica_pocz_danych[4], tablica_pocz_danych[0], elementy_tab_1, elementy_tab_2);
                    tablica_y = realokacja_tablicy(tablica_y, elementy_tab_2);
                    wypelnianie_tablicy_y(tablica_x, tablica_y, tablica_pocz_danych[2], tablica_pocz_danych[3], elementy_tab_1, elementy_tab_2);
                    tablica_zaszumionych = realokacja_tablicy(tablica_zaszumionych, elementy_tab_2);
					if (elementy_tab_2 < elementy_tab_1)
					{
						wypelnianie_tablicy_y_zaszumionych(tablica_y, tablica_zaszumionych, elementy_tab_0, elementy_tab_2);
					}
					else
					{
						wypelnianie_tablicy_y_zaszumionych(tablica_y, tablica_zaszumionych, elementy_tab_1, elementy_tab_2);
					}
					tablica_odszumionych = utworz_tablice(elementy_tab_2);
					puts("Pomyslnie wykonano realokacje!\n");
                    a=1;
                }
                if (b==0)
                {
                    tablica_x = realokacja_tablicy(tablica_x, elementy_tab_2);
                    wypelnianie_tablicy_x(tablica_x, tablica_pocz_danych[4], tablica_pocz_danych[0], elementy_tab_1, elementy_tab_2);
                    tablica_y = realokacja_tablicy(tablica_y, elementy_tab_2);
                    wypelnianie_tablicy_y(tablica_x, tablica_y, tablica_pocz_danych[2], tablica_pocz_danych[3], elementy_tab_1, elementy_tab_2);
					tablica_zaszumionych = utworz_tablice(elementy_tab_2);
					tablica_odszumionych = utworz_tablice(elementy_tab_2);
					puts("Pomyslnie wykonano realokacje!\n");
                    a=1;
                }
            }; break;
            case '5': {
				if (d == 0)
				{
					puts("Prosze najpierw wygenerowac sygnal!\n");
					goto poczatek0;
				}
				else
				{
					if (a == 1) zapis_do_pliku(tablica_x, tablica_y, tablica_zaszumionych, tablica_odszumionych, elementy_tab_2);
					if (a == 0) zapis_do_pliku(tablica_x, tablica_y, tablica_zaszumionych, tablica_odszumionych, elementy_tab_1);
					e = 1;
				}
            }; break;
            case '6': {
				if (e == 0)
				{
					puts("Prosze najpierw zapisac dane do pliku!\n");
					goto poczatek0;
				}
                odczyt_z_pliku();
            }; break;
			case '7': {
				goto poczatek4;
			}; break;
            case '8': {
				free(tablica_x);
				free(tablica_y);
				free(tablica_zaszumionych);
				free(tablica_odszumionych);
				free(tablica_pocz_danych);
				system("PAUSE");
                exit(0);
            }; break;
            default: {
				val = atoi(opcja);
				if ((val < 1) || (val > 8))
				{
					printf("Nie ma takiej opcji!\n");
				}
            }; break;
        }

    }

	//generacja_wykresu(tablica_x, tablica_odszumionych, elementy_tab_2);

	system("PAUSE");
	return 0;
}

double* utworz_tablice(int ilosc_elementow_tablicy)
{
	double *tab;
	tab = (double*)calloc(ilosc_elementow_tablicy, sizeof(double));
	return tab;
}

double* wypelnianie_tablicy_poczatkowych_danych(int ilosc_elementow_tablicy)
{
    double *tab_pocz_danych;
    tab_pocz_danych=(double*)calloc(5,sizeof(double));

	poczatek5:
    printf("Podaj poczatek zakresu: ");
	tab_pocz_danych[0] = sczytywanie_double();
	//scanf("%lf %lf", &tab_pocz_danych[0], &tab_pocz_danych[1]);
	printf("Podaj koniec zakresu: ");
	tab_pocz_danych[1] = sczytywanie_double();
	if (tab_pocz_danych[0] > tab_pocz_danych[1])
	{
		puts("Podales wartosc poczatkowa wieksza od koncowej!");
		goto poczatek5;
	}
	printf("Podaj iloczyn: ");
	tab_pocz_danych[2] = sczytywanie_double();
	//scanf("%lf %lf", &tab_pocz_danych[2], &tab_pocz_danych[3]);
	printf("Podaj przesuniecie: ");
	tab_pocz_danych[3] = sczytywanie_double();
	puts(" ");
	tab_pocz_danych[4]=liczenie_dx(tab_pocz_danych[0],tab_pocz_danych[1],ilosc_elementow_tablicy);

	return tab_pocz_danych;
}

double liczenie_dx(double poczatek_zakresu, double koniec_zakresu, int ilosc_elementow_tablicy)
{
	double dx;
	dx = (koniec_zakresu - poczatek_zakresu) / (ilosc_elementow_tablicy - 1);
	return dx;
}

void wypelnianie_tablicy_x(double *tab_x, double dx, double poczatek_zakresu, int wyraz_tab_p, int wyraz_tab_k)
{
	int i;
	for (i = wyraz_tab_p; i<wyraz_tab_k; i++)
	{
		tab_x[i] = poczatek_zakresu + i*dx;
	}
}

void wypelnianie_tablicy_y(double *tab_x, double *tab_y, double iloczyn, double przesuniecie, int wyraz_tab_p, int wyraz_tab_k)
{
	int i;
	for (i = wyraz_tab_p; i<wyraz_tab_k; i++)
	{
		tab_y[i] = iloczyn*cos(tab_x[i] + przesuniecie);
		if (tab_y[i]<0) tab_y[i] = 0;
	}
}

void wypelnianie_tablicy_y_zaszumionych(double *tab_y, double *tab_szum, int wyraz_tab_p, int wyraz_tab_k)
{
	int a, b, i;
	char opcja[20];
	double rand_max, rand_min, rand_zakres, rand_div;

	printf("Okreslic przedzial zaszumienia? T/N :");
	poczatek1:
	scanf("%19s", opcja);
	switch (opcja[0]) {
	case 'T': {
		poczatek2:
		printf("Podaj poczatek zakresu: ");
		a = sczytywanie_int();
		//scanf("%d", &a);
		if ((a < wyraz_tab_p)||(a > wyraz_tab_k))
		{
			puts("Podales wartosc nie nalezaca do zakresu!\n");
			goto poczatek2;
		}
		poczatek3:
		printf("Podaj koniec zakresu: ");
		b = sczytywanie_int();
		//scanf("%d", &b);
		if ((b < wyraz_tab_p)||(b > wyraz_tab_k))
		{
			puts("Podales wartosc nie nalezaca do zakresu!\n");
			goto poczatek3;
		}
		if (a > b)
		{
			puts("Podales wartosc poczatkowa wieksza od koncowej!\n");
			goto poczatek2;
		}
	}; break;
	case 'N': {
		a = wyraz_tab_p;
		b = wyraz_tab_k;
	}; break;
	default: {
		printf("Nie ma takiej opcji!\n");
		printf("Wybierz T/N :");
		goto poczatek1;
	}; break;
	}

	for (i = a; i<b; i++)
	{
		rand_max = (tab_y[i] + 0.2);
		rand_min = (tab_y[i] - 0.2);
		rand_zakres = rand_max - rand_min;
		rand_div = RAND_MAX / rand_zakres;
		tab_szum[i] = rand_min + (rand() / rand_div);
	}

	if (a>wyraz_tab_p) {
		for (i = wyraz_tab_p; i<a; i++)
		{
			tab_szum[i] = tab_y[i];
		}}
	if (b<wyraz_tab_k) {
		for (i = b; i<wyraz_tab_k; i++)
		{
			tab_szum[i] = tab_y[i];
		}}
}

void wypelnianie_tablicy_y_odszumionych_mediana(double *tab_szum, double *tab_odszum, int wyraz_tab_p, int wyraz_tab_k)
{
	int i,j,k,a;
	double t;
	double *tab_sort;


	if (wyraz_tab_p == 0)
	{
		tab_odszum[0] = tab_szum[0];
		tab_odszum[1] = tab_szum[1];
		tab_sort = (double*)calloc(5, sizeof(double));
		tab_sort[0] = tab_szum[0];
		tab_sort[1] = tab_szum[1];
		tab_sort[2] = tab_szum[2];
		tab_sort[3] = tab_szum[3];
		tab_sort[4] = tab_szum[4];
		for (k = 0; k < 5; k++)
		{
			a = 0;
			for (j = 0; j < 4; j++)
			{
				if (tab_sort[j] > tab_sort[j + 1])
				{
					t = tab_sort[j];
					tab_sort[j] = tab_sort[j + 1];
					tab_sort[j + 1] = t;
					a = 1;
				}
			}
			if (a == 0) break;
		}
		tab_odszum[2] = tab_sort[2];
		free(tab_sort);

		tab_sort = (double*)calloc(5, sizeof(double));
		tab_sort[0] = tab_szum[wyraz_tab_k - 5];
		tab_sort[1] = tab_szum[wyraz_tab_k - 4];
		tab_sort[2] = tab_szum[wyraz_tab_k - 3];
		tab_sort[3] = tab_szum[wyraz_tab_k - 2];
		tab_sort[4] = tab_szum[wyraz_tab_k - 1];
		for (k = 0; k < 5; k++)
		{
			a = 0;
			for (j = 0; j < 4; j++)
			{
				if (tab_sort[j] > tab_sort[j + 1])
				{
					t = tab_sort[j];
					tab_sort[j] = tab_sort[j + 1];
					tab_sort[j + 1] = t;
					a = 1;
				}
			}
			if (a == 0) break;
		}
		tab_odszum[wyraz_tab_k - 3] = tab_sort[2];
		free(tab_sort);
		tab_odszum[wyraz_tab_k - 2] = tab_szum[wyraz_tab_k - 2];
		tab_odszum[wyraz_tab_k - 1] = tab_szum[wyraz_tab_k - 1];

		for (i = 3; i < wyraz_tab_k - 3; i++)
		{
			tab_sort = (double*)calloc(7, sizeof(double));
			tab_sort[0] = tab_szum[i - 3];
			tab_sort[1] = tab_szum[i - 2];
			tab_sort[2] = tab_szum[i - 1];
			tab_sort[3] = tab_szum[i];
			tab_sort[4] = tab_szum[i + 1];
			tab_sort[5] = tab_szum[i + 2];
			tab_sort[6] = tab_szum[i + 3];
			for (k = 0; k < 7; k++)
			{
				a = 0;
				for (j = 0; j < 6; j++)
				{
					if (tab_sort[j] > tab_sort[j + 1])
					{
						t = tab_sort[j];
						tab_sort[j] = tab_sort[j + 1];
						tab_sort[j + 1] = t;
						a = 1;
					}
				}
				if (a == 0) break;
			}
			tab_odszum[i] = tab_sort[3];
			free(tab_sort);
		}
	}
	else
	{
		tab_sort = (double*)calloc(5, sizeof(double));
		tab_sort[0] = tab_szum[wyraz_tab_k - 5];
		tab_sort[1] = tab_szum[wyraz_tab_k - 4];
		tab_sort[2] = tab_szum[wyraz_tab_k - 3];
		tab_sort[3] = tab_szum[wyraz_tab_k - 2];
		tab_sort[4] = tab_szum[wyraz_tab_k - 1];
		for (k = 0; k < 5; k++)
		{
			a = 0;
			for (j = 0; j < 4; j++)
			{
				if (tab_sort[j] > tab_sort[j + 1])
				{
					t = tab_sort[j];
					tab_sort[j] = tab_sort[j + 1];
					tab_sort[j + 1] = t;
					a = 1;
				}
			}
			if (a == 0) break;
		}
		tab_odszum[wyraz_tab_k - 3] = tab_sort[2];
		tab_odszum[wyraz_tab_k - 2] = tab_szum[wyraz_tab_k - 2];
		tab_odszum[wyraz_tab_k - 1] = tab_szum[wyraz_tab_k - 1];

		for (i = wyraz_tab_p; i < wyraz_tab_k - 3; i++)
		{
			tab_sort = (double*)calloc(7, sizeof(double));
			tab_sort[0] = tab_szum[i - 3];
			tab_sort[1] = tab_szum[i - 2];
			tab_sort[2] = tab_szum[i - 1];
			tab_sort[3] = tab_szum[i];
			tab_sort[4] = tab_szum[i + 1];
			tab_sort[5] = tab_szum[i + 2];
			tab_sort[6] = tab_szum[i + 3];
			for (k = 0; k < 7; k++)
			{
				a = 0;
				for (j = 0; j < 6; j++)
				{
					if (tab_sort[j] > tab_sort[j + 1])
					{
						t = tab_sort[j];
						tab_sort[j] = tab_sort[j + 1];
						tab_sort[j + 1] = t;
						a = 1;
					}
				}
				if (a == 0) break;
			}
			tab_odszum[i] = tab_sort[3];
			free(tab_sort);
		}
	}
}

void wypelnianie_tablicy_y_odszumionych_srednia(double *tab_szum, double *tab_odszum, int wyraz_tab_p, int wyraz_tab_k)
{
	int i;
	double srednia,suma;


	if (wyraz_tab_p == 0)
	{
		suma = tab_szum[0] + tab_szum[1] + tab_szum[2] + tab_szum[3] + tab_szum[4];
		srednia = suma / 5;
		tab_odszum[0] = srednia;
		suma = tab_szum[0] + tab_szum[1] + tab_szum[2] + tab_szum[3] + tab_szum[4] + tab_szum[5];
		srednia = suma / 6;
		tab_odszum[1] = srednia;
		suma = tab_szum[0] + tab_szum[1] + tab_szum[2] + tab_szum[3] + tab_szum[4] + tab_szum[5] + tab_szum[6];
		srednia = suma / 7;
		tab_odszum[2] = srednia;
		suma = tab_szum[wyraz_tab_k - 7] + tab_szum[wyraz_tab_k - 6] + tab_szum[wyraz_tab_k - 5] + tab_szum[wyraz_tab_k - 4] + tab_szum[wyraz_tab_k - 3] + tab_szum[wyraz_tab_k - 2] + tab_szum[wyraz_tab_k - 1];
		srednia = suma / 7;
		tab_odszum[wyraz_tab_k - 3] = srednia;
		suma = tab_szum[wyraz_tab_k - 6] + tab_szum[wyraz_tab_k - 5] + tab_szum[wyraz_tab_k - 4] + tab_szum[wyraz_tab_k - 3] + tab_szum[wyraz_tab_k - 2] + tab_szum[wyraz_tab_k - 1];
		srednia = suma / 6;
		tab_odszum[wyraz_tab_k - 2] = srednia;
		suma = tab_szum[wyraz_tab_k - 5] + tab_szum[wyraz_tab_k - 4] + tab_szum[wyraz_tab_k - 3] + tab_szum[wyraz_tab_k - 2] + tab_szum[wyraz_tab_k - 1];
		srednia = suma / 5;
		tab_odszum[wyraz_tab_k - 1] = srednia;

		for (i = 3; i < wyraz_tab_k - 3; i++)
		{
			suma = tab_szum[i - 3]+tab_szum[i - 2]+tab_szum[i - 1]+tab_szum[i]+tab_szum[i + 1]+tab_szum[i + 2]+tab_szum[i + 3];
			srednia = suma / 7;
			tab_odszum[i] = srednia;
		}
	}
	else
	{
		suma = tab_szum[wyraz_tab_k - 7] + tab_szum[wyraz_tab_k - 6] + tab_szum[wyraz_tab_k - 5] + tab_szum[wyraz_tab_k - 4] + tab_szum[wyraz_tab_k - 3] + tab_szum[wyraz_tab_k - 2] + tab_szum[wyraz_tab_k - 1];
		srednia = suma / 7;
		tab_odszum[wyraz_tab_k - 3] = srednia;
		suma = tab_szum[wyraz_tab_k - 6] + tab_szum[wyraz_tab_k - 5] + tab_szum[wyraz_tab_k - 4] + tab_szum[wyraz_tab_k - 3] + tab_szum[wyraz_tab_k - 2] + tab_szum[wyraz_tab_k - 1];
		srednia = suma / 6;
		tab_odszum[wyraz_tab_k - 2] = srednia;
		suma = tab_szum[wyraz_tab_k - 5] + tab_szum[wyraz_tab_k - 4] + tab_szum[wyraz_tab_k - 3] + tab_szum[wyraz_tab_k - 2] + tab_szum[wyraz_tab_k - 1];
		srednia = suma / 5;
		tab_odszum[wyraz_tab_k - 1] = srednia;

		for (i = wyraz_tab_p; i < wyraz_tab_k - 3; i++)
		{
			suma = tab_szum[i - 3] + tab_szum[i - 2] + tab_szum[i - 1] + tab_szum[i] + tab_szum[i + 1] + tab_szum[i + 2] + tab_szum[i + 3];
			srednia = suma / 7;
			tab_odszum[i] = srednia;
		}
	}
}

void zapis_do_pliku(double* tab_x, double* tab_y, double* tab_szum, double* tab_odszum, int ilosc_elementow_tablicy)
{
	FILE *plik;
	int i;
	plik = fopen("wynik_cos.csv", "w");
	for (i = 0; i<ilosc_elementow_tablicy; i++)
		fprintf(plik, "%lf;%lf;%lf;%lf\n", tab_x[i], tab_y[i], tab_szum[i], tab_odszum[i]);
	fclose(plik);
	printf("Plik z danymi zostal utworzony!\n \n");

}

double* realokacja_tablicy(double *tab, int nowa_ilosc_elementow_tablicy)
{
	//int i;
	//double *temp;
	//poczatek1:
	tab = (double*)realloc(tab, nowa_ilosc_elementow_tablicy * sizeof(double));
	/*if (temp != NULL)
	{
		//tab = temp;
		//free(temp);
		for (i = 0; i < nowa_ilosc_elementow_tablicy; i++)
			tab[i] = temp[i];
	}
	else
	{
		free(temp);
		goto poczatek1;
	} */
	return tab;
}

void odczyt_z_pliku()
{
	FILE *plik;
	int k,i = 0;
	char znak;
	char *tab;

	plik = fopen("wynik_cos.csv", "r");
	if (plik == NULL)
	{
		printf("Plik nie istnieje. \n");
		return 0;
	}
	else rewind(plik);

	tab = (char*)calloc(1, sizeof(char));

	while (!feof(plik))
	{
		znak = fgetc(plik);
		tab[i] = znak;
		//fscanf(plik, "%c", &tab[i]);
		tab = (char*)realloc(tab,(i + 2)*sizeof(char));
		i++;
	}
	fclose(plik);
	tab = (char*)realloc(tab,i * sizeof(char));

	printf("Oto odczytane dane z pliku!\n");
	for (k = 0; k < i; k++)
		printf("%c", tab[k]);

	free(tab);
}

int sczytywanie_int() {
	int temp;
	while (1) {
		if (scanf("%d", &temp) == 1) {
			return temp;
		}
		printf("Prosze podac wartosc typu int: ");
		scanf("%*s");
	}
}

double sczytywanie_double() {
	double temp;
	while (1) {
		if (scanf("%lf", &temp) == 1) {
			return temp;
		}
		printf("Prosze podac wartosc typu double: ");
		scanf("%*s");
	}
}

void generacja_wykresu(double* tab_x, double* tab_2, int ilosc_elementow_tablicy)
{
	FILE *Wsk_do_pliku;
	int i;

	Wsk_do_pliku = fopen("cosinusik.html", "w");

	fprintf(Wsk_do_pliku, "<html>\n");
	fprintf(Wsk_do_pliku, "<head>\n");
	fprintf(Wsk_do_pliku, "<script type=\"text/javascript\" src=\"https://www.google.com/jsapi\"></script>\n");
	fprintf(Wsk_do_pliku, "<script type=\"text/javascript\">\n");
	fprintf(Wsk_do_pliku, "google.load(\"visualization\", \"1\", {packages:[\"corechart\"]});\n");
	fprintf(Wsk_do_pliku, "google.setOnLoadCallback(drawChart);\n");
	fprintf(Wsk_do_pliku, "function drawChart() {\n");
	fprintf(Wsk_do_pliku, "var data = google.visualization.arrayToDataTable([\n");
	fprintf(Wsk_do_pliku, "['i', 'dane z tablicy'],\n");

	for (i = 0; i < ilosc_elementow_tablicy; i++)
	{
		fprintf(Wsk_do_pliku, "[%lf, %lf],\n", tab_x[i], tab_2[i]);   //przekazanie danych na wykres
	}

	fprintf(Wsk_do_pliku, "]);\n");

	fprintf(Wsk_do_pliku, "var options = {\n");
	fprintf(Wsk_do_pliku, "title: 'rozklad Gaussa'\n");
	fprintf(Wsk_do_pliku, "};\n");
	fprintf(Wsk_do_pliku, "var chart = new google.visualization.LineChart(document.getElementById('chart_div'));\n");
	fprintf(Wsk_do_pliku, "chart.draw(data, {\n");
	fprintf(Wsk_do_pliku, "colors: ['blue']\n");
	fprintf(Wsk_do_pliku, "}\n");
	fprintf(Wsk_do_pliku, ");\n");
	fprintf(Wsk_do_pliku, "}\n");
	fprintf(Wsk_do_pliku, "</script>\n");
	fprintf(Wsk_do_pliku, "</head>\n");
	fprintf(Wsk_do_pliku, "<body>\n");
	fprintf(Wsk_do_pliku, "<div id=\"chart_div\" style=\"width: 900px; height: 500px;\"></div>\n");
	fprintf(Wsk_do_pliku, "</body>\n");
	fprintf(Wsk_do_pliku, "</html>\n");

	fclose(Wsk_do_pliku);
}
