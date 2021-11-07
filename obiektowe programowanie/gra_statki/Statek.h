#include <vector>
#include "Pole.h"
#include "Plansza.h"

static const int ORIENTACJA_POZIOMA = 0;
static const int ORIENTACJA_PIONOWA = 1;

class Statek {
private:
	int x_index;
	int y_index;
	int orientacja;
	int dlugosc;
	vector<Pole*> pola;
	vector<Pole*> pola_sasiednie;
	bool czy_zatopiony;				// przechowuje czy tak czy nie

	bool sprawdz_czy_zatopiony();	// tu si� wykonuje, zmienia flag� czy_zatopiony na true jak tak

public:
	Statek();
	Statek(int dlugosc);

	bool czy_mozna_utworzyc_statek(Plansza *plansza, int orientacja, int x_index, int y_index);
	void utworz_statek(Plansza *plansza, int orientacja, int x_index, int y_index);
	bool czy_trafiony_zatopiony();
	void odkryj_sasiednie_pola();

	void operator--(int);			// odkrywanie s�siednich p�l

	friend class Gracz;
	friend class Interfejs;
};
