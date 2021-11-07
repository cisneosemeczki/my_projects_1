#include "interpolation.h"


//punkt_kartezjanski trajektoria_liniowa_przeskalowana[MAX_ROZDZIELCZOSC_INTERPOLACJI] = { 0 };
punkt_kartezjanski trajektoria_liniowa[MAX_ROZDZIELCZOSC_INTERPOLACJI] = { 0 };				// Wektor przechowujacy wspolrzedne wszystkich punktow trajektorji dla interpolacji liniowej
punkt_kartezjanski trajektoria_kolowa[MAX_ROZDZIELCZOSC_INTERPOLACJI] = { 0 };				// Wektor przechowujacy wspolrzedne wszystkich punktow trajektorji dla interpolacji kolowej
punkt_kartezjanski droga_przegubowa[MAX_ROZDZIELCZOSC_INTERPOLACJI] = { 0 };

void iloczyn_wektorowy(punkt_kartezjanski *pkt_wyj,
		punkt_kartezjanski *pkt_wej_1, punkt_kartezjanski *pkt_wej_2);
void normalizacja(punkt_kartezjanski *pkt_wyj,
		punkt_kartezjanski *pkt_wej);
float iloczyn_skalarny(punkt_kartezjanski *pkt_wej_1,
		punkt_kartezjanski *pkt_wej_2);
void mnozenie_wektora_przez_skalar(punkt_kartezjanski *wektor_wyj,
		punkt_kartezjanski *wektor_wej, float skalar);
void dodawanie_wektorow(punkt_kartezjanski *wektor_wyj,
		punkt_kartezjanski *wektor_wej_1, punkt_kartezjanski *wektor_wej_2);


void liniowa_interpolacja(
		punkt_kartezjanski punkt_poczatkowy,	// [IN] - Wspolrzedne punktu poczatkowego [mm]
		punkt_kartezjanski punkt_koncowy,		// [IN] - Wspolrzedne punktu koncowego [mm]
		//punkt_kartezjanski *trajektoria,
		int rozdzielczosc,						// [IN] - Rozdzielczosc [-]
		float v_max,							// [IN] - Maksymalna predkosc [mm/s]
		float a_max)							// [IN] - Maksymalne przyspieszenie [mm/s^2]
{
	if (rozdzielczosc < MAX_ROZDZIELCZOSC_INTERPOLACJI)
	{

		float s = sqrtf(powf(punkt_koncowy.x - punkt_poczatkowy.x, 2) +
				powf(punkt_koncowy.y - punkt_poczatkowy.y, 2) + powf(punkt_koncowy.z - punkt_poczatkowy.z, 2));	//dlugosci drogi

		float t_ruchu = fmaxf(sqrtf(6 * s / a_max), 3 * s / (2 * v_max));			//czas ruchu

		float inkrement_czasu = t_ruchu / rozdzielczosc;

		float t;

		for (uint8_t i = 0; i <= rozdzielczosc; i++)
		{
			t = i * inkrement_czasu;
			float wspolczynnik_od_czasu = powf(t / t_ruchu, 2) * (3 - 2 * t / t_ruchu);		//wspolczynnik przemieszczenia zalezny od czasu
			trajektoria_liniowa[i].x = punkt_poczatkowy.x + (punkt_koncowy.x - punkt_poczatkowy.x) * wspolczynnik_od_czasu;
			trajektoria_liniowa[i].y = punkt_poczatkowy.y + (punkt_koncowy.y - punkt_poczatkowy.y) * wspolczynnik_od_czasu;
			trajektoria_liniowa[i].z = punkt_poczatkowy.z + (punkt_koncowy.z - punkt_poczatkowy.z) * wspolczynnik_od_czasu;
			trajektoria_liniowa[i].t = t;
		}
	}
	else printf("BLAD: rozdzielczosc interpolacji musi byc mniejsza niz %d",
			MAX_ROZDZIELCZOSC_INTERPOLACJI);
}



