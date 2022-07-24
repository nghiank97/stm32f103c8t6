

#ifndef ENCODER_H
#define ENCODER_H

#ifdef __cplusplus
extern "C"{
#endif

#include "Config.h"

class Encoder{
public:
	Encoder(void);
	void update(void);
	float getPosition(void);
	float getVelocity(void);
private:
	int32_t raw_count = 0;
	float part_position, position, velocity;
};

#ifdef __cplusplus
}
#endif
#endif