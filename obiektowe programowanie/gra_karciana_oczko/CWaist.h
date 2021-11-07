#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "CCard.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


class CWaist
{
public:
	CWaist();
	~CWaist();
private:
	CCard * waist[52];
	int iterator; //najpierw 0, rosnie o 1 i wskazuje karte
public:
	void shuffle();
	void print_waist();
	int get_iterator();
	CCard* give_card();
};

