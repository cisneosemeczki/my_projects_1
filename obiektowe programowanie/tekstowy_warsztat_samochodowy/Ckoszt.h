#pragma once

class Ckoszt
{
public:
	Ckoszt();
	~Ckoszt();

private:
	int koszt_naprawy;

public:
	void ustaw_koszt_naprawy(int);
	inline const int daj_koszt_naprawy() { return koszt_naprawy; };
	Ckoszt &operator+=(int koszt_temp);
};

