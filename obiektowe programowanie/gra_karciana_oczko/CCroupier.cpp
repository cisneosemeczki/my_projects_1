#include "CCroupier.h"

CCroupier::CCroupier(CWaist *waist_temp)
{
	waist = waist_temp;
}

CCroupier::~CCroupier()
{
}

bool CCroupier::play()
{
	bool game_is_active = true;

	if (get_card_value() < 17) // dla krupiera prog 17 dobieran
	{
		choose_card();
		game_is_active = true;
	}
	else game_is_active = false;

	return game_is_active;
}

void CCroupier::display()
{
	cout << endl;
	cout << "OTO KRUPIERA KARTY:" << endl;
	cout << "kolor - figura - wartosc" << endl;
	for (int i = 0; i < 10; i++)
	{
		if (card_tab[i] != NULL)
			card_tab[i]->display_card();
	}
	cout << "KRUPIERA ILOSC PKT: " << get_card_value() << endl;
}

void CCroupier::display_one_card()
{
	cout << endl;
	cout << "OTO KRUPIERA KARTA:" << endl;
	cout << "kolor - figura - wartosc" << endl;

	if (card_tab[0] != NULL)
		card_tab[0]->display_card();
}