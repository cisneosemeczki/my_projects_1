#include "Interfejs.h"


Interfejs::Interfejs() {
	gra = nullptr;
	czy_gra_zostala_zainicjonowana = false;
}

Interfejs::~Interfejs() {
	usun_gre();
}

void Interfejs::start() {
	printf(POKAZ_POWITALNY_TEKST);

	do {
		if (czy_wczytac_gre()) {
			wczytaj_gre();
		}
		else {
			init_gre();
			init_statki();
			czy_gra_zostala_zainicjonowana = true;
		}

		if (czy_gra_zostala_zainicjonowana) {
			zacznij_gre();
			wyswietl_zwyciezce();
			usun_gre();
		}
		else {
			printf(POWIADOM_O_BRAKU_INICJALIZCJI_GRY);
			system("PAUSE");
		}
	} while (czy_chcesz_zagrac_ponownie());
}

void Interfejs::init_gre() {
	int liczba_graczy;
	string nazwa_gracza_1;
	string nazwa_gracza_2;

	do {
		printf(ZAPYTAJ_O_LICZBE_GRACZY);
		liczba_graczy = czytaj_z_konsoli_liczbe();
	} while (liczba_graczy < 1 || liczba_graczy > 2);

	do {
		printf(ZAPYTAJ_O_NAZWE_DLA_GRACZA_NUMER, 1);
		nazwa_gracza_1 = czytaj_z_konsoli();
	} while (nazwa_gracza_1.length() == 0);

	if (liczba_graczy == 1) {
		gra = new Gra(nazwa_gracza_1);
	}
	else {
		do {
			printf(ZAPYTAJ_O_NAZWE_DLA_GRACZA_NUMER, 2);
			nazwa_gracza_2 = czytaj_z_konsoli();
		} while (nazwa_gracza_2.length() == 0);

		gra = new Gra(nazwa_gracza_1, nazwa_gracza_2);
	}

}

int Interfejs::wez_kolumne() {
	printf(ZAPYTAJ_O_KOLUMNE);
	return czytaj_z_konsoli_liczbe() - 1;
}

int Interfejs::wez_wiersz() {
	printf(ZAPYTAJ_O_WIERSZ);
	return czytaj_z_konsoli_liczbe() - 1;
}

int Interfejs::wez_orientacje() {
	printf(ZAPYTAJ_O_POZIOMA_ORIENTACJE);
	czytaj_z_konsoli();
	if (linia == "y" || linia == "Y") {
		return ORIENTACJA_POZIOMA;
	}
	return ORIENTACJA_PIONOWA;
}

bool Interfejs::czy_wylosowac_statki() {
	system("cls");
	printf(ZAPYTAJ_O_WYLOSOWANIE_STATKOW);
	czytaj_z_konsoli();
	return linia == "y" || linia == "Y";
}

void Interfejs::init_statki_dla_gracza(Gracz *gracz) {
	bool czy_losowo = true;
	if (!gracz->czy_gracz_komputerowy) {
		system("cls");
		printf(POWIADOM_GRACZA_O_INICJACJI_STATKOW, gracz->nazwa.c_str());
		system("PAUSE");

		czy_losowo = czy_wylosowac_statki();
	}

	for (int i = 0; i<LICZBA_STATKOW; i++) {
		init_statek_dla_gracza(gracz, DLUGOSCI_STATKOW[i], czy_losowo);
	}

	if (!gracz->czy_gracz_komputerowy) {
		system("cls");
		pokaz_plansze(gracz->plansza);
		system("PAUSE");
	}
}

void Interfejs::init_statki() {
	init_statki_dla_gracza(gra->gracz_1);
	init_statki_dla_gracza(gra->gracz_2);
}

