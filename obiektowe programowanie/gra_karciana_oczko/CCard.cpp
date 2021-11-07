#define _CRT_SECURE_NO_WARNINGS
#include "CCard.h"
#include <string>
using namespace std;

CCard::CCard(char* colour_temp, int symbol_temp)
{
	strcpy(colour, colour_temp);
	symbol = symbol_temp;

	if (symbol >= 2 && symbol <= 10) value = symbol;
	else if (symbol == 11) value = 2;
	else if (symbol == 12) value = 3;
	else if (symbol == 13) value = 4;
	else if (symbol == 14) value = 11;
}


CCard::~CCard()
{
}

int CCard::get_value()   //mozna by uzyc inline
{
	int value_temp;
	value_temp = value;
	return value_temp;
}

void CCard::display_card()
{
	if (symbol >= 2 && symbol <= 10) cout << "Karta: " << colour << ", " << value << endl;
	else if (symbol == 11) cout << "Karta: " << colour << " J, " << value << endl;
	else if (symbol == 12) cout << "Karta: " << colour << " Q, " << value << endl;
	else if (symbol == 13) cout << "Karta: " << colour << " K, " << value << endl;
	else if (symbol == 14) cout << "Karta: " << colour << " A, " << value << endl;
}

