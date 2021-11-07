#pragma once
#include "Cblad.h"
#include <iostream>
#include <Windows.h>
using namespace std;

template <class typ>
typ daj_wartosc(typ dolny_zakres, typ gorny_zakres)
{
	int a,b;
	typ wartosc_temp;
poczatek2:
	a = 0;
	cin >> wartosc_temp;
	while (cin.fail() == 1)
	{
		a = 1;
		cin.clear();
		cin.ignore(1000, '\n');
	}
	if (a == 1)
	{
		Cblad(101);
		goto poczatek2;
	}
	if (wartosc_temp < dolny_zakres || wartosc_temp > gorny_zakres)
	{
		Cblad(102);
		cin.clear();
		cin.ignore(1000, '\n');
		goto poczatek2;
	}
	return wartosc_temp;
}

template <class typ>
typ hmm()
{
	cout << endl;
	for (int i = 0; i < 3; i++)
	{
		Sleep(800);
		cout << ".";
	}
	Sleep(800);
	cout << endl;
}

template <class typ>
typ hmm2()
{
	for (int i = 0; i < 3; i++)
	{
		Sleep(800);
		cout << ".";
	}
	Sleep(800);
	cout << endl;
}