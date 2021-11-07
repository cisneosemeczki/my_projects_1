#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "tim.h"
#include "math_consts.h"
#include "delta_geometry.h"


#define TIM_H_X		( htim3 )
#define TIM_H_Y		( htim2 )
#define TIM_H_Z		( htim4 )

#define TIM_CH_X	( TIM_CHANNEL_1 )
#define TIM_CH_Y	( TIM_CHANNEL_1 )
#define TIM_CH_Z	( TIM_CHANNEL_1 )

#define LICZBA_SILNIKOW		( 3 )


typedef struct instancja_silnika
{
	void *const timInstance;
	const uint32_t timChannel;
	void *const dirGpioPort;
	const uint32_t dirPinMask;
	void *const enGpioPort;
	const uint32_t enPinMask;
	uint16_t stepsPerRev;
	uint8_t uStep;
	float pitch;
	float mmPerStep;
	float currAngle;
	uint8_t moving_f;
	uint8_t isEnabled;
	int32_t stepsCount;
	uint8_t dir;
	float absPos;
	float velocity;
} Stepper_t;

typedef enum
{
	STEPPER_OK = 0,
	STEPPER_DISABLED,
	STEPPER_OUT_OF_RANGE,
	STEPPER_MOVE_INTERRUPT
} Stepper_Status_t;

extern Stepper_t lista_silnikow[LICZBA_SILNIKOW];
extern Stepper_Status_t stepperStatus;

extern void Stepper_Init(void);
extern void Stepper_Update(int i);
extern void Stepper_Enable(Stepper_t *instancja_silnika);
extern void Stepper_Disable(Stepper_t *instancja_silnika);
extern void Stepper_EnableAll(void);
extern Stepper_Status_t Stepper_moveAbsPos(Stepper_t *instancja_silnika,
		float pozycja, float predkosc);
extern Stepper_Status_t Stepper_moveIncDist(Stepper_t *instancja_silnika,
		float dystans,	float predkosc);
extern void Stepper_EndStopHandler(int i);


