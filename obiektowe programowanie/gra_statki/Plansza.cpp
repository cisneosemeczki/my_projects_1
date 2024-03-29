#include "Plansza.h"


Plansza::Plansza() {

}

Plansza::Plansza(int szerokosc, int wysokosc) {
	this->szerokosc = szerokosc;
	this->wysokosc = wysokosc;

	for (int i = 0; i<wysokosc; i++) {		// tworzenie 10 rz�d�w
		vector<Pole*> rzad;
		for (int j = 0; j<szerokosc; j++) {	
			rzad.push_back(new Pole(j, i));	// wype�nianie rz�d�w polami
		}
		macierz_pol.push_back(rzad);
	}
}

Plansza::~Plansza() {
	for (int i = 0; i<wysokosc; i++) {
		for (int j = 0; j<szerokosc; j++) {
			delete macierz_pol[i][j];
		}
	}
}

void Plansza::init_macierz() {				//do wczytywania pliku 
	for (int i = 0; i<wysokosc; i++) {
		vector<Pole*> rzad;
		macierz_pol.push_back(rzad);
	}
}