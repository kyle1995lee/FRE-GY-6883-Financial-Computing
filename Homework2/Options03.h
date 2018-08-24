#pragma once

#ifndef Options03_h
#define Options03_h

int GetInputData(int& N, double& K);
//computing call payoff
double CallPayoff(double z, double K);
//computing put payoff
double PutPayoff(double z, double K);
double DigitCallPayoff(double z, double K);
double DigitPutPayoff(double z, double K);
double PriceByCRR(double S0, double U, double D, double R, int N, double K,
	double(*Payoff)(double z, double K));

#endif
