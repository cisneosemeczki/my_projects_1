#include "limit_switch.h"


int stan1 = 0;
int podczas_kalibracji = 0;
int kalibracja_wykonana = 0;

int krancowka_X_wczesniej = 0;
int krancowka_Y_wczesniej = 0;
int krancowka_Z_wczesniej = 0;

int X_gora = 0;
int Y_gora = 0;
int Z_gora = 0;

int dojazd_do_1_krancowki = 0;
int dojazd_do_2_krancowki = 0;
int dojazd_do_3_krancowki = 0;

int krancowka_X = 0;
int krancowka_Y = 0;
int krancowka_Z = 0;

int krancowka_aktywna = 1;



void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if ((GPIO_Pin == X_MIN_Pin || X_MAX_Pin || Y_MIN_Pin ||
			Y_MAX_Pin || Z_MIN_Pin || Z_MAX_Pin) && podczas_kalibracji == 0)
	{
		//HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		Stepper_EndStopHandler(0);
		Stepper_EndStopHandler(1);
		Stepper_EndStopHandler(2);
	}


	if ((GPIO_Pin == USER_BUTTON_Pin) && podczas_kalibracji == 0)
	{
		stan1 = 1;
	}

	//tutaj do kalibracji od krancowek
	if ((GPIO_Pin == X_MAX_Pin || Y_MAX_Pin || Z_MAX_Pin) && podczas_kalibracji == 1 && krancowka_aktywna == 1)
	{
		if (dojazd_do_1_krancowki == 0 && dojazd_do_2_krancowki == 0 && dojazd_do_3_krancowki == 0)
		{
			if (GPIO_Pin == X_MAX_Pin)
					{
						krancowka_X = 1;
						dojazd_do_1_krancowki = 1;
						krancowka_aktywna = 0;
						Stepper_EndStopHandler(0);
					}
			else if (GPIO_Pin == Y_MAX_Pin)
					{
						krancowka_Y = 1;
						dojazd_do_1_krancowki = 1;
						krancowka_aktywna = 0;
						Stepper_EndStopHandler(1);
					}
			else if (GPIO_Pin == Z_MAX_Pin)
					{
						krancowka_Z = 1;
						dojazd_do_1_krancowki = 1;
						krancowka_aktywna = 0;
						Stepper_EndStopHandler(2);
					}
		}
		if (dojazd_do_1_krancowki == 1 && dojazd_do_2_krancowki == 0 && dojazd_do_3_krancowki == 0)
		{
			if ((GPIO_Pin == X_MAX_Pin) && krancowka_X == 0)
					{
						krancowka_X = 1;
						dojazd_do_2_krancowki = 1;
						krancowka_aktywna = 0;
						Stepper_EndStopHandler(0);
					}
			else if ((GPIO_Pin == Y_MAX_Pin) && krancowka_Y == 0)
					{
						krancowka_Y = 1;
						dojazd_do_2_krancowki = 1;
						krancowka_aktywna = 0;
						Stepper_EndStopHandler(1);
					}
			else if ((GPIO_Pin == Z_MAX_Pin) && krancowka_Z == 0)
					{
						krancowka_Z = 1;
						dojazd_do_2_krancowki = 1;
						krancowka_aktywna = 0;
						Stepper_EndStopHandler(2);
					}
		}
		if (dojazd_do_1_krancowki == 1 && dojazd_do_2_krancowki == 1 && dojazd_do_3_krancowki == 0)
		{
			if ((GPIO_Pin == X_MAX_Pin) && krancowka_X == 0)
					{
						krancowka_X = 1;
						dojazd_do_3_krancowki = 1;
						krancowka_aktywna = 0;
						Stepper_EndStopHandler(0);
					}
			else if ((GPIO_Pin == Y_MAX_Pin) && krancowka_Y == 0)
					{
						krancowka_Y = 1;
						dojazd_do_3_krancowki = 1;
						krancowka_aktywna = 0;
						Stepper_EndStopHandler(1);
					}
			else if ((GPIO_Pin == Z_MAX_Pin) && krancowka_Z == 0)
					{
						krancowka_Z = 1;
						dojazd_do_3_krancowki = 1;
						krancowka_aktywna = 0;
						Stepper_EndStopHandler(2);
					}
		}
	}
}



