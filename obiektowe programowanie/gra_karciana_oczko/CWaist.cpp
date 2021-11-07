#define _CRT_SECURE_NO_WARNINGS
#include "CWaist.h"
#include <string>
using namespace std;


CWaist::CWaist()
{
	int i = 0;
	char pik[6] = "pik";
	char kier[6] = "kier";
	char karo[6] = "karo";
	char trefl[6] = "trefl";
	for (i = 0; i < 13; i++) waist[0 + i] = new CCard(pik, i + 2);
	for (i = 0; i < 13; i++) waist[13 + i] = new CCard(kier, i + 2);
	for (i = 0; i < 13; i++) waist[26 + i] = new CCard(karo, i + 2);
	for (i = 0; i < 13; i++) waist[39 + i] = new CCard(trefl, i + 2);
	iterator = 0;
}


CWaist::~CWaist()
{
}

void CWaist::print_waist()
{
	for (int i = 0; i < 52; i++) waist[i]->display_card();
}

void CWaist::shuffle()
{
	CCard* card_temp;
	int i, j;

	srand(time(nullptr));

	for (i = 0; i < 52; i++)
	{
		card_temp = waist[i];
		j = rand() % 52;
		if (j != i)
		{
			waist[i] = waist[j];
			waist[j] = card_temp;
		}
	}
}

int CWaist::get_iterator() //moze inline???
{
	int iterator_temp;
	iterator_temp = iterator;
	return iterator_temp;
}

CCard* CWaist::give_card()
{
	CCard *next_card = NULL;
	next_card = waist[iterator];
	iterator++;
	return next_card;
}