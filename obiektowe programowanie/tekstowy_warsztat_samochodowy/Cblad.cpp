#include "Cblad.h"
#include <iostream>
using namespace std;


Cblad::Cblad(int kod_bledu_temp)
{
	kod_bledu = kod_bledu_temp;
	if (kod_bledu == 101) cout << "Podales zly format! Podaj wartosc ponownie: ";
	if (kod_bledu == 102) cout << "Podana wartosc nie nalezy do zakresu! Podaj wartosc ponownie: ";
}


Cblad::~Cblad()
{
}