void przegubowa_interpolacja(
		punkt_kartezjanski pozycja_poczatkowa,		// [IN] - Pozycja poczatkowa [mm]
		punkt_kartezjanski pozycja_koncowa,			// [IN] - Pozycja koncowa [mm]
		int rozdzielczosc,							// [IN] - Rozdzielczosc [-]
		float v_max,								// [IN] - Predkosc maksymalna [mm/s]
		float a_max)								// [IN] - Przyspieszenie maksymalna [mm/s^2]
{
	if (rozdzielczosc < MAX_ROZDZIELCZOSC_INTERPOLACJI)
	{
		float delta_d_max = fmaxf(fmaxf(fabsf(pozycja_koncowa.x - pozycja_poczatkowa.x), fabsf(pozycja_koncowa.y - pozycja_poczatkowa.y)), fabsf(pozycja_koncowa.z - pozycja_poczatkowa.z));	//najwieksze przemieszczenie przegubu

		float t_ruchu = fmaxf(sqrt(6 * delta_d_max / a_max), 3 * delta_d_max / (2 * v_max));												//czas ruchu

		float inkrement_czasu = t_ruchu / rozdzielczosc;

		float t;

		for (int i = 0; i <= rozdzielczosc; i++)
		{
			t = i * inkrement_czasu;
			float wspolczynnik_od_czasu = powf(t / t_ruchu, 2) * (3 - 2 * t / t_ruchu);	//wspolczynnik zalezny od czasu
			droga_przegubowa[i].x = pozycja_poczatkowa.x + (pozycja_koncowa.x - pozycja_poczatkowa.x) * wspolczynnik_od_czasu;
			droga_przegubowa[i].y = pozycja_poczatkowa.y + (pozycja_koncowa.y - pozycja_poczatkowa.y) * wspolczynnik_od_czasu;
			droga_przegubowa[i].z = pozycja_poczatkowa.z + (pozycja_koncowa.z - pozycja_poczatkowa.z) * wspolczynnik_od_czasu;
			droga_przegubowa[i].t = t;

		}
	}
	else printf("BLAD: rozdzielczosc interpolacji musi byc mniejsza niz %d",
			MAX_ROZDZIELCZOSC_INTERPOLACJI);
}



