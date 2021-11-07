#include "Interfejs.h"


void Interfejs::pokaz_plansze(Plansza *plansza) {
	cout << endl << "Twoja Plansza." << endl;
	cout << "    1 2 3 4 5 6 7 8 9 10" << endl;
	for (int i = 0; i < plansza->wysokosc; i++) {
		if (i<9) {
			cout << i + 1 << "   ";
		}
		else {
			cout << i + 1 << "  ";
		}
		for (int j = 0; j < plansza->szerokosc; j++) {
			if (plansza->macierz_pol[i][j]->czy_odkryte) {
				if (plansza->macierz_pol[i][j]->czy_nalezy_do_statku) {
					cout << "X ";
				}
				else {
					cout << "O ";
				}
			}
			else {
				if (plansza->macierz_pol[i][j]->czy_nalezy_do_statku) {
					cout << "H ";
				}
				else {
					cout << "- ";
				}
			}
		}
		cout << endl;
	}
	cout << endl;
}

void Interfejs::pokaz_plansze_przeciwnika(Plansza *plansza) {
	cout << endl << "Plansza Przeciwnika." << endl;
	cout << "    1 2 3 4 5 6 7 8 9 10" << endl;
	for (int i = 0; i < plansza->wysokosc; i++) {
		if (i<9) {
			cout << i + 1 << "   ";
		}
		else {
			cout << i + 1 << "  ";
		}
		for (int j = 0; j < plansza->szerokosc; j++) {
			if (plansza->macierz_pol[i][j]->czy_odkryte) {
				if (plansza->macierz_pol[i][j]->czy_nalezy_do_statku) {
					cout << "X ";
				}
				else {
					cout << "O ";
				}
			}
			else {
				cout << "- ";
			}
		}
		cout << endl;
	}
	cout << endl;
}