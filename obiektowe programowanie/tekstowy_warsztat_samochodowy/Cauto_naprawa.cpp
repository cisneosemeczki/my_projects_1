#include "Cauto_naprawa.h"
using namespace std;


Cauto_naprawa::Cauto_naprawa()
{
	for (int j = 0; j < 10; j++) stan_naprawy[j] = 0;
}


Cauto_naprawa::~Cauto_naprawa()
{
}


int Cauto_naprawa::daj_koszt_naprawy()
{
	int koszt_temp = koszt_naprawy.daj_koszt_naprawy();
	return koszt_temp;
}

int Cauto_naprawa::daj_stan_naprawy(int i)
{
	return stan_naprawy[i];
}

void Cauto_naprawa::wyswietl_koszt_naprawy()
{
	int koszt_temp = koszt_naprawy.daj_koszt_naprawy();
	cout << "\nMechanik: Laczny koszt naprawy bedzie wynosil " << koszt_temp << " zl!"; hmm<void>();
	cout << "Zadowolony?"; hmm<void>();
	if (koszt_temp < 300)
	{
		cout << "Klient: Hehe, no pewnie!"; hmm<void>();
	}
	else
	{
		cout << "Klient: Niby tak, ale drogo wyszlo :/ Ale bylem tego swiadomy, ze bedzie to tyle kosztowac."; hmm<void>();
	}
}

void Cauto_naprawa::wypisanie_usterki()
{
	for (int i = 0; i < 1; i++)
	{

		if (filtr_oleju == 0)
		{
			cout << "Klient: A Panie mechaniku, filtr oleju bylby do wymiany."; hmm<void>();
			cout << "Mechanik: No niezle, niezle, zrobi sie to."; hmm<void>();
			cout << "Cos jeszcze?"; hmm<void>();
		}
		if (rozrusznik == 0)
		{
			cout << "Klient: Sa problemy z odpalaniem samochodu mojego kochanego."; hmm<void>();
			cout << "Mechanik: Hmmm, moze cos sie stalo niedobrego z rozrusznikiem."; hmm<void>();
			cout << "Jeszcze dokladnie nie wiem ile bedzie kosztowac naprawa, bo to zalezy czy bedzie musial byc nowy rozrusznik."; hmm<void>();
			cout << "Jeszcze jest jakas usterka?"; hmm<void>();
		}
		if (wahacz == 0)
		{
			cout << "Klient: Hmmm, bo troche driftowalem sobie po parkingu przy biedronce zeszlej nocy."; hmm<void>();
			cout << "I kurcze nadlamal mi sie lewy wahacz w przednim kole :/"; hmm<void>();
			cout << "Mechanik: No ladnie ladnie. Ale nie ma problemu, wymienimy na nowy."; hmm<void>();
			cout << "Jeszcze cos niesprawne?"; hmm<void>();
		}
		if (klocki_hamulcowe == 0)
		{
			cout << "Klient: Przetarly sie klocki hamulcowe, bo kontrolka wskazuje."; hmm<void>();
			cout << "Mechanik: Jasne, wymiana nie bedzie stanowic problemu."; hmm<void>();
			cout << "Jeszcze cos?"; hmm<void>();
		}
	}
	cout << "Klient: Nie, to wszystko!"; hmm<void>();
}

