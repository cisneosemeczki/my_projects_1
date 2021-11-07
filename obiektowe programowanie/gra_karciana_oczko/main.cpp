#include <iostream>
#include "CScheduler.h"

int main()
{
	CWaist talia;
	CPlayer gracz(&talia);
	CCroupier krupier(&talia);
	CScheduler zarzadca(&talia, &gracz, &krupier);


	zarzadca.game();


	system("PAUSE");
	return 0;
}