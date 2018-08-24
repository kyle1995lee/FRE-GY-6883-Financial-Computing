#pragma once
#include <vector>
#include "Share.h"
#include "group.h"
#include <stdlib.h>
#include "ExcelDriver\VectorsAndMatrices\Vector.hpp"
#include "ExcelDriver\ExcelDriver.hpp"
#include "ExcelDriver\ExcelMechanisms.hpp"
#include "ExcelDriver\VectorsAndMatrices\Matrix.hpp"

class Boost {
private:
	std::vector<Group> ThreeGroups = std::vector<Group>(3);
	double threshold = 5;
	int times = 30;
	Matrix<Vector<double, long>, long> AAR_CAAR = Matrix<Vector<double, long>, long>(3, 2);
public:
	Boost() {
		for (long r = AAR_CAAR.MinRowIndex(); r <= AAR_CAAR.MaxRowIndex(); ++r) {
			for (long col = AAR_CAAR.MinColumnIndex(); col <= AAR_CAAR.MaxColumnIndex(); ++col) {
				AAR_CAAR(r, col) = Vector<double, long>(90);
			}
		}
	};
	Boost(double thre, int t) {
		threshold = thre;
		times = t;
		for (long r = AAR_CAAR.MinRowIndex(); r <= AAR_CAAR.MaxRowIndex(); ++r) {
			for (long col = AAR_CAAR.MinColumnIndex(); col <= AAR_CAAR.MaxColumnIndex(); ++col) {
				AAR_CAAR(r, col) = Vector<double, long>(90);
			}
		}
	};
	~Boost() {};
	Vector<double, long> GetAAR_CAAR(long row, long col);
	std::list< Vector<double, long> > GetAARlist();
	std::list< Vector<double, long> > GetCAARlist();
	const double GetThreshold();
	const int GetResampleTimes();
	void SetThreshold(double thre);
	void SetResampleTimes(int t);
	const Group& GetGroup(int index);
	Group Sampling(const Group& group);
	void WriteGroups(const std::map<std::string, Stock>& allstocks_);
	void Bootstrap(const Share& SPY_);
};