void Interfejs::init_statek_dla_gracza(Gracz *gracz, int dlugosc, bool czy_losowo) {
	Statek *statek = new Statek(dlugosc);
	int numer_kolumny;
	int numer_wiersza;
	int orientacja;

	bool czy_mozna_utworzyc = false;

	do {
		if (czy_losowo) {
			numer_kolumny = gracz->wez_losowa_kolumne();
			numer_wiersza = gracz->wez_losowy_wiersz();
			orientacja = gracz->wez_losowa_orientacje();

			czy_mozna_utworzyc = statek->czy_mozna_utworzyc_statek(gracz->plansza, orientacja, numer_kolumny, numer_wiersza);
		}
		else {
			system("cls");
			pokaz_plansze(gracz->plansza);
			printf(POWIADOM_O_INICJACJI_STATKU_O_DLUGOSCI, dlugosc);
			do {
				numer_kolumny = wez_kolumne();
			} while (numer_kolumny < 0 || numer_kolumny >= gracz->plansza->wysokosc);

			do {
				numer_wiersza = wez_wiersz();
			} while (numer_wiersza < 0 || numer_wiersza >= gracz->plansza->szerokosc);

			do {
				orientacja = wez_orientacje();
			} while (orientacja != ORIENTACJA_PIONOWA && orientacja != ORIENTACJA_POZIOMA);

			if (statek->czy_mozna_utworzyc_statek(gracz->plansza, orientacja, numer_kolumny, numer_wiersza)) {
				czy_mozna_utworzyc = true;
			}
			else {
				printf(POWIADOM_O_BRAKU_MOZLIWOSCI_UTWORZENIA_STATKU);
				system("PAUSE");
			}
		}
	} while (!czy_mozna_utworzyc);

	statek->utworz_statek(gracz->plansza, orientacja, numer_kolumny, numer_wiersza);
	gracz->dodaj_statek(statek);
}

void Interfejs::zacznij_gre() {
	Gracz *gracz_atakujacy;
	Gracz *gracz_broniacy;
	Gracz *temp;

	bool czy_pudlo = false;

	if (gra->czy_tura_pierwszego_gracza) {
		gracz_atakujacy = gra->gracz_1;
		gracz_broniacy = gra->gracz_2;
	}
	else {
		gracz_broniacy = gra->gracz_1;
		gracz_atakujacy = gra->gracz_2;
	}

	if (!gracz_atakujacy->czy_gracz_komputerowy && !gracz_broniacy->czy_gracz_komputerowy) {
		system("cls");
		printf(POWIADOM_GRACZA_O_TURZE, gracz_atakujacy->nazwa.c_str());
		system("PAUSE");
	}

	do {
		if (czy_pudlo) {
			gra->czy_tura_pierwszego_gracza = !gra->czy_tura_pierwszego_gracza;

			temp = gracz_atakujacy;
			gracz_atakujacy = gracz_broniacy;
			gracz_broniacy = temp;

			if (!gracz_atakujacy->czy_gracz_komputerowy && !gracz_broniacy->czy_gracz_komputerowy) {
				system("cls");
				printf(POWIADOM_GRACZA_O_TURZE, gracz_atakujacy->nazwa.c_str());
				system("PAUSE");
			}
		}

		if (gracz_atakujacy->czy_gracz_komputerowy) {
			czy_pudlo = !strzel_w_pole_gracza(gracz_broniacy, (GraczKomputer*)gracz_atakujacy);
		}
		else {
			czy_pudlo = !strzel_w_pole_gracza(gracz_broniacy, gracz_atakujacy);
		}
	} while (!gra->czy_koniec_gry());
}

void Interfejs::wyswietl_zwyciezce() {
	system("cls");
	printf(POKAZ_ZWYCIEZCE, gra->wez_wygranego()->nazwa.c_str());
	printf(POKAZ_STATYSTYKI, gra->wez_wygranego()->liczba_strzalow_trafionych, gra->wez_wygranego()->liczba_strzalow);
	system("PAUSE");
}

void Interfejs::usun_gre() {
	delete gra;
	gra = nullptr;
	czy_gra_zostala_zainicjonowana = false;
}

bool Interfejs::czy_chcesz_zagrac_ponownie() {
	printf(ZAPYTAJ_O_PONOWNA_GRE);
	czytaj_z_konsoli();
	return linia == "y" || linia == "Y";
}

