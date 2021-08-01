/*
 * Swarm.h
 *
 *  Created on: 1 Oct 2020
 *      Author: barr
 */

#ifndef SWARM_H_
#define SWARM_H_

#include "Particle.h"

namespace fartsimulator {

class Swarm {
public:
	const static int NPARTICLES = 500;
private:
	Particle * m_pParticles;
	int lastTime;

public:
	Swarm();
	virtual ~Swarm();

	const Particle * const getPerticle() { return m_pParticles; };
	void update(int elapsed);
};

} /* namespace fartsimulator */

#endif /* SWARM_H_ */
