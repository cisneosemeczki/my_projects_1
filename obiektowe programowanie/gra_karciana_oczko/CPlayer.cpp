#include "CPlayer.h"


CPlayer::CPlayer(CWaist* waist_temp)
{
	waist = waist_temp;
}

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::choose_card()
{
	for (int i = 0; i < 13; i++)
	{
		if (card_tab[i] == NULL)
		{
			card_tab[i] = waist->give_card();
			break;
		}
	}
}

bool CPlayer::play()
{
	bool game_is_active = true;
	int choice = 0;

	while (1)
	{
		int a;
	poczatek1:
		a = 0;
		cout << endl;
		cout << "HMMHMHM KOLEJNA KARTE?" << endl;
		cout << "A OCZYWISCIE [1]" << endl;
		cout << "MOZE JEDNAK NIE [2]" << endl;

		cin >> choice;
		//if (choice == 1 || choice == 2)
			/*{
			cin.clear();
			cin.ignore();
			break;
			}*/
		while (cin.fail() == 1)
		{
			a = 1;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		if (a == 1)
		{
			cout << "NO CO TY TAM SYNKU WPISALES" << endl;
			goto poczatek1;
		}
		if (choice < 1 || choice > 2)
		{
			cout << "NO CO TY TAM SYNKU WPISALES" << endl;
			cin.clear();
			cin.ignore();
		}

		if (choice == 1)
		{
			game_is_active = true;
			choose_card();
			display();

			if (get_card_value() >= 21)
				game_is_active = false;
		}
		else if (choice == 2)
			game_is_active = false;

		return game_is_active;
	}
}

int CPlayer::get_card_value()
{
	int value = 0;

	for (int i = 0; i < 10; i++)
	{
		if (card_tab[i] != NULL)
			value = value + card_tab[i]->get_value();
	}

	return value;
}

void CPlayer::display()
{
	cout << endl;
	cout << "OTO TWOJE KARTY:" << endl;
	cout << "kolor - figura - wartosc" << endl;
	for (int i = 0; i < 10; i++)
	{
		if (card_tab[i] != NULL)
			card_tab[i]->display_card();
	}
	cout << "TWOJA ILOSC PKT: " << get_card_value() << endl;
}
