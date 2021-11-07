#include "Ckoszt.h"
#include <iostream>

Ckoszt::Ckoszt()
{
	koszt_naprawy = 0;
}


Ckoszt::~Ckoszt()
{
}

void Ckoszt::ustaw_koszt_naprawy(int koszt)
{
	koszt_naprawy = koszt;
}

Ckoszt &Ckoszt::operator+=(int koszt_temp)
{
	ustaw_koszt_naprawy(koszt_naprawy + koszt_temp);
	return (*this);
}