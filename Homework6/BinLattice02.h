#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
template<typename Type> class BinLattice
{
private:
	int N;
	vector< vector<Type> > Lattice;
public:
	void SetN(int N_)
	{
		N = N_;
		Lattice.resize(N + 1);
		for (int n = 0; n <= N; n++) Lattice[n].resize(n + 1);
	}
	void SetNode(int n, int i, Type x) { Lattice[n][i] = x; }
	Type GetNode(int n, int i) { return Lattice[n][i]; }
	void Display()
	{
		cout << setiosflags(ios::fixed) << setprecision(3);
		for (int n = 0; n <= N; n++)
		{
			for (int i = 0; i <= n; i++)
				cout << setw(7) << GetNode(n, i);
			cout << endl;
		}
		cout << endl;
	}
	void Display(ofstream &fout)
	{
		fout << setiosflags(ios::fixed) << setprecision(6);
		for (int n = 0; n <= N; n++)
		{
			for (int i = 0; i <= n; i++)
				fout << setw(15) << GetNode(n, i);
			fout << endl;
		}
		fout << endl;
	}
};