bool Interfejs::strzel_w_pole_gracza(Gracz *przeciwnik, Gracz *gracz) {
	int numer_kolumny;
	int numer_wiersza;

	do {
		system("cls");
		printf(POKAZ_STATYSTYKI, gracz->liczba_strzalow_trafionych, gracz->liczba_strzalow);
		pokaz_plansze(gracz->plansza);
		pokaz_plansze_przeciwnika(przeciwnik->plansza);

		do {
			numer_kolumny = wez_kolumne();
		} while (numer_kolumny < 0 || numer_kolumny >= przeciwnik->plansza->wysokosc);

		do {
			numer_wiersza = wez_wiersz();
		} while (numer_wiersza < 0 || numer_wiersza >= przeciwnik->plansza->szerokosc);

		if (przeciwnik->plansza->macierz_pol[numer_wiersza][numer_kolumny]->czy_odkryte) {
			printf(POWIADOM_O_ODKRYTYM_POLU);
			system("PAUSE");
		}
		else {
			przeciwnik->plansza->macierz_pol[numer_wiersza][numer_kolumny]->czy_odkryte = true;

			if (przeciwnik->plansza->macierz_pol[numer_wiersza][numer_kolumny]->czy_nalezy_do_statku) {
				if (przeciwnik->czy_stracil_statek()) {
					printf(POWIADOM_O_ZATOPIENIU);
				}
				else {
					printf(POWIADOM_O_TRAFIONYM_STRZALE);
				}
				gracz->liczba_strzalow_trafionych++;
				gracz->liczba_strzalow++;
				system("PAUSE");
				return true;
			}
			else {
				printf(POWIADOM_O_CHYBIONYM_STRZALE);
				gracz->liczba_strzalow++;
				system("PAUSE");
				return false;
			}
		}

	} while (true);
}

bool Interfejs::strzel_w_pole_gracza(Gracz *przeciwnik, GraczKomputer *gracz_komputerowy) {
	Pole *pole_do_ostrzalu;

	gracz_komputerowy->uaktualnij_dostepne_pola(przeciwnik->plansza);

	if (gracz_komputerowy->czy_jest_statek_do_zatopienia) {
		pole_do_ostrzalu = gracz_komputerowy->wez_przewidywane_pole();
	}
	else {
		pole_do_ostrzalu = gracz_komputerowy->wez_losowe_pole();
	}

	pole_do_ostrzalu->czy_odkryte = true;

	if (pole_do_ostrzalu->czy_nalezy_do_statku) {
		if (przeciwnik->czy_stracil_statek()) {
			gracz_komputerowy->zmien_ustawienia_na_domyslne();
		}
		else {
			gracz_komputerowy->czy_jest_statek_do_zatopienia = true;
		}
		gracz_komputerowy->liczba_strzalow_trafionych++;
		gracz_komputerowy->liczba_strzalow++;
		return true;
	}
	else {
		gracz_komputerowy->zmien_ostrzal();
		gracz_komputerowy->liczba_strzalow++;
		return false;
	}
}

string Interfejs::czytaj_z_konsoli() {
	getline(cin, linia);
	if (linia == "q") {
		printf(POWIADOM_O_ZAMYKANIU_GRY);
		usun_gre();
		system("PAUSE");
		exit(0);
	}
	else if (linia == "s") {
		if (czy_gra_zostala_zainicjonowana) {
			zapisz_gre();
		}
		else {
			printf(POWIADOM_O_BRAKU_INICJALIZCJI_GRY);
			printf(POWIADOM_O_BLEDZIE_ZAPISANIU_PLIKU);
		}
		printf(POWIADOM_O_ZAMYKANIU_GRY);
		usun_gre();
		system("PAUSE");
		exit(0);
	}
	else if (linia == "h") {
		printf(POKAZ_POMOC);
		linia = "";
	}
	return linia;
}

int Interfejs::czytaj_z_konsoli_liczbe() {
	czytaj_z_konsoli();
	if (linia.length() == 0) {
		return -1;
	}

	for (int i = 0; i<linia.length(); i++) {
		if ((char)linia[i] < 48 || (char)linia[i] > 57) {
			return -1;
		}
	}
	return stoi(linia);
}

bool Interfejs::czy_wczytac_gre() {
	ifstream plik(NAZWA_PLIKU_ZAPISANEJ_GRY);
	if (plik.good()) {
		printf(ZAPYTAJ_CZY_WCZYTAC_GRE);
		czytaj_z_konsoli();
		return linia == "y" || linia == "Y";
	}
	return false;
}
