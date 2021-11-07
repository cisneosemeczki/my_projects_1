class Pole {
private:
	int x_pozycja;
	int y_pozycja;
	bool czy_nalezy_do_statku;
	bool czy_odkryte;

public:
	Pole();
	Pole(int x_pozycja, int y_pozycja);

	friend class Statek;
	friend class Interfejs;
	friend class GraczKomputer;
};
