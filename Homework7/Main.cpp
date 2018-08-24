#include <iostream>
#include <iomanip>
#include "BinModel02.h"
#include "BinLattice02.h"
#include "Options09.h"
#include <cmath>
using namespace std;
int main()
{
	double S0 = 106.0;
	double r = 0.058;
	double sigma = 0.46;
	double T = (double)9 / 12;
	double K = 100.0;
	int N = 8;
	double h = T / N;
	cout << setiosflags(ios::fixed) << setprecision(5);

	cout << "S0 = " << S0 << endl;
	cout << "r  = " << r << endl;
	cout << "sigma = " << sigma << endl;
	cout << "T = " << T << endl;
	cout << "K = " << K << endl;
	cout << "N = " << N << endl << endl;

	double U = exp((r - pow(sigma, 2) / 2)*h + sigma * sqrt(h)) - 1, D = exp((r - pow(sigma, 2) / 2)*h - sigma * sqrt(h)) - 1, R = exp(r*h) - 1;
	BinModel Appx(S0, U, D, R);
	cout << "U = " << Appx.GetU() << endl;
	cout << "D = " << Appx.GetD() << endl;
	cout << "R = " << Appx.GetR() << endl;

	BinLattice<double> PriceTree;
	BinLattice<bool> StoppingTree;
	Call option1;
	option1.GetInputData(N, K);
	cout << "American call option price = " << option1.PriceBySnell(Appx, PriceTree, StoppingTree) << endl;

	system("pause");
	return 0;
}
