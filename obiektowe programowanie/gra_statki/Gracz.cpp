#include "Gracz.h"

Gracz::Gracz() {}

Gracz::Gracz(string nazwa) {
	this->nazwa = nazwa;
	this->plansza = new Plansza(10, 10);
	this->czy_gracz_komputerowy = false;
	this->liczba_strzalow_trafionych = 0;
	this->liczba_strzalow = 0;
}

Gracz::~Gracz() {
	for (int i = 0; i<statki.size(); i++) {
		delete statki[i];
	}

	delete plansza;
}

int Gracz::wez_losowa_kolumne() {
	return rand() % plansza->szerokosc;
}

int Gracz::wez_losowy_wiersz() {
	return rand() % plansza->wysokosc;
}

int Gracz::wez_losowa_orientacje() {
	return rand() % 2;
}

void Gracz::dodaj_statek(Statek *statek) {
	this->statki.push_back(statek);
}

bool Gracz::czy_przegral() {
	for (int i = 0; i<statki.size(); i++) {
		if (!statki[i]->czy_zatopiony) {
			return false;
		}
	}
	return true;
}

bool Gracz::czy_stracil_statek() {
	for (int i = 0; i<statki.size(); i++) {
		if (statki[i]->czy_trafiony_zatopiony()) {
			(*statki[i])--;  // zatop statek
			return true;
		}
	}
	return false;
}

GraczKomputer::GraczKomputer() : Gracz("Komputer") {
	this->czy_gracz_komputerowy = true;
	zmien_ustawienia_na_domyslne();
}

void GraczKomputer::uaktualnij_dostepne_pola(Plansza *plansza) {
	dostepne_pola.clear();
	for (int i = 0; i<plansza->wysokosc; i++) {
		for (int j = 0; j<plansza->szerokosc; j++) {
			Pole *pole = plansza->macierz_pol[i][j];
			if (!pole->czy_odkryte) {
				dostepne_pola.push_back(pole);
			}
		}
	}
}

Pole *GraczKomputer::wez_losowe_pole() {
	pierwsze_trafione_pole = dostepne_pola[rand() % dostepne_pola.size()];
	ostatnio_trafione_pole = pierwsze_trafione_pole;
	return ostatnio_trafione_pole;
}

Pole *GraczKomputer::wez_przewidywane_pole() {
	int x_pozycja;
	int y_pozycja;
	bool czy_poprawne = false;

	do {
		if (kierunek_ostrzalu == ORIENTACJA_PIONOWA) {
			x_pozycja = ostatnio_trafione_pole->x_pozycja;
			y_pozycja = ostatnio_trafione_pole->y_pozycja + zwrot_ostrzalu;						// zwrot ostrza³u ma wartoœci 1 lub -1
		}
		else {
			x_pozycja = ostatnio_trafione_pole->x_pozycja + zwrot_ostrzalu;
			y_pozycja = ostatnio_trafione_pole->y_pozycja;
		}

		ostatnio_trafione_pole = wez_dostepne_pole(x_pozycja, y_pozycja);
		if (ostatnio_trafione_pole != nullptr) {
			czy_poprawne = true;
		}
		else {
			zmien_ostrzal();
		}

	} while (!czy_poprawne);

	return ostatnio_trafione_pole;
}

Pole * GraczKomputer::wez_dostepne_pole(int x_pozycja, int y_pozycja) {
	if (x_pozycja >= 0 && x_pozycja < plansza->szerokosc && y_pozycja >= 0 && y_pozycja < plansza->wysokosc) {
		for (int i = 0; i <dostepne_pola.size(); i++) {
			if (dostepne_pola[i]->x_pozycja == x_pozycja && dostepne_pola[i]->y_pozycja == y_pozycja) {
				return dostepne_pola[i];
			}
		}
	}
	return nullptr;
}

void GraczKomputer::zmien_ustawienia_na_domyslne() {
	czy_jest_statek_do_zatopienia = false;
	czy_jest_znany_zwrot = false;
	kierunek_ostrzalu = ORIENTACJA_PIONOWA;
	zwrot_ostrzalu = 1;
}

void GraczKomputer::zmien_ostrzal() {
	ostatnio_trafione_pole = pierwsze_trafione_pole;

	if (!czy_jest_znany_zwrot) {
		zwrot_ostrzalu *= -1;
		czy_jest_znany_zwrot = true;
	}
	else {
		if (kierunek_ostrzalu == ORIENTACJA_PIONOWA) {
			kierunek_ostrzalu = ORIENTACJA_POZIOMA;
		}
		else {
			kierunek_ostrzalu = ORIENTACJA_PIONOWA;
		}
		czy_jest_znany_zwrot = false;
	}
}