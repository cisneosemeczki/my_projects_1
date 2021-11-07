#include "Cobsluga.h"
using namespace std;


Cobsluga::Cobsluga(Cklient* klient_temp)
{
	klient = klient_temp;
}


Cobsluga::~Cobsluga()
{
}

void Cobsluga::obsluga_klienta()
{
	hmm<void>(); cout << "Mechanik: Witam " << klient->podaj_imie() << " w naszym warsztacie samochodowym!"; hmm<void>();
	cout << "Coz to za usterka sprowadza do nas?"; hmm<void>();

	klient->samochod->losowanie_usterki();
	klient->samochod->wypisanie_usterki();
	klient->samochod->naprawa();
	klient->samochod->wyswietl_koszt_naprawy();
	klient->drukowanie_faktury();
}