void Cauto_naprawa::naprawa()
{
	hmm<void>(); cout << "NAPRAWIANIE!"; hmm<void>();
	if (filtr_oleju == 0)
	{
		float ilosc_litrow_oleju;
		cout << "Trzeba sie zabrac za wymiane filtru!"; hmm<void>();
		cout << "Filtr oleju zostal wymieniony!"; hmm<void>();
		cout << "Nalezy teraz nalac odpowiednia ilosc oleju, powinna ona wynosic ok. 2,3 raza wiecej niz pojemnosc silnika samochodu."; hmm<void>();
		cout << "Ile zatem nalejesz oleju drogi mechaniku? Hmhmh: ";
		ilosc_litrow_oleju = daj_wartosc<float>(2.1*pojemnosc_silnika, 2.5*pojemnosc_silnika); hmm2<void>();
		cout << "No no, bo prawie przelales!"; hmm<void>();

		koszt_naprawy += 40;
		stan_naprawy[0] = 1;
	}
	if (rozrusznik == 0)
	{
		int opcja;
		cout << "Po wstepnych ogledzinach stwierdzasz, ze chyba trzeba wstawic nowy rozrusznik."; hmm<void>();
		cout << "Ale beda wysokie koszty dla klienta i moze byc niezadowolony. Co robisz?"; hmm<void>();
		cout << "Nowy rozrusznik! (1) / Wymieniam zuzyte czesci w rozruszniku ;) (2)"; hmm<void>();
		cout << "Hmmm? ";
		opcja = daj_wartosc<int>(1, 2); hmm2<void>();
		if (opcja == 1)
		{
			cout << "Kurde, ale bylo z tym pracy. Hehe, ale to bedzie kosztowac."; hmm<void>();
			cout << "W koncu tez sam rozrusznik sporo kosztuje."; hmm<void>();
			cout << "Jak on zobaczy ta fakturke to :D"; hmm<void>();
			koszt_naprawy += 550;
			stan_naprawy[1] = 1;
		}
		else
		{
			cout << "No, wymienilem wlacznik elektromagnetyczny i kilka lozysk."; hmm<void>();
			cout << "Na jakis czas powinno starczyc!"; hmm<void>();
			cout << "Kliencik drogi bedzie zadowolony ze tak po taniosci!"; hmm<void>();
			koszt_naprawy += 180;
			stan_naprawy[2] = 1;
		}
	}
	if (wahacz == 0)
	{	
		int opcja2;
		cout << "Pojazd zostal podniesiony na czterokolumnowym podnosniku!"; hmm<void>();
		cout << "Wymnieniony zostal wahacz i nalezy jeszcze dokrecic sruby."; hmm<void>();
		cout << "Pomagier: Szefie!!! Opuscic juz auto?"; hmm<void>(); 
		cout << "W zadnym wypadku moj kwiatku! (7) / Smialo opuszczaj! (8)"; hmm<void>();
		cout << "A wiec? Hmmm: ";
		opcja2 = daj_wartosc<int>(7, 8); hmm2<void>();
		if (opcja2 == 7)
		{
			cout << "Dokrecasz sruby, a nastepnie dzielny chlopak opuszcza auto."; hmm<void>();
			cout << "Nagle pekaja gumy na tulei metalowo-gumowej!"; hmm<void>();
			cout << "Jasny gwint, co ja narobilem, powinienem dokrecic te sruby dopiero jak auto bedzie opuszczone, zeby nie powstaly zadne naprezenia w tulejach!"; hmm<void>(); 
			cout << "Teraz musze na wlasny koszt wymienic te tuleje :/"; hmm<void>();
			koszt_naprawy += 20;
			stan_naprawy[3] = 1;
		}
		else
		{
			cout << "Po opuszczeniu samochodu dokrecasz sruby."; hmm<void>();
			cout << "Oj teraz autko bedzie smigac jak nowe!"; hmm<void>();
			koszt_naprawy += 120;
			stan_naprawy[4] = 1;
		}
	}
	if (klocki_hamulcowe == 0)
	{
		int nacisniecia;
		cout << "Podnosimy samochod za pomoca podnosnika, zeby mozna bylo zdjac kola."; hmm<void>();
		cout << "Sruby nie chca puscic, uzywamy uniwersalnego plynu penetracyjnego WD-40!"; hmm<void>();
		cout << "Zdejmujemy zacisk i teraz nalezy wcisnac tloczek znajdujacy sie w nim."; hmm<void>();
		cout << "Wcisnij dowolny przycisk, zeby wcisnac tloczek!"; hmm<void>();
		nacisniecia = rand() % 3;
		if (nacisniecia == 0)
		{
			system("pause"); hmm2<void>();
			cout << "Ty dzisiaj sniadania nie jadles? Jak Ty to wciskasz?"; hmm<void>();
			system("pause"); hmm2<void>();
		}
		if (nacisniecia == 1)
		{
			system("pause"); hmm2<void>();
			cout << "NO DAWAJ TLOCZKU!"; hmm<void>();
			system("pause"); hmm2<void>();
			cout << "JESZCZE TROSZECZKE!"; hmm<void>();
			system("pause"); hmm2<void>();
		}
		if (nacisniecia == 2)
		{
			system("pause"); hmm2<void>();
			cout << "Jasny gwint, ale to ciezko idzie!"; hmm<void>();
			system("pause"); hmm2<void>();
			cout << "Nie bede sie denerwowal, predzej czy pozniej wcisne!"; hmm<void>();
			system("pause"); hmm2<void>();
			cout << "Ooo, jeszcze milimetry!"; hmm<void>();
			system("pause"); hmm2<void>();
		}
		cout << "Uff, udalo sie wcisnac ten tloczek, ale sie spocilem przy tym."; hmm<void>();
		cout << "Zacisk hamulcowy wymieniony, kolo przykrecone!"; hmm<void>();
		koszt_naprawy += 100;
		stan_naprawy[5] = 1;
	}
	hmm<void>(); cout << "KONIEC NAPRAWIANIA!"; hmm<void>();
}