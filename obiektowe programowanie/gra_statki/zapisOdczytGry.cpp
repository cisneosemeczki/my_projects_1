#include "Interfejs.h"


void Interfejs::wczytaj_gre() {
	fstream plik;
	plik.open(NAZWA_PLIKU_ZAPISANEJ_GRY, ios::in | ios::out);

	gra = new Gra();
	try {
		int x_index;
		int y_index;
		int orientacja;
		int size;
		bool czy_gracz_komputerowy;
		Gracz *gracz;
		Gracz **gracze[2] = { &gra->gracz_1, &gra->gracz_2 };
		Plansza *plansza;
		Pole *pole;
		Statek *statek;


		getline(plik, linia);
		gra->czy_tura_pierwszego_gracza = (bool)stoi(linia);

		for (int ii = 0; ii < 2; ii++) {
			getline(plik, linia);
			czy_gracz_komputerowy = (bool)stoi(linia);

			if (czy_gracz_komputerowy) {
				gracz = new GraczKomputer();
				gracz->czy_gracz_komputerowy = true;

				getline(plik, linia);
				((GraczKomputer *)gracz)->czy_jest_statek_do_zatopienia = (bool)stoi(linia);

				getline(plik, linia);
				((GraczKomputer *)gracz)->czy_jest_znany_zwrot = (bool)stoi(linia);

				getline(plik, linia);
				((GraczKomputer *)gracz)->kierunek_ostrzalu = stoi(linia);

				getline(plik, linia);
				((GraczKomputer *)gracz)->zwrot_ostrzalu = stoi(linia);
			}
			else {
				gracz = new Gracz();
				gracz->czy_gracz_komputerowy = false;
			}

			getline(plik, linia);
			gracz->nazwa = linia;
			getline(plik, linia);
			gracz->liczba_strzalow_trafionych = stoi(linia);
			getline(plik, linia);
			gracz->liczba_strzalow = stoi(linia);

			plansza = new Plansza();
			getline(plik, linia);
			plansza->wysokosc = stoi(linia);
			getline(plik, linia);
			plansza->szerokosc = stoi(linia);
			plansza->init_macierz();

			for (int i = 0; i < plansza->wysokosc; i++) {
				for (int j = 0; j < plansza->szerokosc; j++) {
					pole = new Pole(j, i);

					getline(plik, linia);
					pole->czy_nalezy_do_statku = (bool)stoi(linia);

					getline(plik, linia);
					pole->czy_odkryte = (bool)stoi(linia);

					plansza->macierz_pol[i].push_back(pole);
				}
			}

			gracz->plansza = plansza;

			getline(plik, linia);
			size = stoi(linia);

			for (int i = 0; i < size; i++) {
				statek = new Statek();
				getline(plik, linia);
				statek->dlugosc = stoi(linia);
				getline(plik, linia);
				statek->czy_zatopiony = (bool)stoi(linia);

				getline(plik, linia);
				x_index = stoi(linia);
				getline(plik, linia);
				y_index = stoi(linia);
				getline(plik, linia);
				orientacja = stoi(linia);
				statek->utworz_statek(plansza, orientacja, x_index, y_index);

				gracz->statki.push_back(statek);
			}
			*gracze[ii] = gracz;
		}

		for (int ii = 0; ii < 2; ii++) {
			getline(plik, linia);
			int x_pozycja_pierwsze = stoi(linia);
			getline(plik, linia);
			int y_pozycja_pierwsze = stoi(linia);

			getline(plik, linia);
			int x_pozycja_ostatnio = stoi(linia);
			getline(plik, linia);
			int y_pozycja_ostatnio = stoi(linia);

			gracz = *gracze[ii];
			plansza = (*gracze[(ii + 1) % 2])->plansza;

			if (gracz->czy_gracz_komputerowy) {
				((GraczKomputer *)gracz)->pierwsze_trafione_pole = plansza->macierz_pol[y_pozycja_pierwsze][x_pozycja_pierwsze];
				((GraczKomputer *)gracz)->ostatnio_trafione_pole = plansza->macierz_pol[y_pozycja_ostatnio][x_pozycja_ostatnio];
			}
		}

		printf(POWIADOM_O_WCZYTANIU_PLIKU);
		czy_gra_zostala_zainicjonowana = true;
		plik.close();
	}
	catch (...) {
		usun_gre();
		printf(POWIADOM_O_BLEDZIE_CZYTANIA_PLIKU);
	}
}

void Interfejs::zapisz_gre() {
	fstream plik;
	plik.open(NAZWA_PLIKU_ZAPISANEJ_GRY, ios::out | ios::trunc);

	if (plik.good()) {
		Gracz *gracz;
		Gracz *gracze[2] = { gra->gracz_1, gra->gracz_2 };
		Plansza *plansza;
		Pole *pole;
		Statek *statek;

		plik << gra->czy_tura_pierwszego_gracza << endl;

		for (int ii = 0; ii < 2; ii++) {
			gracz = gracze[ii];
			plik << gracz->czy_gracz_komputerowy << endl;

			if (gracz->czy_gracz_komputerowy) {
				plik << ((GraczKomputer *)gracz)->czy_jest_statek_do_zatopienia << endl;
				plik << ((GraczKomputer *)gracz)->czy_jest_znany_zwrot << endl;
				plik << ((GraczKomputer *)gracz)->kierunek_ostrzalu << endl;
				plik << ((GraczKomputer *)gracz)->zwrot_ostrzalu << endl;
			}

			plik << gracz->nazwa << endl;
			plik << gracz->liczba_strzalow_trafionych << endl;
			plik << gracz->liczba_strzalow << endl;


			plansza = gracz->plansza;
			plik << plansza->wysokosc << endl;
			plik << plansza->szerokosc << endl;

			for (int i = 0; i < plansza->wysokosc; i++) {
				for (int j = 0; j < plansza->szerokosc; j++) {
					pole = plansza->macierz_pol[i][j];

					plik << pole->czy_nalezy_do_statku << endl;
					plik << pole->czy_odkryte << endl;
				}
			}

			plik << gracz->statki.size() << endl;

			for (int i = 0; i < gracz->statki.size(); i++) {
				statek = gracz->statki[i];

				plik << statek->dlugosc << endl;
				plik << statek->czy_zatopiony << endl;
				plik << statek->x_index << endl;
				plik << statek->y_index << endl;
				plik << statek->orientacja << endl;
			}
		}
		for (int ii = 0; ii < 2; ii++) {
			gracz = gracze[ii];
			if (gracz->czy_gracz_komputerowy && ((GraczKomputer *)gracz)->czy_jest_statek_do_zatopienia) {
				plik << ((GraczKomputer *)gracz)->pierwsze_trafione_pole->x_pozycja << endl;
				plik << ((GraczKomputer *)gracz)->pierwsze_trafione_pole->y_pozycja << endl;
				plik << ((GraczKomputer *)gracz)->ostatnio_trafione_pole->x_pozycja << endl;
				plik << ((GraczKomputer *)gracz)->ostatnio_trafione_pole->y_pozycja << endl;
			}
			else {
				plik << 0 << endl;
				plik << 0 << endl;
				plik << 0 << endl;
				plik << 0 << endl;
			}
		}

		printf(POWIADOM_O_ZAPISANIU_PLIKU);

		plik.close();
	}
	else {
		printf(POWIADOM_O_BLEDZIE_ZAPISANIU_PLIKU);
	}
}