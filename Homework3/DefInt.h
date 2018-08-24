#ifndef DefInt_h
#define DefInt_h

class DefInt {
private:
	double a;
	double b;
	double (*f)(double x);

public:
	DefInt(double a1, double b1, double (*f1)(double x));
	double ByTrapzoid(int n);
	double BySimpson();
	double ByMidpoint(int n);
};

#endif
#pragma once