void kalibracja_krancowek(void)
{
	podczas_kalibracji = 1;

	while (dojazd_do_1_krancowki != 1)
	{
		Stepper_Enable(&lista_silnikow[0]);
		Stepper_moveIncDist(&lista_silnikow[0], 20, 15);   //tutaj do ustalenia jeszcze jak daleko ma jechac
		while(lista_silnikow[0].moving_f == 1) {}

		if (dojazd_do_1_krancowki == 1) break;

		Stepper_Enable(&lista_silnikow[1]);
		Stepper_moveIncDist(&lista_silnikow[1], 20, 15);   //tutaj do ustalenia jeszcze jak daleko ma jechac
		while(lista_silnikow[1].moving_f == 1) {}

		if (dojazd_do_1_krancowki == 1) break;

		Stepper_Enable(&lista_silnikow[2]);
		Stepper_moveIncDist(&lista_silnikow[2], 20, 15);   //tutaj do ustalenia jeszcze jak daleko ma jechac
		while(lista_silnikow[2].moving_f == 1) {}
	}

	//UWAGA TU ZAKLADAM ZE STEP 0 to X MAX, STEP 1 to Y MAX a STEP 2 to Z MAX
	//TO TRZEBA OGARNAC JESZCZE

	if (dojazd_do_1_krancowki == 1 && krancowka_X == 1 && krancowka_Y == 0 && krancowka_Z == 0)
	{
		Stepper_Enable(&lista_silnikow[0]);
		Stepper_moveIncDist(&lista_silnikow[0], -20, 10);
		while(lista_silnikow[0].moving_f == 1) {}
		X_gora = 0;
		krancowka_X_wczesniej = 1;
		krancowka_aktywna = 1;

		while (dojazd_do_2_krancowki != 1)
		{
			if (X_gora == 0) {
				Stepper_Enable(&lista_silnikow[0]);
				Stepper_moveIncDist(&lista_silnikow[0], 15, 10);
				while(lista_silnikow[0].moving_f == 1) {}
				X_gora = 1;
			} else {
				Stepper_Enable(&lista_silnikow[0]);
				Stepper_moveIncDist(&lista_silnikow[0], -15, 10);
				while(lista_silnikow[0].moving_f == 1) {}
				X_gora = 0;
			}

			if (dojazd_do_2_krancowki == 1) break;

			Stepper_Enable(&lista_silnikow[1]);
			Stepper_moveIncDist(&lista_silnikow[1], 20, 10);   //tutaj do ustalenia jeszcze jak daleko ma jechac
			while(lista_silnikow[1].moving_f == 1) {}

			if (dojazd_do_2_krancowki == 1) break;

			Stepper_Enable(&lista_silnikow[2]);
			Stepper_moveIncDist(&lista_silnikow[2], 20, 10);
			while(lista_silnikow[2].moving_f == 1) {}
		}
	}
	else if (dojazd_do_1_krancowki == 1 && krancowka_X == 0 && krancowka_Y == 1 && krancowka_Z == 0)
	{
		Stepper_Enable(&lista_silnikow[1]);
		Stepper_moveIncDist(&lista_silnikow[1], -20, 10);
		while(lista_silnikow[1].moving_f == 1) {}
		Y_gora = 0;
		krancowka_Y_wczesniej = 1;
		krancowka_aktywna = 1;

		while (dojazd_do_2_krancowki != 1)
		{
			if (Y_gora == 0) {
				Stepper_Enable(&lista_silnikow[1]);
				Stepper_moveIncDist(&lista_silnikow[1], 15, 10);
				while(lista_silnikow[1].moving_f == 1) {}
				Y_gora = 1;
			} else {
				Stepper_Enable(&lista_silnikow[1]);
				Stepper_moveIncDist(&lista_silnikow[1], -15, 10);
				while(lista_silnikow[1].moving_f == 1) {}
				Y_gora = 0;
			}

			if (dojazd_do_2_krancowki == 1) break;

			Stepper_Enable(&lista_silnikow[0]);
			Stepper_moveIncDist(&lista_silnikow[0], 20, 10);  //tutaj do ustalenia jeszcze jak daleko ma jechac
			while(lista_silnikow[0].moving_f == 1) {}

			if (dojazd_do_2_krancowki == 1) break;

			Stepper_Enable(&lista_silnikow[2]);
			Stepper_moveIncDist(&lista_silnikow[2], 20, 10);
			while(lista_silnikow[2].moving_f == 1) {}
		}
	}
	else if (dojazd_do_1_krancowki == 1 && krancowka_X == 0 && krancowka_Y == 0 && krancowka_Z == 1)
	{
		Stepper_Enable(&lista_silnikow[2]);
		Stepper_moveIncDist(&lista_silnikow[2], -20, 10);
		while(lista_silnikow[2].moving_f == 1) {}
		Z_gora = 0;
		krancowka_Z_wczesniej = 1;
		krancowka_aktywna = 1;

		while (dojazd_do_2_krancowki != 1)
		{
			if (Z_gora == 0) {
				Stepper_Enable(&lista_silnikow[2]);
				Stepper_moveIncDist(&lista_silnikow[2], 15, 10);
				while(lista_silnikow[2].moving_f == 1) {}
				Z_gora = 1;
			} else {
				Stepper_Enable(&lista_silnikow[2]);
				Stepper_moveIncDist(&lista_silnikow[2], -15, 10);
				while(lista_silnikow[2].moving_f == 1) {}
				Z_gora = 0;
			}

			if (dojazd_do_2_krancowki == 1) break;

			Stepper_Enable(&lista_silnikow[0]);
			Stepper_moveIncDist(&lista_silnikow[0], 20, 10); //tutaj do ustalenia jeszcze jak daleko ma jechac
			while(lista_silnikow[0].moving_f == 1) {}

			if (dojazd_do_2_krancowki == 1) break;

			Stepper_Enable(&lista_silnikow[1]);
			Stepper_moveIncDist(&lista_silnikow[1], 20, 10);
			while(lista_silnikow[1].moving_f == 1) {}
		}
	}


	if (dojazd_do_1_krancowki == 1 && dojazd_do_2_krancowki == 1
			&& krancowka_X == 1 && krancowka_Y == 1 && krancowka_Z == 0)
	{
		if (krancowka_Y_wczesniej == 1){
			Stepper_Enable(&lista_silnikow[0]);
			Stepper_moveIncDist(&lista_silnikow[0], -20, 10);
			while(lista_silnikow[0].moving_f == 1) {}
			X_gora = 0;
		} else if (krancowka_X_wczesniej == 1){
			Stepper_Enable(&lista_silnikow[1]);
			Stepper_moveIncDist(&lista_silnikow[1], -20, 10);
			while(lista_silnikow[1].moving_f == 1) {}
			Y_gora = 0;
		}
		krancowka_aktywna = 1;

		while (dojazd_do_3_krancowki != 1)
		{
			if (X_gora == 0) {
				Stepper_Enable(&lista_silnikow[0]);
				Stepper_moveIncDist(&lista_silnikow[0], 15, 10);
				while(lista_silnikow[0].moving_f == 1) {}
				X_gora = 1;
			} else {
				Stepper_Enable(&lista_silnikow[0]);
				Stepper_moveIncDist(&lista_silnikow[0], -15, 10);
				while(lista_silnikow[0].moving_f == 1) {}
				X_gora = 0;
			}

			if (dojazd_do_3_krancowki == 1) break;

			if (Y_gora == 0) {
				Stepper_Enable(&lista_silnikow[1]);
				Stepper_moveIncDist(&lista_silnikow[1], 15, 10);
				while(lista_silnikow[1].moving_f == 1) {}
				Y_gora = 1;
			} else {
				Stepper_Enable(&lista_silnikow[1]);
				Stepper_moveIncDist(&lista_silnikow[1], -15, 10);
				while(lista_silnikow[1].moving_f == 1) {}
				Y_gora = 0;
			}

			if (dojazd_do_3_krancowki == 1) break;

			Stepper_Enable(&lista_silnikow[2]);
			Stepper_moveIncDist(&lista_silnikow[2], 20, 10);  //tutaj do ustalenia jeszcze jak daleko ma jechac
			while(lista_silnikow[2].moving_f == 1) {}
		}
		Stepper_Enable(&lista_silnikow[2]);
		Stepper_moveIncDist(&lista_silnikow[2], -5, 10);   //tutaj do ustalenia jeszcze jak daleko ma jechac
		while(lista_silnikow[2].moving_f == 1) {}
		Z_gora = 1;
	}
	else if (dojazd_do_1_krancowki == 1 && dojazd_do_2_krancowki == 1
			&& krancowka_X == 1 && krancowka_Y == 0 && krancowka_Z == 1)
	{
		if (krancowka_Z_wczesniej == 1){
			Stepper_Enable(&lista_silnikow[0]);
			Stepper_moveIncDist(&lista_silnikow[0], -20, 10);
			while(lista_silnikow[0].moving_f == 1) {}
			X_gora = 0;
		} else if (krancowka_X_wczesniej == 1){
			Stepper_Enable(&lista_silnikow[2]);
			Stepper_moveIncDist(&lista_silnikow[2], -20, 10);
			while(lista_silnikow[2].moving_f == 1) {}
			Z_gora = 0;
		}
		krancowka_aktywna = 1;

		while (dojazd_do_3_krancowki != 1)
		{
			if (X_gora == 0) {
				Stepper_Enable(&lista_silnikow[0]);
				Stepper_moveIncDist(&lista_silnikow[0], 15, 10);
				while(lista_silnikow[0].moving_f == 1) {}
				X_gora = 1;
			} else {
				Stepper_Enable(&lista_silnikow[0]);
				Stepper_moveIncDist(&lista_silnikow[0], -15, 10);
				while(lista_silnikow[0].moving_f == 1) {}
				X_gora = 0;
			}

			if (dojazd_do_3_krancowki == 1) break;

			if (Z_gora == 0) {
				Stepper_Enable(&lista_silnikow[2]);
				Stepper_moveIncDist(&lista_silnikow[2], 15, 10);
				while(lista_silnikow[2].moving_f == 1) {}
				Z_gora = 1;
			} else {
				Stepper_Enable(&lista_silnikow[2]);
				Stepper_moveIncDist(&lista_silnikow[2], -15, 10);
				while(lista_silnikow[2].moving_f == 1) {}
				Z_gora = 0;
			}

			if (dojazd_do_3_krancowki == 1) break;

			Stepper_Enable(&lista_silnikow[1]);
			Stepper_moveIncDist(&lista_silnikow[1], 20, 10);   //tutaj do ustalenia jeszcze jak daleko ma jechac
			while(lista_silnikow[1].moving_f == 1) {}
		}

		Stepper_Enable(&lista_silnikow[1]);
		Stepper_moveIncDist(&lista_silnikow[1], -5, 10);   //tutaj do ustalenia jeszcze jak daleko ma jechac
		while(lista_silnikow[1].moving_f == 1) {}
		Y_gora = 1;
	}
	else if (dojazd_do_1_krancowki == 1 && dojazd_do_2_krancowki == 1
			&& krancowka_X == 0 && krancowka_Y == 1 && krancowka_Z == 1)
	{
		if (krancowka_Z_wczesniej == 1){
			Stepper_Enable(&lista_silnikow[1]);
			Stepper_moveIncDist(&lista_silnikow[1], -20, 10);
			while(lista_silnikow[1].moving_f == 1) {}
			Y_gora = 0;
		} else if (krancowka_Y_wczesniej == 1){
			Stepper_Enable(&lista_silnikow[2]);
			Stepper_moveIncDist(&lista_silnikow[2], -20, 10);
			while(lista_silnikow[2].moving_f == 1) {}
			Z_gora = 0;
		}
		krancowka_aktywna = 1;

		while (dojazd_do_3_krancowki != 1)
		{
			if (Y_gora == 0) {
				Stepper_Enable(&lista_silnikow[1]);
				Stepper_moveIncDist(&lista_silnikow[1], 15, 10);
				while(lista_silnikow[1].moving_f == 1) {}
				Y_gora = 1;
			} else {
				Stepper_Enable(&lista_silnikow[1]);
				Stepper_moveIncDist(&lista_silnikow[1], -15, 10);
				while(lista_silnikow[1].moving_f == 1) {}
				Y_gora = 0;
			}

			if (dojazd_do_3_krancowki == 1) break;

			if (Z_gora == 0) {
				Stepper_Enable(&lista_silnikow[2]);
				Stepper_moveIncDist(&lista_silnikow[2], 15, 10);
				while(lista_silnikow[2].moving_f == 1) {}
				Z_gora = 1;
			} else {
				Stepper_Enable(&lista_silnikow[2]);
				Stepper_moveIncDist(&lista_silnikow[2], -15, 10);
				while(lista_silnikow[2].moving_f == 1) {}
				Z_gora = 0;
			}

			if (dojazd_do_3_krancowki == 1) break;

			Stepper_Enable(&lista_silnikow[0]);
			Stepper_moveIncDist(&lista_silnikow[0], 20, 10);   //tutaj do ustalenia jeszcze jak daleko ma jechac
			while(lista_silnikow[0].moving_f == 1) {}
		}

		Stepper_Enable(&lista_silnikow[0]);
		Stepper_moveIncDist(&lista_silnikow[0], -5, 10);   //tutaj do ustalenia jeszcze jak daleko ma jechac
		while(lista_silnikow[0].moving_f == 1) {}
		X_gora = 1;
	}


	if (dojazd_do_1_krancowki == 1 && dojazd_do_2_krancowki == 1 && dojazd_do_3_krancowki == 1)
	{
		// poczatek ukladu wspolrzednych w wartosciach absolutnych:
		//  X prowadnica = -361.263702
		//  Y prowadnica = -415.196625
		//  Z prowadnica = -415.196625
		//
		//  wozek na prowadnicy moze sie poruszac od 0 do 245 mm
		//  nie wiadomo przy jakiej wspolrzednej absolutnej jest jakby nasza krancowka czyli punkt 0,
		//  powiedzmy ze zaloze sobie ze teraz punktem 0 jest punkt 0 po prostu,
		//  czyli silniki beda przed startem w polozeniu 0 - 5 + 3 = 2, po tym jak najpierw przejada na X, Y, Z _gora
		//  potem pojedziemy nimi do wspolrzednych 361, 415 i 415

		if (X_gora == 0)
		{
			Stepper_Enable(&lista_silnikow[0]);
			Stepper_moveIncDist(&lista_silnikow[0], 15, 10);
			while(lista_silnikow[0].moving_f == 1) {}
			X_gora = 1;
		}
		if (Y_gora == 0)
		{
			Stepper_Enable(&lista_silnikow[1]);
			Stepper_moveIncDist(&lista_silnikow[1], 15, 10);
			while(lista_silnikow[1].moving_f == 1) {}
			Y_gora = 1;
		}
		if (Z_gora == 0)
		{
			Stepper_Enable(&lista_silnikow[2]);
			Stepper_moveIncDist(&lista_silnikow[2], 15, 10);
			while(lista_silnikow[2].moving_f == 1) {}
			Z_gora = 1;
		}

		lista_silnikow[0].absPos = -255;
		lista_silnikow[1].absPos = -255;
		lista_silnikow[2].absPos = -255;

		Stepper_EnableAll();
		Stepper_moveIncDist(&lista_silnikow[0], -106, 15);
		Stepper_moveIncDist(&lista_silnikow[1], -115, 15);
		Stepper_moveIncDist(&lista_silnikow[2], -115, 15);

		while(lista_silnikow[0].moving_f == 1) {}
		while(lista_silnikow[1].moving_f == 1) {}
		while(lista_silnikow[2].moving_f == 1) {}

		lista_silnikow[0].absPos = -361.263702;
		lista_silnikow[1].absPos = -415.196625;
		lista_silnikow[2].absPos = -415.196625;
	}


	krancowka_X_wczesniej = 0;
	krancowka_Y_wczesniej = 0;
	krancowka_Z_wczesniej = 0;
	X_gora = 0;
	Y_gora = 0;
	Z_gora = 0;
	dojazd_do_1_krancowki = 0;
	dojazd_do_2_krancowki = 0;
	dojazd_do_3_krancowki = 0;
	krancowka_X = 0;
	krancowka_Y = 0;
	krancowka_Z = 0;

	podczas_kalibracji = 0;
	kalibracja_wykonana = 1;
}



