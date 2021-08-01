/*
 * Particle.h
 *
 *  Created on: 1 Oct 2020
 *      Author: barr
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <stdlib.h>
#include <math.h>

namespace fartsimulator {

struct Particle {
	double m_x;
	double m_y;
	const double SPEED = 0.04;
	const double ANGULAR_SPEED = 0.003;

private:
	double m_speed;
	double m_direction;

public:
	Particle();
	virtual ~Particle();
	void init();
	void update(int interval);
};

} /* namespace fartsimulator */

#endif /* PARTICLE_H_ */
