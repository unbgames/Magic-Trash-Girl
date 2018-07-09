/*
 * Fader.h
 *
 *  Created on: 01/06/2018
 *      Author: gabriel
 */

#ifndef FADER_H_
#define FADER_H_
#include "globals.h"

class Fader{
public:
	static void 	CalculateParam(FadeTypes fade,double &a, double &b, double &c, float Vi, float Vf, float time);
	static float	Eval(FadeTypes fade,double a, double b, double c, float t);
};



#endif /* FADER_H_ */
