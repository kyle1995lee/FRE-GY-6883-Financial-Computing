#ifndef Strangle_h
#define Strangle_h
#include "Options06.h"
class Strangle : public EurOption
{
private:
	double K1; //parameter 1
	double K2; //parameter 2
public:
	int GetInputData();
	double Payoff(double z);
};
#endif
#pragma once
