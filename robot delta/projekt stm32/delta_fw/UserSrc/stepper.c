#include "stepper.h"


#define INSTANCJA_SILNIKA(tim_inst, tim_channel, dir_gpio_port, dir_pin_mask, en_gpio_port, en_pin_mask, u_step) \
	{ \
		.timInstance = tim_inst, \
		.timChannel = tim_channel, \
		.dirGpioPort = (void *) dir_gpio_port, \
		.dirPinMask = (uint32_t) dir_pin_mask, \
		.enGpioPort = (void *) en_gpio_port, \
		.enPinMask = (uint32_t) en_pin_mask, \
		.uStep = u_step, \
		.pitch = 16.0F, \
		.currAngle = INFINITY, \
		.moving_f = 0, \
		.isEnabled = 0, \
		.stepsCount = 0, \
		.dir = 0, \
		.absPos = 0.0F \
	}

Stepper_t lista_silnikow[LICZBA_SILNIKOW] =
{
	INSTANCJA_SILNIKA(&TIM_H_X, TIM_CH_X, X_DIR_GPIO_Port,
			X_DIR_Pin, X_EN_GPIO_Port, X_EN_Pin, 16),
	INSTANCJA_SILNIKA(&TIM_H_Y, TIM_CH_Y, Y_DIR_GPIO_Port,
			Y_DIR_Pin, Y_EN_GPIO_Port, Y_EN_Pin, 16),
	INSTANCJA_SILNIKA(&TIM_H_Z, TIM_CH_Z, Z_DIR_GPIO_Port,
			Z_DIR_Pin, Z_EN_GPIO_Port, Z_EN_Pin, 16)
};

Stepper_Status_t stepperStatus = STEPPER_OK;


void Stepper_Init(void)
{
	lista_silnikow[0].stepsPerRev = 200 * lista_silnikow[0].uStep;
	lista_silnikow[1].stepsPerRev = 200 * lista_silnikow[1].uStep;
	lista_silnikow[2].stepsPerRev = 200 * lista_silnikow[2].uStep;

	lista_silnikow[0].mmPerStep = lista_silnikow[0].pitch / lista_silnikow[0].stepsPerRev;
	lista_silnikow[1].mmPerStep = lista_silnikow[1].pitch / lista_silnikow[1].stepsPerRev;
	lista_silnikow[2].mmPerStep = lista_silnikow[2].pitch / lista_silnikow[2].stepsPerRev;

	TIM_H_X.Instance->CCR1 = 2;
	TIM_H_Y.Instance->CCR1 = 2;
	TIM_H_Z.Instance->CCR1 = 2;
}


void Stepper_Update(int i)
{
	lista_silnikow[i].absPos += (lista_silnikow[i].dir) ? (-lista_silnikow[i].mmPerStep) : (lista_silnikow[i].mmPerStep);
	lista_silnikow[i].stepsCount--;
	if (lista_silnikow[i].stepsCount == 0)
	{
		lista_silnikow[i].moving_f = 0;
		HAL_TIM_PWM_Stop_IT(lista_silnikow[i].timInstance, lista_silnikow[i].timChannel);
		Stepper_Disable(&lista_silnikow[i]);
	}
}


void Stepper_Enable(Stepper_t *instancja_silnika)
{
	instancja_silnika->isEnabled = 1;
	HAL_GPIO_WritePin(instancja_silnika->enGpioPort,
			instancja_silnika->enPinMask, GPIO_PIN_RESET);
}


void Stepper_Disable(Stepper_t *instancja_silnika)
{
	instancja_silnika->isEnabled = 0;
	HAL_GPIO_WritePin(instancja_silnika->enGpioPort,
			instancja_silnika->enPinMask, GPIO_PIN_SET);
}


void Stepper_EnableAll(void)
{
	for (uint8_t i = 0; i < LICZBA_SILNIKOW; ++i)
	{
		HAL_GPIO_WritePin(lista_silnikow[i].enGpioPort,
				lista_silnikow[i].enPinMask, GPIO_PIN_RESET);
		lista_silnikow[i].isEnabled = 1;
	}
}


