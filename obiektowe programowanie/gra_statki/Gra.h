#include <string>
#include "Gracz.h"

using namespace std;

class Gra {
private:
	Gracz *gracz_1;
	Gracz *gracz_2;
	bool czy_tura_pierwszego_gracza;

public:
	Gra();
	Gra(string nazwa_gracza);
	Gra(string nazwa_gracza_1, string nazwa_gracza_2);
	~Gra();

	bool czy_koniec_gry();
	Gracz *wez_wygranego();

	friend class Interfejs;
};
