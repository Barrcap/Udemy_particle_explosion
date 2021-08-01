/*
 * Particle.cpp
 *
 *  Created on: 1 Oct 2020
 *      Author: barr
 */

#include "Particle.h"

namespace fartsimulator {

Particle::Particle(): m_x(0), m_y(0) {

	init();

}

void Particle::init() {
	m_x = 0;
	m_y = 0;
	m_direction = ((2 * M_PI * rand())/RAND_MAX); // setting random val between 0 and 2*PI
	m_speed = (SPEED * rand()) / RAND_MAX; // setting random val between -1 and 1, multipy by SPEED const
	m_speed *= m_speed;
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

void Particle::update(int interval) {

	//add rotation
	m_direction += interval * ANGULAR_SPEED;

	double xspeed = m_speed * cos(m_direction);
	double yspeed = m_speed * sin(m_direction);

	m_x += xspeed * interval;
	m_y += yspeed * interval;

	if (m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1)
		init();

	if (rand() < RAND_MAX/100)
		init();

}

} /* namespace fartsimulator */
