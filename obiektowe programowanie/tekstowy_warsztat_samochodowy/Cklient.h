#pragma once
#include "Cauto_naprawa.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip> 

class Cklient
{
public:
	Cklient();
	~Cklient();
	Cauto *samochod;

private:
	char imie[300];
	char nazwisko[300];

public:
	void drukowanie_faktury();
	inline const string podaj_imie() { return imie; };
	inline const string podaj_nazwisko() { return nazwisko; };
};