Stepper_Status_t Stepper_moveAbsPos(Stepper_t *instancja_silnika,
		float pozycja,
		float predkosc)
{
	if (!instancja_silnika->isEnabled) return STEPPER_DISABLED;
	if (instancja_silnika->moving_f) return STEPPER_MOVE_INTERRUPT;
	//if (pozycja < JOINT_MIN_POS || pozycja > JOINT_MAX_POS) return STEPPER_OUT_OF_RANGE;
	if (predkosc == 0) return STEPPER_OK;

	// Zmiana czestotliwosci PWM na podstawie zadanej predkosci
	TIM_HandleTypeDef *tmpTim = instancja_silnika->timInstance;
	float czestotliwosc_pwm = (predkosc / instancja_silnika->mmPerStep); 				// mm/s -> steps/s (PWM freq)
	WRITE_REG(tmpTim->Instance->PSC, (uint32_t) 50000000.0F / czestotliwosc_pwm);

	float dystans = pozycja - instancja_silnika->absPos;

	// Wybranie kierunku obrotu
	instancja_silnika->dir = (dystans < 0) ? (1) : (0);
	dystans = fabsf(dystans);

	// Obliczenie liczby krokow do pokonania
	instancja_silnika->stepsCount = (uint32_t) roundf(200.0F * dystans);
	if (instancja_silnika->stepsCount == 0) return STEPPER_OK;

	instancja_silnika->moving_f = 1;

	// Uruchomienie PWM (zostabie wylaczony w przerwaniu jak wykona zadana liczbe krokow)
	HAL_GPIO_WritePin(instancja_silnika->dirGpioPort, instancja_silnika->dirPinMask, instancja_silnika->dir);
	HAL_TIM_PWM_Start_IT(instancja_silnika->timInstance, instancja_silnika->timChannel);

	return STEPPER_OK;
}


Stepper_Status_t Stepper_moveIncDist(
		Stepper_t *instancja_silnika,			// [IN] - wskaznik na strukture zawierajaca informacje o krokowcu
		float dystans,							// [IN] - odleglosc ktora nalezy przejechac, wartosci ujemne oznaczaja zmiane kierunku [mm]
		float predkosc)							// [IN] - liniowa predkosc poruszania sie [mm/s]
{
	if (!instancja_silnika->isEnabled) return STEPPER_DISABLED;
	if (instancja_silnika->moving_f) return STEPPER_MOVE_INTERRUPT;
	if (instancja_silnika->absPos - dystans < JOINT_MIN_POS || instancja_silnika->absPos + dystans > JOINT_MAX_POS)
		return STEPPER_OUT_OF_RANGE;
	if (predkosc == 0) return STEPPER_OK;

	// Zmiana czestotliwosci PWM na podstawie zadanej predkosci
	TIM_HandleTypeDef *tmpTim = instancja_silnika->timInstance;
	float czestotliwosc_pwm = (predkosc / instancja_silnika->mmPerStep); 				// mm/s -> steps/s (PWM freq)
	WRITE_REG(tmpTim->Instance->PSC, (uint32_t) 50000000.0F / czestotliwosc_pwm);

	// Wybranie kierunku obrotu
	instancja_silnika->dir = (dystans < 0) ? (1) : (0);
	dystans = fabsf(dystans);

	// Obliczenie liczby krokow do pokonania
	instancja_silnika->stepsCount = (uint32_t) roundf(200.0F * dystans);
	if (instancja_silnika->stepsCount == 0) return STEPPER_OK;

	instancja_silnika->moving_f = 1;

	// Uruchomienie PWM (zostabie wylaczony w przerwaniu jak wykona zadana liczbe krokow)
	HAL_GPIO_WritePin(instancja_silnika->dirGpioPort, instancja_silnika->dirPinMask, instancja_silnika->dir);
	HAL_TIM_PWM_Start_IT(instancja_silnika->timInstance, instancja_silnika->timChannel);

	return STEPPER_OK;
}


void Stepper_EndStopHandler(int i)
{
	HAL_TIM_PWM_Stop_IT(lista_silnikow[i].timInstance, lista_silnikow[i].timChannel);
	lista_silnikow[i].moving_f = 0;
	lista_silnikow[i].stepsCount = 0;
	Stepper_Disable(&lista_silnikow[i]);
}


// Obsluga przerwan PWM krokowcow oraz serw
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM_H_X.Instance)
	{
		Stepper_Update(0);
	}
	else if (htim->Instance == TIM_H_Y.Instance)
	{
		Stepper_Update(1);
	}
	else if (htim->Instance == TIM_H_Z.Instance)
	{
		Stepper_Update(2);
	}
}

