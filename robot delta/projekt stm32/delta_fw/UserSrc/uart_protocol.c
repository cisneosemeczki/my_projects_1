#include "uart_protocol.h"

static char line_buffer[LINE_MAX_LENGTH + 1];
static uint32_t line_length;

static char *point_code;

float rodzaj_interpolacji = 0;
int rozdzielczosc_interpolacji = 0;
float wspolrzedna_X = 0;
float wspolrzedna_Y = 0;
float wspolrzedna_Z = 0;

int ruch_robotem = 0;


int __io_putchar(int ch)
{
    if (ch == '\n') {
        uint8_t ch2 = '\r';
        HAL_UART_Transmit(&huart2, &ch2, 1, HAL_MAX_DELAY);
    }

    HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
    return 1;
}



void odbior_danych_z_aplikacji(uint8_t value)
{
	if (value == '\r' || value == '\n')
	{
		if (line_length > 0)
		{
			line_buffer[line_length] = '\0';
			printf("Otrzymano: %s\n", line_buffer);

			if (strcmp(line_buffer, "ruch_efektorem") == 0)
			{
				ruch_robotem = 1;
				printf("Robot uruchamia przejazd efektorem!\n");
			}
			else
			{
				point_code = line_buffer;
				przypisanie_danych_do_zmiennych();
			}
			line_length = 0;
		}
	}
	else
	{
		if (line_length >= LINE_MAX_LENGTH)
		{
			line_length = 0;
		}
		line_buffer[line_length++] = value;
	}
}



void przypisanie_danych_do_zmiennych(void)
{
	sscanf(line_buffer, "%f:%d:%f:%f:%f", &rodzaj_interpolacji, &rozdzielczosc_interpolacji, &wspolrzedna_X, &wspolrzedna_Y, &wspolrzedna_Z);
	printf("interpolacja: G%.0f   rozdzielczosc: %d   wspol_X: %.3f   wspol_Y: %.3f   wspol_Z: %.3f\n",
			rodzaj_interpolacji, rozdzielczosc_interpolacji, wspolrzedna_X, wspolrzedna_Y, wspolrzedna_Z);
}
