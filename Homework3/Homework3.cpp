#include "stdafx.h"
#include <iostream>
#include <cmath>
#include "DefInt.h"
#include <cstring>
using namespace std;

double f(double x) { return x * x*x - x * x + 1; }

int main()
{
	//double a, b;
	//double *f(double x);
	/*cout << "a:" << endl;
	cin >> a;
	cout << "b:" << endl;
	cin >> b;
	cout << "function:" << endl;
	cin >> *f;
	*/
	/*
	cout << "Enter a number" << endl;
	double x = 0.0;
	cin >> x;
	cout << f(x) << endl;
	*/
	DefInt MyInt(1.0, 2.0, f);
	int n = 1000000;
	cout << "By Trapzoid: " << MyInt.ByTrapzoid(n) << endl;
	cout << "By Simpson: " << MyInt.BySimpson() << endl;
	cout << "By Midpoint: " << MyInt.ByMidpoint(n) << endl;
	system("pause");
	return 0;
}