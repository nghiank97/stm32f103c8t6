#include "pid.h"

PIDController::PIDController(float P, float I , float D, uint16_t limit)
    : P(P)
    , I(I)
	, D(D)
    , limit(limit)
{
	proportional = 0;
	integral = 0;
	derivative = 0;
	output = 0;
	error_prev = 0;
}

float PIDController::operator() (float error){
	proportional = P * error;
	integral += I*(float)error;

	if (integral < -limit/2){
		integral = -limit/2;
	}
	if (integral > limit/2){
		integral = limit/2;
	}

	derivative = D*(error - error_prev);
	output= proportional + integral + derivative;

	if (output < -limit){
		output = -limit;
	}
	if (output > limit){
		output = limit;
	}

    error_prev = error;
    return output;
}

void PIDController::reset(void){
	proportional = 0;
	integral = 0;
	derivative = 0;
	output = 0;
	error_prev = 0;
}
