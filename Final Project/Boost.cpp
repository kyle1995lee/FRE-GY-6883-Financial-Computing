#include "Boost.h"
#include <algorithm>
#include <random>
#include <chrono>

Vector<double, long> Boost::GetAAR_CAAR(long row, long col) {
	return AAR_CAAR(row, col);
}
std::list< Vector<double, long> > Boost::GetAARlist() {
	std::list<Vector<double, long> > aar_list;
	for (int r = AAR_CAAR.MinRowIndex(); r <= AAR_CAAR.MaxRowIndex(); ++r) {
		aar_list.push_back(AAR_CAAR(r, 1));
	}
	return aar_list;
}

std::list< Vector<double, long> > Boost::GetCAARlist() {
	std::list<Vector<double, long> > caar_list;
	for (int r = AAR_CAAR.MinRowIndex(); r <= AAR_CAAR.MaxRowIndex(); ++r) {
		caar_list.push_back(AAR_CAAR(r, 2));
	}
	return caar_list;
}

const double Boost::GetThreshold() {
	return threshold;
}

const int Boost::GetResampleTimes() {
	return times;
}
void Boost::SetThreshold(double thre) {
	threshold = thre;
}
void Boost::SetResampleTimes(int t) {
	times = t;
}
const Group& Boost::GetGroup(int index) {
	return ThreeGroups[index];
}
Group Boost::Sampling(const Group& group) {
	Group sampled;
	std::vector<std::string> keys = group.Gettickers();

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(keys.begin(), keys.end(), std::default_random_engine(seed));
	for (int i = 0; i < 60; ++i) {
		sampled.addnew(group.GetStock(keys[i]));
	}
	return sampled;
}
void Boost::WriteGroups(const std::map<std::string, Stock>& allstocks_) {
	for (auto i = allstocks_.begin(); i != allstocks_.end(); i++) {
		if ((i->second).GetSurprise() > threshold) {
			ThreeGroups[0].addnew(i->second);
		}
		else if (i->second.GetSurprise() < -threshold) {
			ThreeGroups[2].addnew(i->second);
		}
		else {
			ThreeGroups[1].addnew(i->second);
		}
	}
}
void  Boost::Bootstrap(const Share& SPY) {
	cout << "Bootstraping initialized"<<endl 
		 << "Resampling might be called if outlier AR detected, which might takes a longer time." << endl;
	for (int i = 0; i < times; ++i) {
		for (int j = 1; j <= 3; ++j) {
			Group sampled = Sampling(ThreeGroups[j - 1]);
			while (!sampled.Computing(SPY)) {
				sampled = Sampling(ThreeGroups[j - 1]);
			}
			std::vector<double> AAR = sampled.GetAAR();
			std::vector<double> CAAR = sampled.GetCAAR();
			for (int k = 1; k <= 90; k++) {

				AAR_CAAR(j, 1)[k] = (AAR_CAAR(j, 1)[k] * i + AAR[k - 1]) / (i + 1);
				AAR_CAAR(j, 2)[k] = (AAR_CAAR(j, 2)[k] * i + CAAR[k - 1]) / (i + 1);

			}
		}

		std::cout << "Bootstrap Time " << i + 1 << " Completed" << std::endl;
	}
}