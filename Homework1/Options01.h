#pragma once

#ifndef Options01_h
#define Options01_h

int GetInputData(int& N, double& K);
double CallPayoff(double z, double K);
double Conbi(double n, double x);
double PriceByCRR(double S0, double U, double D, double R, int N, double K);

#endif
