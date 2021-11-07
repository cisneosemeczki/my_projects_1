#include "Gra.h"


Gra::Gra() {
}

Gra::~Gra() {
	delete gracz_1;
	delete gracz_2;
}

Gra::Gra(string nazwa_gracza) {
	this->gracz_1 = new Gracz(nazwa_gracza);
	this->gracz_2 = new GraczKomputer();
	czy_tura_pierwszego_gracza = true;
}

Gra::Gra(string nazwa_gracza_1, string nazwa_gracza_2) {
	this->gracz_1 = new Gracz(nazwa_gracza_1);
	this->gracz_2 = new Gracz(nazwa_gracza_2);
	czy_tura_pierwszego_gracza = true;
}

bool Gra::czy_koniec_gry() {
	return gracz_1->czy_przegral() || gracz_2->czy_przegral();
}

Gracz *Gra::wez_wygranego() {
	if (gracz_1->czy_przegral()) {
		return gracz_2;
	}
	else if (gracz_2->czy_przegral()) {
		return gracz_1;
	}
	return nullptr;
}
