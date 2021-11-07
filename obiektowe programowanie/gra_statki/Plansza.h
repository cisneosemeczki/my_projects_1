#include <vector>
#include "Pole.h"

using namespace std;

class Plansza {
private:
	int szerokosc;
	int wysokosc;
	vector<vector<Pole*>> macierz_pol;

public:
	Plansza();
	Plansza(int szerokosc, int wysokosc);
	~Plansza();

	void init_macierz();

	friend class Statek;
	friend class Interfejs;
	friend class Gracz;
	friend class GraczKomputer;
};
