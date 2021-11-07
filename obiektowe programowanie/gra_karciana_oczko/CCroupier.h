#pragma once
#include "CPlayer.h"
#include <iostream>
using namespace std;

class CCroupier :
	public CPlayer
{
public:
	CCroupier(CWaist* waist_temp);
	~CCroupier();
	bool play();
	void display_one_card();
	void display();
};

