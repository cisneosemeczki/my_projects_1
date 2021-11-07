#include "Interfejs.h"
#include <time.h>


int main() {
	srand(time(NULL));

	Interfejs interfejs;
	interfejs = Interfejs();
	interfejs.start();

	return 0;
}