
#ifndef LSPB_H
#define LSPB_H

#ifdef __cplusplus
extern "C"{
#endif
#include <inttypes.h>
#include "defaults.h"
class LSPB{

private:
	float t0, tf;
	int16_t q0, qf;

	float V,Vo;
	float tb = 0;

	float t;
	float index;
	float position;

public:
	LSPB(float _V, float _t);
	float operator()(int16_t sp);
	float position_yt(float _t);
	int finished;
};

#ifdef __cplusplus
}
#endif
#endif
