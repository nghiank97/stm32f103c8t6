#include <math.h>
#include "Drive.h"
#include "Defaults.h"
#include "Config.h"

Drive::Drive(void){
#ifndef DEF_PWM_LIM
	#error "don't define the pwm range"
#endif
}

void Drive::setVoltage(int16_t pwm){
	if (pwm < 0){
		IN1_ON();
		IN2_OFF();
	}
	else{
		IN1_OFF();
		IN2_ON();
	}
	tim_pwm_set_value(abs(pwm));
}
