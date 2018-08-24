#include "Options01.h"
#include "stdafx.h"
#include "BinModel01.h"
#include <iostream>
#include <cmath>
using namespace std;
int GetInputData(int& N, double& K)
{
	cout << "Enter steps to expiry N: "; cin >> N;
	cout << "Enter strike price K:    "; cin >> K;
	cout << endl;
	return 0;
}

double CallPayoff(double z, double K)
{
	if (z>K) return z - K;
	return 0.0;
}

double Conbi(double n, double x) {
	double i;
	double temp;
	temp = 1.0;
	if (x == 0) {
		return 1;
	}
	else {
		for (i = 0; i < x; i++) {
			temp = ((n - i) / (i + 1))*temp;
		}
		return temp;
	}
}

double PriceByCRR(double S0, double U, double D, double R, int N, double K)
{
	double q = RiskNeutProb(U, D, R);
	double Price[10];
	double price_crr=0;
	for (int i = 0; i <= N; i++)
	{
		Price[i] = CallPayoff(S(S0, U, D, N, i), K);
	}
	/*
	for (int n = N - 1; n >= 0; n--)
	{
		for (int i = 0; i <= n; i++)
		{
			Price[i] = (q*Price[i + 1] + (1 - q)*Price[i]) / (1 + R);
		}
	}*/
	for (int i = 0; i <= N; i++) {
		price_crr = price_crr + (Conbi(N, i)*pow(q, i)*pow((1 - q), N - i)*Price[i]) / pow((1 + R), N);
	}
	return price_crr;
}
