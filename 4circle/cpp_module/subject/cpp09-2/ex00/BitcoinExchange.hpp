#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <fstream>
#include <string>

struct Date
{
	int year, month, day;
	Date(int y, int m, int d) : year(y), month(m), day(d) {}

	bool operator<(const Date &other) const;
};

class BitcoinExchange
{
public:
	BitcoinExchange();
	BitcoinExchange(std::string path);
	BitcoinExchange(const BitcoinExchange &obj);
	BitcoinExchange &operator=(const BitcoinExchange &obj);
	~BitcoinExchange();
	void memorizeData();
	void processInput();

private:
	std::string path;
	std::map<Date, double> dbMap;
	double calculatePrice(Date originDate);
};

#endif