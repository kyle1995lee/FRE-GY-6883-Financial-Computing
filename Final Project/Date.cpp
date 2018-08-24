#include "Date.h"


bool Date::operator>(const Date& obj) const {
	if (year > obj.year) {
		return true;
	}
	else if (year == obj.year) {
		if (month > obj.month) {
			return true;
		}
		else if (month == obj.month) {
			return (day > obj.day);
		}
	}
	return false;
}

bool Date::operator<(const Date& obj) const {
	if (year < obj.year) {
		return true;
	}
	else if (year == obj.year) {
		if (month < obj.month) {
			return true;
		}
		else if (month == obj.month) {
			return (day < obj.day);
		}
	}
	return false;
}

bool Date::operator==(const Date& obj) const {
	if (year == obj.year && month == obj.month && day == obj.day) {
		return true;
	}
	return false;
}

bool Date::operator<=(const Date & obj) const {
	return ((*this) < obj || (*this) == obj);
}

bool Date::operator>=(const Date & obj) const {
	return ((*this) > obj || (*this) == obj);
}


const Date& Date::operator=(const Date& obj) {
	year = obj.year;
	month = obj.month;
	day = obj.day;
	return *this;
}

int Date::GetYear() const {
	return year;
}
int Date::GetMonth() const {
	return month;
}
int Date::GetDay() const {
	return day;
}

void Date::SetYear(int y) {
	year = y;
}
void Date::SetMonth(int m) {
	month = m;
}
void Date::SetDay(int d) {
	day = d;
}
std::string Date::asString() {
	return std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day);
}