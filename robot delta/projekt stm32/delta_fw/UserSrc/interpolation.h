#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "math_consts.h"

#define MAX_ROZDZIELCZOSC_INTERPOLACJI 100

typedef struct Punkt_kartezjanski
{
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		float wektor[3];
	};
	float t;
} punkt_kartezjanski;

/*
typedef struct Punkt_przegubowy
{
	float d_1;
	float d_2;
	float d_3;
	float t;
} punkt_przegubowy;
*/

//extern punkt_kartezjanski trajektoria_liniowa_przeskalowana[MAX_ROZDZIELCZOSC_INTERPOLACJI];
extern punkt_kartezjanski trajektoria_liniowa[MAX_ROZDZIELCZOSC_INTERPOLACJI];
extern punkt_kartezjanski trajektoria_kolowa[MAX_ROZDZIELCZOSC_INTERPOLACJI];
extern punkt_kartezjanski droga_przegubowa[MAX_ROZDZIELCZOSC_INTERPOLACJI];

extern void liniowa_interpolacja(punkt_kartezjanski punkt_poczatkowy,
		punkt_kartezjanski punkt_koncowy, int rozdzielczosc, float v_max, float a_max);
extern void przegubowa_interpolacja(punkt_kartezjanski pozycja_poczatkowa,
		punkt_kartezjanski pozycja_koncowa, int rozdzielczosc, float v_max, float a_max);
extern void kolowa_interpolacja(punkt_kartezjanski punkt_poczatkowy,
		punkt_kartezjanski punkt_koncowy, float promien, int rozdzielczosc, float v_max, float a_max);


//extern void liniowa_interpolacja(punkt_kartezjanski punkt_poczatkowy, punkt_kartezjanski punkt_koncowy,
//		punkt_kartezjanski *trajektoria, int rozdzielczosc, float v_max, float a_max);
