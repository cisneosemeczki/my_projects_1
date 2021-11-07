#include "Cauto.h"
using namespace std;

Cauto::Cauto()
{
	bool rozrusznik = 1;
	bool wahacz = 1;
	bool skrzynia_biegow = 1;
	bool klocki_hamulcowe = 1;
	bool filtr_oleju = 1;

	char marka_temp[300], model_temp[300];

	cout << "Kliencie podaj parametry swojego auta!" << endl;
	cout << "Marka: ";
	cin >> marka_temp;
	strcpy(marka, marka_temp);
	cout << "Model: ";
	cin >> model_temp;
	strcpy(model, model_temp);

	cout << "Podaj rok produkcji: ";
	rok_produkcji = daj_wartosc<int>(1950, 2017);

	cout << "Podaj pojemnosc silnika: ";
	pojemnosc_silnika = daj_wartosc<float>(1.0, 8.0);
}


Cauto::~Cauto()
{
}

void Cauto::losowanie_usterki()
{
	srand(time(NULL));
	int usterki[2];

poczatek1:
	for (int i = 0; i < 2; i++)
	{
		usterki[i] = rand() % 4;
	}
	if (usterki[0] == usterki[1]) goto poczatek1;

	for (int i = 0; i < 2; i++)
	{
		if (usterki[i] == 0) filtr_oleju = 0;
		else if (usterki[i] == 1) klocki_hamulcowe = 0;
		else if (usterki[i] == 2) wahacz = 0;
		else if (usterki[i] == 3) rozrusznik = 0;
	}
}

 void Cauto::wypisanie_usterki()
{
	 cout << "Klient: ";
	 if (filtr_oleju == 0) cout << "Panie mechaniku filtr oleju bylby do wymiany.\n";
	 if (klocki_hamulcowe == 0) cout << "Klocki hamulcowe trzeba wymienic.\n";
	 if (wahacz == 0) cout << "Wahacz zniszczony kiedy driftowalem.\n";
	 if (rozrusznik == 0) cout << "Samochod ciezko odpala, mysle, ze rozrusznik jest winny\n";
	 cout << "Mechanik: Jasne, wszystko sie naprawi!\n";
}