void kolowa_interpolacja(
        punkt_kartezjanski Ps,		// [IN] - Wspolrzedne punktu poczatkowego [mm]
		punkt_kartezjanski Pk,		// [IN] - Wspolrzedne punktu koncowego [mm]
		float promien,				// [IN] - Promien okregu [mm]
		int rozdzielczosc,			// [IN] - Rozdzielczosc [-]
		float v_max,				// [IN] - Maksymalna predkosc [mm/s]
		float a_max)				// [IN] - Maksymalne przyspieszenie [mm/s^2]
{
    // Pf - punkt koncowy
    // Ps - punkt poczatkowy
    // Po - srodek okregu
    // M - srodek odcinka miedzy Pk a Ps

    if (rozdzielczosc < MAX_ROZDZIELCZOSC_INTERPOLACJI)
    {
        float s_min = sqrtf(powf(Pk.x - Ps.x, 2) +  powf(Pk.y - Ps.y, 2) + powf(Pk.z - Ps.z, 2));
        float r_min = s_min/2;

        if (promien < r_min) promien = r_min+1;

        punkt_kartezjanski wektor_PsPf;
        wektor_PsPf.x = Pk.x - Ps.x;
        wektor_PsPf.y = Pk.y - Ps.y;
        wektor_PsPf.z = Pk.z - Ps.z;

        punkt_kartezjanski M;   //srodek odcinka miedzy Pf a Ps
        M.x = (Pk.x - Ps.x)/2 + Ps.x;
        M.y = (Pk.y - Ps.y)/2 + Ps.y;
        M.z = (Pk.z - Ps.z)/2 + Ps.z;

        //stała D od rownania plaszczyzny
        float D = -1*(wektor_PsPf.x * M.x + wektor_PsPf.y * M.y + wektor_PsPf.z * M.z);

        // ppPfsr - plaszczyzna prostopadla do_wektora_Pf_w_jego_srodku
        //float ppPfsr[4] = {wektor_PsPf.x, wektor_PsPf.y, wektor_PsPf.z, D};

        float przyprostokatna_1_r = sqrtf(powf(M.x - Ps.x, 2) +  powf(M.y - Ps.y, 2) + powf(M.z - Ps.z, 2));
        float przyprostokatna_2_r = sqrtf(powf(promien, 2) - powf(przyprostokatna_1_r, 2));


        punkt_kartezjanski Po; //srodek okregu
        Po.x = 0;
        Po.y = 0;
        Po.z = M.z;  //zakladamy ze wspol_Z srodka okregu bedzie sie pokrywac z wspol_Z srodka odcinka

        float a = wektor_PsPf.y/(-wektor_PsPf.x);
        float b = (wektor_PsPf.z * Po.z + D)/(-wektor_PsPf.x);
        float g = b - M.x;
        float m = powf(a, 2) + 1.0F;
        float n = 2*g*a - 2*M.y;
        float o = powf(g, 2) + powf(M.y, 2) - powf(przyprostokatna_2_r, 2);
        float delta = powf(n, 2) - 4*m*o;

        Po.y = ( -n - sqrtf(delta) ) / (2*m);
        Po.x = a * Po.y + b;

        //float temp_r1 = sqrtf(powf(Po.x - Ps.x, 2) +  powf(Po.y - Ps.y, 2) + powf(Po.z - Ps.z, 2));
        //float temp_r2 = sqrtf(powf(Po.x - Pf.x, 2) +  powf(Po.y - Pf.y, 2) + powf(Po.z - Pf.z, 2));


        punkt_kartezjanski wektor_PsPo = {};
        wektor_PsPo.x =  Po.x - Ps.x;
        wektor_PsPo.y =  Po.y - Ps.y;
        wektor_PsPo.z =  Po.z - Ps.z;

        //vector_sub(&wektor_PsPo, &Po, &Ps);

        //osie w układzie plaskim UV
        punkt_kartezjanski U;
        normalizacja(&U, &wektor_PsPf);

        punkt_kartezjanski V;
        iloczyn_wektorowy(&V, &U, &wektor_PsPo);
        iloczyn_wektorowy(&V, &V, &U);
        normalizacja(&V, &V);


        //punkty okręgu w układzie UV
        punkt_kartezjanski Ps_UV;
        Ps_UV.x = 0;
        Ps_UV.y = 0;
        punkt_kartezjanski Pf_UV;
        Pf_UV.x = iloczyn_skalarny(&wektor_PsPf, &U);
        Pf_UV.y = 0;
        punkt_kartezjanski Po_UV;
        Po_UV.x = iloczyn_skalarny(&wektor_PsPo, &U);
        Po_UV.y = iloczyn_skalarny(&wektor_PsPo, &V);

        float alfa_s = (atan2f(Ps_UV.y - Po_UV.y, Ps_UV.x - Po_UV.x));
        float alfa_f = (atan2f(Pf_UV.y - Po_UV.y, Pf_UV.x - Po_UV.x));
        float delta_alfa = fabsf(alfa_f - alfa_s);


        float s = 2 * PI * promien * (RAD2DEG(fabsf(delta_alfa))/360);

        float t_ruchu = fmaxf(sqrtf(6 * s / a_max), 3 * s / (2 * v_max));

        float inkrement_czasu = t_ruchu / rozdzielczosc;

        float inkrement_alfa = delta_alfa/rozdzielczosc;

        float t;
        float alfa;

        // punkty posrednie w UV
        punkt_kartezjanski P_UV[MAX_ROZDZIELCZOSC_INTERPOLACJI];

        for (int i = 0; i <= rozdzielczosc; i++)
        {
            t = i * inkrement_czasu;
            alfa = i * inkrement_alfa;
            P_UV[i].x = Po_UV.x + promien * cosf(alfa_s + alfa);
            P_UV[i].y = Po_UV.y + promien * sinf(alfa_s + alfa);
            P_UV[i].t = t;
        }
        //tutaj nadpisuje wartosci poniewaz z powyzszych przeksztalcen punkt poczatkowy i koncowy roznia sie o kilka tysiecznych
        P_UV[0].x = Ps_UV.x;
        P_UV[0].y = Ps_UV.y;
        P_UV[rozdzielczosc].x = Pf_UV.x;
        P_UV[rozdzielczosc].y = Pf_UV.y;


        // osie do rzutowania
        punkt_kartezjanski x_axis;
        x_axis.x = 1;
        x_axis.y = 0;
        x_axis.z = 0;
        punkt_kartezjanski y_axis;
        y_axis.x = 0;
        y_axis.y = 1;
        y_axis.z = 0;
        punkt_kartezjanski z_axis;
        z_axis.x = 0;
        z_axis.y = 0;
        z_axis.z = 1;

        punkt_kartezjanski P_U_axis = {};
        punkt_kartezjanski P_V_axis = {};
        punkt_kartezjanski P_UV_axis = {};

        for (int i = 0; i <= rozdzielczosc; i++)
        {
            //wektory U i V o długościach równych współrzędnym punktu p_uv
        	mnozenie_wektora_przez_skalar(&P_U_axis, &U, P_UV[i].x);
            mnozenie_wektora_przez_skalar(&P_V_axis, &V, P_UV[i].y);

            //suma wektorów = wektor od p_s do p w układzie XYZ
            dodawanie_wektorow(&P_UV_axis, &P_U_axis, &P_V_axis);

            //rzutowanie wektora p_uv_axis na osie układu XYZ
            trajektoria_kolowa[i].x = Ps.x + iloczyn_skalarny(&P_UV_axis, &x_axis);
            trajektoria_kolowa[i].y = Ps.y + iloczyn_skalarny(&P_UV_axis, &y_axis);
            trajektoria_kolowa[i].z = Ps.z + iloczyn_skalarny(&P_UV_axis, &z_axis);
            trajektoria_kolowa[i].t = P_UV[i].t;
        }
        //tutaj nadpisuje wartosci poniewaz z powyzszych przeksztalcen punkt koncowy rozni sie o kilka tysiecznych
        trajektoria_kolowa[rozdzielczosc].x = Pk.x;
        trajektoria_kolowa[rozdzielczosc].y = Pk.y;
        trajektoria_kolowa[rozdzielczosc].z = Pk.z;

    }
    else printf("BLAD: rozdzielczosc interpolacji musi byc mniejsza niz %d",
    		MAX_ROZDZIELCZOSC_INTERPOLACJI);
}


