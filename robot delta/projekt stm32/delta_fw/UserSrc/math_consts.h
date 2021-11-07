#pragma once

#include <math.h>


#define PI		( (float) M_PI )

#define SQRT_2	( (float) M_SQRT2 )
#define SQRT_3	( (float) M_SQRT3 )

#define SIN_30	( 0.5F )
#define SIN_60	( 0.866025403784439F )
#define SIN_120 ( 0.866025403784439F )
#define COS_30	( 0.866025403784439F )
#define COS_60	( 0.5F )
#define COS_120 ( -0.5F )
#define TAN_30	( 0.577350269189626F )
#define TAN_60	( 1.732050807568878F )
#define TAN_120 ( -1.732050807568878F )

#define __DEG2RAD_COEF__	( M_PI / 180.0 )
#define DEG2RAD(deg_angle)	( (float) (deg_angle * __DEG2RAD_COEF__) )

#define __RAD2DEG_COEF__	( 180.0 / M_PI )
#define RAD2DEG(rad_angle)	( (float) (rad_angle * __RAD2DEG_COEF__) )
