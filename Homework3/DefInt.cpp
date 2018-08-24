#include "stdafx.h"
#include<iostream>
#include<cmath>
#include "DefInt.h"

DefInt::DefInt(double a1, double b1, double (*f1)(double x)){
	a = a1;
	b = b1;
	f = f1;
};
double DefInt::ByTrapzoid(int n) {
	double len;
	len = (b - a) / n;
	double sum;
	sum = f(a);
	int i;
	for (i = 1; i < n; i++) {
		sum = sum + 2 * f(a + i * len);
	}
	sum = sum + f(b);
	return ((b - a)*sum) / (2 * n);
}

double DefInt::BySimpson() {
	return ((b - a)*(f(a) + 4*f((a + b) / 2) + f(b))) / 6;
}

double DefInt::ByMidpoint(int n) {
	double sum = 0;
	double len = (b - a) / n;
	int i;
	for (i = 0; i <= n; i++) {
		sum = sum + f(a + len * (i - 0.5));
	}
	return ((b - a)*sum) / n;
}