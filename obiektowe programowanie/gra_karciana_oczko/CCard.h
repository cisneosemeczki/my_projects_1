#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
using namespace std;

class CCard
{
public:
	CCard(char* colour_temp, int symbol_temp);
	~CCard();
private:
	char colour[6]; //1-pik 2-kier 3-karo 4-trefl
	int symbol; //2,3,4,5,6,7,8,9,10 11-bubek 12-damka 13-krolik 14-as
	int value;
public:
	int get_value();
	void display_card();
};

