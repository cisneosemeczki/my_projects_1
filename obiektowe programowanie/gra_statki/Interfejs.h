#include <iostream>
#include <fstream>
#include "Gra.h"
#include "komunikaty.h"

static const char* NAZWA_PLIKU_ZAPISANEJ_GRY = "ZapisanaGra.txt";
static const int LICZBA_STATKOW = 6;
static const int DLUGOSCI_STATKOW[LICZBA_STATKOW] = { 4, 4, 3, 3, 2, 2 };

class Interfejs {
private:
	Gra *gra;
	bool czy_gra_zostala_zainicjonowana;
	string linia;

	string czytaj_z_konsoli();
	int czytaj_z_konsoli_liczbe();

	int wez_kolumne();
	int wez_wiersz();
	int wez_orientacje();
	bool czy_wylosowac_statki();
	bool czy_chcesz_zagrac_ponownie();
	bool czy_wczytac_gre();

	void init_gre();

	void init_statki();
	void init_statki_dla_gracza(Gracz *gracz);
	void init_statek_dla_gracza(Gracz *gracz, int dlugosc, bool czy_losowo);

	void zacznij_gre();
	void wyswietl_zwyciezce();
	void usun_gre();
	bool strzel_w_pole_gracza(Gracz *przeciwnik, Gracz *gracz);
	bool strzel_w_pole_gracza(Gracz *przeciwnik, GraczKomputer *gracz_komputerowy);

	void wczytaj_gre();
	void zapisz_gre();

	void pokaz_plansze(Plansza *plansza);
	void pokaz_plansze_przeciwnika(Plansza *plansza);

public:
	Interfejs();
	~Interfejs();

	void start();
};
