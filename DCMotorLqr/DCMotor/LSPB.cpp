
#include "LSPB.h"
#include <math.h>
#include <stdio.h>

LSPB::LSPB(float _Vo, float _t)
{
	t0 = 0;
	tf = 0;
	Vo = _Vo;
	V = _Vo;

	q0 = 0;
	qf = 0;

    tb = 0;

	index= _t;
	finished = 0;
	t = 0;
	position = 0;
}

float LSPB::position_yt(float _t){
	if ((0<= _t) and (_t <= tb)){
    	position = q0 + t*t*V/(2*tb);
	}
    else if ((tb < _t) and (_t <= (tf - tb))){
        position = (V*_t + (qf + q0 - V*tf)/2);
    }
    else if (((tf - tb) < _t) and (_t < tf)){
    	position = qf- tf*tf*V/(2*tb)+ _t*V*tf/tb- _t*_t*V/(2*tb);
    }
	return position;
}

float LSPB::operator() (int16_t sp){
	int16_t delta = sp-qf;
	if ((delta != 0) && ((t > tf) || (t == 0))){
		q0 = qf;
		qf = sp;

        if ((qf - q0) >= 0)
            V = Vo;
        else
            V = -Vo;

		tf = 1.5*(qf - q0)/V;
        tb = (q0 - qf + V*tf)/V;

        t = 0;
        finished = 0;
	}
    if (t <= tf){
    	t += index;
    	return position_yt(t);
    }
    else{
    	finished = 1;
    	return position_yt(tf);
    }
}

