#include "Cklient.h"
#include "Cobsluga.h"
using namespace std;

int main()
{
	Cklient klient;
	Cobsluga pracownik(&klient);

	pracownik.obsluga_klienta();

	system("PAUSE");
	return 0;
}
