#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Ckoszt.h"
#include "Cauto.h"
#include <iostream>
#include <string>

class Cauto_naprawa :
	public Cauto
{
public:
	Cauto_naprawa();
	~Cauto_naprawa();

private:
	bool stan_naprawy[10];
	Ckoszt koszt_naprawy;

public:
	int daj_koszt_naprawy();
	int daj_stan_naprawy(int i);
	void wyswietl_koszt_naprawy();
	void wypisanie_usterki();
	void naprawa();
};

