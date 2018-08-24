#pragma once

#include<map>
#include<string>
#include<vector>
#include "Share.h"

class Group {
private:
	std::multimap<std::string, Stock> stocks;
	std::vector<std::string> tickers;
	std::vector<double> AAR = std::vector<double>(90);
	std::vector<double> CAAR = std::vector<double>(90);
public:
	Group() {};
	Group(const Group& group_) :stocks(group_.stocks), tickers(group_.tickers), AAR(group_.AAR), CAAR(group_.CAAR) {}
	~Group() {};
	const std::vector<double>& GetAAR() const;
	const std::vector<double>& GetCAAR() const;
	const Stock& GetStock(std::string ticker) const;
	const std::vector<std::string>& Gettickers() const;
	bool Computing(const Share& SPY);
	void addnew(const Stock&s);
};