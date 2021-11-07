#pragma once

#include <string.h>
#include <stdio.h>

#include "usart.h"
#include "gpio.h"

#define LINE_MAX_LENGTH 80

extern int ruch_robotem;
extern int rozdzielczosc_interpolacji;
extern float rodzaj_interpolacji, wspolrzedna_X, wspolrzedna_Y, wspolrzedna_Z;

extern int __io_putchar(int ch);
extern void odbior_danych_z_aplikacji(uint8_t value);
extern void przypisanie_danych_do_zmiennych(void);
