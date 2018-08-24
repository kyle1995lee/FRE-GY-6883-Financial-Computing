#include "BinLattice02.h"
#include "BinModel02.h"
#include "Options09.h"
#include <iostream>
#include <fstream>
using namespace std;
int main()
{
	BinModel Model;
	if (Model.GetInputData() == 1) return 1;

	ofstream fout;
	fout.open("Results.txt");

	BinLattice<double> PriceTree;
	BinLattice<double> XTree;
	BinLattice<double> YTree;

	fout << "S0 = " << Model.GetS0() << endl
		<< "U = " << Model.GetU() << endl
		<< "D = " << Model.GetD() << endl
		<< "R = " << Model.GetR() << endl;

	Call Option1;
	Option1.GetInputData();

	fout << "N = " << Option1.GetN() << endl
		<< "K = " << Option1.GetK() << endl;

	fout << "European call prices by PriceByCRR:"
		<< Option1.PriceByCRR(Model) << endl << endl;

	fout << "European call prices by PriceByCRRHW6:"
		<< Option1.PriceByCRRHW6(Model, PriceTree, XTree, YTree)
		<< endl << endl;
	fout << "Stock positions in replicating strategy:" << endl << endl;
	XTree.Display(fout);//fout
	fout << "Money market account positions in replicating strategy:" << endl << endl;
	YTree.Display(fout);//fout

	Put Option2;
	Option2.GetInputData();

	fout << "N = " << Option2.GetN() << endl
		<< "K = " << Option2.GetK() << endl;

	fout << "European put prices by PriceByCRR:"
		<< Option2.PriceByCRR(Model) << endl << endl;

	fout << "European put prices by PriceByCRRHW6:"
		<< Option2.PriceByCRRHW6(Model, PriceTree, XTree, YTree)
		<< endl << endl;
	fout << "Stock positions in replicating strategy:" << endl << endl;
	XTree.Display(fout);//fout
	fout << "Money market account positions in replicating strategy:" << endl << endl;
	YTree.Display(fout);//fout

	fout.close();
	system("pause");
	return 0;
}



