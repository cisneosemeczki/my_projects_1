#include <iostream>
#include <string>
#include <cstdlib>
#include "Plansza.h"
#include "Statek.h"

class Gracz {
protected:
	string nazwa;
	Plansza *plansza;
	vector<Statek*> statki;
	bool czy_gracz_komputerowy;
	int liczba_strzalow_trafionych;
	int liczba_strzalow;

public:
	Gracz();
	Gracz(string nazwa);
	~Gracz();


	int wez_losowa_kolumne();
	int wez_losowy_wiersz();
	int wez_losowa_orientacje();
	void dodaj_statek(Statek *statek);
	bool czy_przegral();
	bool czy_stracil_statek();

	friend class Gra;
	friend class Interfejs;
};

class GraczKomputer : public Gracz {
private:
	Pole *pierwsze_trafione_pole;
	Pole *ostatnio_trafione_pole;
	bool czy_jest_statek_do_zatopienia;
	bool czy_jest_znany_zwrot;
	int kierunek_ostrzalu;
	int zwrot_ostrzalu;
	vector<Pole*> dostepne_pola;

public:
	GraczKomputer();

	void uaktualnij_dostepne_pola(Plansza *plansza);
	Pole *wez_losowe_pole();
	Pole *wez_przewidywane_pole();
	void zmien_ostrzal();
	void zmien_ustawienia_na_domyslne();							//wyzerowanie flag
	Pole * wez_dostepne_pole(int x_pozycja, int y_pozycja);

	friend class Interfejs;
};
