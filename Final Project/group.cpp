#include "group.h"
#include <iostream>;
const std::vector<double>& Group::GetAAR() const {
	return AAR;
}

const std::vector<double>& Group::GetCAAR() const {
	return CAAR;
}


const Stock& Group::GetStock(std::string ticker) const {
	auto i = stocks.find(ticker);
	return i->second;
}

bool Group::Computing(const Share& SPY) {
	int count = 0;

	for (auto i = stocks.begin(); i != stocks.end(); ++i) {

		Share sliced = SPY.slice(i->second.GetStartDate(), i->second.GetEndDate());
		int t = 0;
		for (auto j = i->second.GetReturn().begin(); j != i->second.GetReturn().end(); j++) {
			
			double AR = j->second - sliced.GetReturn().find(j->first)->second;
			
			if (AR > 1000) { return false; }
			AAR[t] = (AAR[t] * count + AR) / (count + 1);

			t++;

		}

		count++;

	}

	CAAR[0] = AAR[0];

	for (int i = 1; i < 90; i++) {
		CAAR[i] = CAAR[i - 1] + AAR[i];
	}
	return true;
}

const std::vector<std::string>& Group::Gettickers() const {
	return tickers;
}

void Group::addnew(const Stock& s) {
	stocks.insert(std::pair<std::string, Stock>(s.GetTicker(), s));
	tickers.push_back(s.GetTicker());
}