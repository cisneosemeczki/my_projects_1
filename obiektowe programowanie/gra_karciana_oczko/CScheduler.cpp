#include "CScheduler.h"

CScheduler::CScheduler(CWaist* talia_temp, CPlayer* gracz_temp, CCroupier* krupier_temp)
{
	talia = talia_temp;
	gracz = gracz_temp;
	krupier = krupier_temp;

	talia->shuffle();

	for (int i = 0; i < 2; i++)
	{
		gracz->choose_card();
		krupier->choose_card();
	}
}

CScheduler::~CScheduler()
{
}

void CScheduler::game()
{
	bool player_option;

	while (1)
	{
		cout << "WITAM W GRZE OCZKO MOJA FOCZKO" << endl;
		cout << "STARTUJEMY!" << endl;
		krupier->display_one_card();
		gracz->display();

		while (1)
		{
			if (krupier->get_card_value() >= 21)
			{
				player_option = false;
				break;
			}
			else
			{
				player_option = gracz->play();
				if (player_option == false)
				{
					if (gracz->get_card_value() == 21)
					{
						krupier->play();
						break;
					}
					else break;
				}
				else krupier->play();
			}
		}

		end_game();

		if (player_option == false) break;
	}
}

void CScheduler::end_game()
{
	cout << "GRA DOBIEGLA KONCA!" << endl;

	if (gracz->get_card_value() <= 21 && krupier->get_card_value() <= 21)
	{
		if (gracz->get_card_value() > krupier->get_card_value())
		{
			gracz->display();
			krupier->display();
			cout << endl << "DALES CZADU!" << endl;
		}
		else if (gracz->get_card_value() < krupier->get_card_value())
		{
			gracz->display();
			krupier->display();
			cout << endl << "DALES CIALA!" << endl;
		}
		else if (gracz->get_card_value() == krupier->get_card_value())
		{
			gracz->display();
			krupier->display();
			cout << endl << "WYROWNANA WALKA!" << endl;
		}
	}
	else if (gracz->get_card_value() > 21 && krupier->get_card_value() > 21)
	{
		cout << endl << "PRZELECIELISCIE 21 PKT!" << endl;
		if (gracz->get_card_value() > krupier->get_card_value())
		{
			gracz->display();
			krupier->display();
			cout << endl << "DALES CIALA!" << endl;
		}
		else if (gracz->get_card_value() < krupier->get_card_value())
		{
			gracz->display();
			krupier->display();
			cout << endl << "DALES CZADU!" << endl;
		}
		else if (gracz->get_card_value() == krupier->get_card_value())
		{
			gracz->display();
			krupier->display();
			cout << endl << "WYROWNANA WALKA!" << endl;
		}
	}
	else
	{
		if (gracz->get_card_value() > 21)
		{
			gracz->display();
			krupier->display();
			cout << endl << "DALES CIALA!" << endl << "PRZELECIALES 21 PKT!" << endl;
		}
		else if (krupier->get_card_value() > 21)
		{
			gracz->display();
			krupier->display();
			cout << endl << "DALES CZADU!" << endl << "KRUPIER PRZELECIAL 21 PKT!" << endl;
		}
	}



}