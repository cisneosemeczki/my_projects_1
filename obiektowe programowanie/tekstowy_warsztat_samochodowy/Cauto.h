#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Cwczytaj.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

class Cauto
{
public:
	Cauto();
	~Cauto();

protected:
	bool rozrusznik;
	bool wahacz;
	bool skrzynia_biegow;
	bool klocki_hamulcowe;
	bool filtr_oleju;
	char marka[300];
	char model[300];
	int rok_produkcji;
	float pojemnosc_silnika;

public:
	void losowanie_usterki();
	virtual void wypisanie_usterki();
	virtual inline void naprawa() {};
	virtual inline void wyswietl_koszt_naprawy() {};
	virtual inline int daj_koszt_naprawy() { return 1; };
	virtual inline int daj_stan_naprawy(int) { return 1; };

	inline const string podaj_marke() { return marka; };
	inline const string podaj_model() { return model; };
	inline const int podaj_rok_produkcji() { return rok_produkcji; };
	inline const float podaj_pojemnosc_silnika() { return pojemnosc_silnika; };
};