void iloczyn_wektorowy(
		punkt_kartezjanski *pkt_wyj,		// [OUT]
		punkt_kartezjanski *pkt_wej_1,		// [IN]
		punkt_kartezjanski *pkt_wej_2)		// [IN]
{
	pkt_wyj->x = pkt_wej_1->y * pkt_wej_2->z - pkt_wej_1->z * pkt_wej_2->y;
	pkt_wyj->y = pkt_wej_1->z * pkt_wej_2->x - pkt_wej_1->x * pkt_wej_2->z;
	pkt_wyj->z = pkt_wej_1->x * pkt_wej_2->y - pkt_wej_1->y * pkt_wej_2->x;
}


void normalizacja(
		punkt_kartezjanski *pkt_wyj,		// [OUT]
		punkt_kartezjanski *pkt_wej)		// [IN]
{
	float dlugosc_pkt_wej = sqrtf(powf(pkt_wej->x, 2) + powf(pkt_wej->y, 2) + powf(pkt_wej->z, 2));
	pkt_wyj->x = pkt_wej->x / dlugosc_pkt_wej;
	pkt_wyj->y = pkt_wej->y / dlugosc_pkt_wej;
	pkt_wyj->z = pkt_wej->z / dlugosc_pkt_wej;
}


float iloczyn_skalarny(
		punkt_kartezjanski *pkt_wej_1,		// [IN]
		punkt_kartezjanski *pkt_wej_2)		// [IN]
{
	return pkt_wej_1->x * pkt_wej_2->x + pkt_wej_1->y * pkt_wej_2->y + pkt_wej_1->z * pkt_wej_2->z;
}


void mnozenie_wektora_przez_skalar(
		punkt_kartezjanski *wektor_wyj,		// [OUT]
		punkt_kartezjanski *wektor_wej,		// [IN]
		float skalar)						// [IN]
{
	wektor_wyj->x = wektor_wej->x * skalar;
	wektor_wyj->y = wektor_wej->y * skalar;
	wektor_wyj->z = wektor_wej->z * skalar;
}


void dodawanie_wektorow(
		punkt_kartezjanski *wektor_wyj,		// [OUT]
		punkt_kartezjanski *wektor_wej_1,	// [IN]
		punkt_kartezjanski *wektor_wej_2)	// [IN]
{
	wektor_wyj->x = wektor_wej_1->x + wektor_wej_2->x;
	wektor_wyj->y = wektor_wej_1->y + wektor_wej_2->y;
	wektor_wyj->z = wektor_wej_1->z + wektor_wej_2->z;
}

