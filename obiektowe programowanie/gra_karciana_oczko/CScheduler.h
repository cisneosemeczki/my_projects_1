#pragma once
#include "CWaist.h"
#include "CPlayer.h"
#include "CCroupier.h"

class CScheduler
{
public:
	CWaist * talia;
	CPlayer *gracz;
	CCroupier *krupier;
	CScheduler(CWaist*, CPlayer*, CCroupier*);
	~CScheduler();
	void game();
	void end_game();
};

