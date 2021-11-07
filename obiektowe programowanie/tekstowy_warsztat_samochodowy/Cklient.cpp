#define _CRT_SECURE_NO_WARNINGS
#include "Cklient.h"
using namespace std;


Cklient::Cklient()
{
	char imie_temp[300], nazwisko_temp[300];

	cout << "Kliencie podaj swoje dane osobowe!" << endl;
	cout << "Imie: ";
	cin >> imie_temp;
	cout << "Nazwisko: ";
	cin >> nazwisko_temp; cout << endl;
	strcpy(imie, imie_temp);
	strcpy(nazwisko, nazwisko_temp);

	samochod = new Cauto_naprawa;
}


Cklient::~Cklient()
{
	delete samochod;
}

void Cklient::drukowanie_faktury()
{
	hmm<void>(); cout << "NASTEPUJE DRUKOWANIE FAKTURY!"; hmm<void>();

	fstream plik;
	plik.open("Fakturka.txt", ios::out);
	plik << "Faktura" << endl << "-----------------" << endl;
	plik << "Dane osobowe: " << endl;
	plik << "Imie:               " << imie << endl;
	plik << "Nazwisko:           " << nazwisko << endl;
	plik << "Marka auta:         " << samochod->podaj_marke() << endl;
	plik << "Model auta:         " << samochod->podaj_model() << endl;
	plik << "Rok produkcji:      " << samochod->podaj_rok_produkcji() << endl;
	plik << "Pojemnosc silnika:  " << samochod->podaj_pojemnosc_silnika() << endl << endl;
	plik << "Wykonane uslugi:    " << endl;
	if (samochod->daj_stan_naprawy(0) == 1)
	{
		plik << "- wymiana filtru oleju\n  Koszt uslugi: 40 zl\n";
	}
	if (samochod->daj_stan_naprawy(1) == 1)
	{
		plik << "- nowy rozrusznik\n  Koszt uslugi: 550 zl\n";
	}
	if (samochod->daj_stan_naprawy(2) == 1)
	{
		plik << "- konserwacja rozrusznika\n  Koszt uslugi: 180 zl\n";
	}
	if (samochod->daj_stan_naprawy(3) == 1)
	{
		plik << "- wymiana wahacza\n  Koszt uslugi: 20 zl\n";
	}
	if (samochod->daj_stan_naprawy(4) == 1)
	{
		plik << "- wymiana wahacza\n  Koszt uslugi: 120 zl\n";
	}
	if (samochod->daj_stan_naprawy(5) == 1)
	{
		plik << "- wymiana klockow hamulcowych\n  Koszt uslugi: 100 zl\n";
	}
	plik << endl << "Laczny koszt: " << samochod->daj_koszt_naprawy() << " zl" << endl;
	plik.close();
}