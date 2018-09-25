/*
 * Fader.cpp
 *
 *  Created on: 01/06/2018
 *      Author: gabriel
 */
#include "Fader.h"

void Fader::CalculateParam(FadeTypes fade, double &a, double &b, double &c, float Vi, float Vf, float time){
	switch (fade){
		case LINEAR:				// y(x) = a*x+b
			a = 1.0*(Vf-Vi)/time;
			b = Vi;
		break;
		case SQUARE:				// y(x) = a*x^2 + bx + c
			a = -1.0*(Vf-Vi)/(time*time);
			b = 2.0*(Vf-Vi)/(time);
			c = Vi;
		break;
		case EXPONENTIAL:{			// y(x) = a*e^(bx) + c - a
			float dv = fabs(Vf - Vi);

			a = (Vf - Vi<0)? -1.0*music_constants::EXP_CONST:music_constants::EXP_CONST;
			b = log((dv + music_constants::EXP_CONST)/music_constants::EXP_CONST)/time;
			c = Vi;
		break;}
		case INVERSESQUARE:{		// y(x) = a/((x+b)^2)
			if (Vi==0) Vi = music_constants::MINVOLUME;
			if (Vf==0) Vf = music_constants::MINVOLUME;

			if (Vi>Vf){
				a= Vi*time*time/((sqrt(Vi/(Vf)) -1)*(sqrt(Vi/(Vf))  -1));
				b= time/((sqrt(Vi/(Vf)) -1));
			}

			else{
				a= Vf*time*time/((sqrt(Vf/(Vi)) -1)*(sqrt(Vf/(Vi))  -1));
				b= -time/((sqrt(Vf/(Vi)) -1))-time;
			}
		break;}}
}

float Fader::Eval(FadeTypes fade, double a, double b, double c, float t){
								// Condicionais? Limites? Fica para o leitor a prova de que não precisa...
		switch (fade){
		case LINEAR:
			return a*t + b;
		break;
		case SQUARE:
			return a*t*t + b*t + c;
		break;
		case EXPONENTIAL:
			return a*exp(b*t) + c - a;
		break;
		case INVERSESQUARE:
			return a/((b+t)*(b+t));
		break;
		}
	return 0;
}

