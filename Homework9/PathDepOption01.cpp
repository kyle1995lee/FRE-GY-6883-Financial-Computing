#include "PathDepOption01.h"
#include <cmath>
double PathDepOption::PriceByMC(BSModel Model, long N)
{
	double H = 0.0;
	SamplePath S(m);
	for (long i = 0; i<N; i++)
	{
		Model.GenerateSamplePath(T, m, S);
		H = (i / (i + 1.0))*H + Payoff(S) / (i + 1.0);
	}
	return exp(-Model.r*T)*H;
}
double ArthmAsianCall::Payoff(SamplePath& S)
{
	double Ave = 0.0;
	for (int k = 0; k<m; k++) Ave = (k / (k + 1.0))*Ave + S[k] / (k + 1.0);
	if (Ave<K) return 0.0;
	return Ave - K;
}
double EurCall::Payoff(SamplePath& S) {
	if (S.back() > K) {
		return S.back() - K;
	}
	else {
		return 0;
	}
}
double EurPut::Payoff(SamplePath& S) {
	if (S.back() < K) {
		return  K - S.back() ;
	}
	else {
		return 0;
	}
}

