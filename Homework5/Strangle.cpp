#include "stdafx.h"
#include "Strangle.h"
#include <iostream>
using namespace std;
int Strangle::GetInputData()
{
	cout << "Enter European Strangle option data:" << endl;
	int N;
	cout << "Enter steps to expiry N: "; cin >> N;
	SetN(N);
	cout << "Enter parameter K1:      "; cin >> K1;
	cout << "Enter parameter K2:      "; cin >> K2;
	cout << endl;
	return 0;
}
double Strangle::Payoff(double z)
{
	if (z <= K1) {
		return K1 - z;
	}
	else if (z > K2) {
		return z - K2;
	}
	else {
		return 0.0;
	}
}
