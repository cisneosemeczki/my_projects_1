#include "delta_kinematics.h"

uint8_t odwrotna_kinematyka(
        float *pozycja_wozkow_prowadnicy,
		float *zadana_pozycja_xyz)
{
    uint8_t status = 0;

    float a = L1;
    float b = L4;
    float l = L3;
    float alfa = ALPHA;
    float teta = 0.0F;

    float fi;
    float beta;

    for (int i=1; i<=3; i++)
    {
        fi = (i - 1) * 120;
        beta = teta + (i - 1) * 120;

        //zakladamy ze wszystkie wektory maja strukture 3x1 czyli 3wiersze oraz 1 kolumna, w matlabie jest to vector = [a; b; c]

        float vector_a[3] = {a*cosf(DEG2RAD(fi)), a*sinf(DEG2RAD(fi)), 0};
        float vector_b[3] = {b*cosf(DEG2RAD(beta)), a*sinf(DEG2RAD(beta)), 0};

        float vector_d[3] =  {-cosf(DEG2RAD(alfa))*cosf(DEG2RAD(fi)), -cosf(DEG2RAD(alfa))*sinf(DEG2RAD(fi)), -sinf(DEG2RAD(alfa)) };

        float vector_L[3] = {0};

        vector_L[0] = zadana_pozycja_xyz[0] + vector_b[0] - vector_a[0];
        vector_L[1] = zadana_pozycja_xyz[1] + vector_b[1] - vector_a[1];
        vector_L[2] = zadana_pozycja_xyz[2] + vector_b[2] - vector_a[2];

        float temp_di0T_Li;
        temp_di0T_Li = vector_d[0] * vector_L[0] + vector_d[1] * vector_L[1] + vector_d[2] * vector_L[2];
        float temp_LiT_Li;
        temp_LiT_Li = vector_L[0] * vector_L[0] + vector_L[1] * vector_L[1] + vector_L[2] * vector_L[2];

        pozycja_wozkow_prowadnicy[i-1] = temp_di0T_Li - sqrtf( powf(temp_di0T_Li, 2) - temp_LiT_Li + powf(l, 2) );

        //printf("%d prowadnica - polozenie wynosi %f\n", i, pozycja_wozkow_prowadnicy[i-1]);

    }
    return status = 0;
}
