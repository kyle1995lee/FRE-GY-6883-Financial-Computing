#ifndef Butterfly_h
#define Butterfly_h
#include "Options06.h"
class Butterfly : public EurOption
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
