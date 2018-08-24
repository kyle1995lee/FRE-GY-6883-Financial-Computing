#include "Solver03.h"
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
class F1
{
public:
	double Value(double x) { return x * x - 2; }
	double Deriv(double x) { return 2 * x; }
};
class F2
{
private:
	double a; //parameter
public:
	F2(double a_) { a = a_; }
	double Value(double x) { return x * x - a; }
	double Deriv(double x) { return 2 * x; }
};
class CouponBond
{
private:
	double C, F, T;
public:
	CouponBond(double C_, double F_,double T_) {
		C = C_;
		F = F_;
		T = T_;
	}
	double Value(double y) {
		double P = 0;
		for (int i = 1; i <= T; i++) {
			P = P + C * exp(-y * i);
		}
		P = P + F * exp(-y * T);
		return P;
	}
	double Deriv(double y) {
		double P = 0;
		for (int i = 1; i <= T; i++) {
			P = P + C * exp(-y * T)*(-i);
		}
		P = P + F * exp(-y * T)*(-T);
		return P;
	}
};

int main()
{
	int i = 0;
	double F = 100.0;
	double T = 3.0;
	double C = 1.2;
	double P = 98.56;

	double Acc = 0.0001;
	double LEnd = 0.0;
	double REnd = 1.0;
	double Guess = 0.2;
	CouponBond Bond(C, F, T);
	cout << setiosflags(ios::fixed) << setprecision(4);
	cout << "F = " << F << endl;
	cout << "T = " << T << endl;
	cout << "coupons:" << endl;
	for ( i = 0; i < T; i++) {
		cout << "C" << i << " = " << C << endl;
	}
	cout << "tenors:" << endl;
	for (i = 0; i < T; i++) {
		cout << "T" << i << " = " << double (i + 1) << endl;
	}
	cout << "P = " << P << endl<<endl;
	cout << "Yield by bisection method: " << SolveByBisect(&Bond, P, LEnd, REnd, Acc) << endl;
	cout << "Yield by Newton-Raphson: " << SolveByNR(&Bond, P, Guess, Acc) << endl;
	system("pause");
	return 0;
}

