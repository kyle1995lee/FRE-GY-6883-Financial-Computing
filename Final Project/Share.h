#pragma once
#ifndef Share_h
#define Share_h
#include "Date.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>


class Share {
protected:
	std::string ticker;
	Date start_date;
	Date end_date;
	std::map<Date, double> price;
	std::map<Date, double> ret;

public:
	Share() {}
	Share(std::string ticker_, Date s, Date e, std::map<Date, double> price_, std::map<Date, double> ret_);
	Share(const Share& Share) :ticker(Share.ticker), start_date(Share.start_date), end_date(Share.end_date), price(Share.price), ret(Share.ret) {}
	~Share() {}
	const Date& GetStartDate() const;
	const Date& GetEndDate() const;
	std::string GetTicker() const;
	const std::map<Date, double>& GetPrice();
	const std::map<Date, double>& GetReturn();

	void SetStartDate(Date ds) { start_date = ds; }
	void SetEndDate(Date de) { end_date = de; }
	void SetTicker(std::string Ticker) { ticker = Ticker; }
	void SetPrice(std::map<Date, double> Price) { price = Price; }
	void SetReturn(std::map<Date, double> Return) { ret = Return; };
	Share slice(Date start, Date end) const;
};

class Stock :public Share {
private:
	Date eps_date;
	double surprise;

public:
	Stock() {}
	Stock(std::string ticker_, Date s, Date e, Date report, std::map<Date, double> price_, std::map<Date, double> ret_, double surprise_);
	Stock(const Stock& stock);
	~Stock() {}
	const Date& GetEpsDate();
	double GetSurprise() const { return surprise; }
	Date GetReportDate() const { return eps_date; }
	void SetSurprise(double Surprise) { surprise = Surprise; }
	void SetReportDate(Date Eps_date) { eps_date = Eps_date; }
	void Display();
};
#endif