#include "Pole.h"


Pole::Pole() {

}

Pole::Pole(int x_pozycja, int y_pozycja) {
	this->x_pozycja = x_pozycja;
	this->y_pozycja = y_pozycja;

	this->czy_nalezy_do_statku = false;
	this->czy_odkryte = false;
}
