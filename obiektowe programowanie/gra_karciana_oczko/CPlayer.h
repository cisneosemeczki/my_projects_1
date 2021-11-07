#pragma once
#include "CWaist.h"
#include <iostream>
using namespace std;

class CPlayer
{
public:
	CPlayer(CWaist *waist_temp);
	CPlayer();
	~CPlayer();
protected:
	CCard * card_tab[10]; //tablica wskaznikow kart
	CWaist* waist;
	int points_amount;
public:
	virtual bool play();
	virtual void display();
	void choose_card();
	int get_card_value();
};

