#pragma once
#include "Cklient.h"
#include <iostream>
#include <string>

class Cobsluga
{

public:
	Cklient* klient;
	Cobsluga(Cklient*);
	~Cobsluga();
	void obsluga_klienta();
};

