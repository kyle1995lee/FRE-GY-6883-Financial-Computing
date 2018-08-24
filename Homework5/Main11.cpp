#include "stdafx.h"
#include "BinModel02.h"
#include "Options06.h"
#include "DoubDigitOpt.h"
#include "Strangle.h"
#include "Butterfly.h"

#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	BinModel Model;
	if (Model.GetInputData() == 1)
		return 1;
	Call Option1;
	Option1.GetInputData();
	cout << "European call option price = " << Option1.PriceByCRR(Model) << endl << endl;

	Put Option2;
	Option2.GetInputData();
	cout << "European put option price = " << Option2.PriceByCRR(Model) << endl << endl;
	DoubDigitOpt Option3;
	Option3.GetInputData();
	cout << "European double-digital option price = " << Option3.PriceByCRR(Model) << endl << endl;

	Strangle Option4;
	Option4.GetInputData();
	cout << "European Strangle Spread option price = " << Option4.PriceByCRR(Model) << endl << endl;
	

	Butterfly Option5;
	Option5.GetInputData();
	cout << "European Strangle Spread option price = " << Option5.PriceByCRR(Model) << endl << endl;
	
	system("pause");
	return 0;
}
