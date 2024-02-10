#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(std::string path)
{
	this->path = path;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &obj)
{
	this->path = obj.path;
	this->dbMap = obj.dbMap;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &obj)
{
	if (this == &obj)
		return *this;
	this->path = obj.path;
	this->dbMap = obj.dbMap;
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

static void exceptionWithErrMsg(std::string errMsg)
{
	throw std::runtime_error(errMsg);
}

static std::string trim(const std::string &str)
{
	size_t first = str.find_first_not_of(' ');
	size_t last = str.find_last_not_of(' ');
	if (first == std::string::npos || last == std::string::npos)
		return "";
	return str.substr(first, last - first + 1);
}

static double myStrToD(std::string &str)
{
	std::string originString = str;
	char *end;
	double num = std::strtod(str.c_str(), &end);
	if (*end != '\0')
		exceptionWithErrMsg("BAD INPUT => " + originString);
	if (num > std::numeric_limits<int>::max())
		exceptionWithErrMsg("NUMBER IS TOO LARGE");
	if (num < 0)
		exceptionWithErrMsg("NOT A POSIVIVE NUNBER");
	return num;
}

static bool isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

static bool isValidDate(int year, int month, int day)
{
	if (year < 1 || year > 4000 || month < 1 || month > 12 || day < 1)
	{
		return false;
	}

	int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (isLeapYear(year))
	{
		daysInMonth[2] = 29;
	}

	return day <= daysInMonth[month];
}

static int getDaysFromStart(int year, int month, int day)
{
	int monthDays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int days = day;

	for (int y = 1; y < year; ++y)
		days += isLeapYear(y) ? 366 : 365;

	for (int m = 1; m < month; ++m)
	{
		days += monthDays[m];
		if (m == 2 && isLeapYear(year))
			days += 1;
	}

	return days;
}

static int myAtoi(const std::string &str)
{
	char *end;
	long num = std::strtol(str.c_str(), &end, 10);
	if (*end != '\0' || errno == ERANGE)
		new std::exception();
	if (num > std::numeric_limits<int>::max())
		new std::exception();
	return static_cast<int>(num);
}

bool Date::operator<(const Date &other) const
{
	if (year != other.year)
		return year < other.year;
	if (month != other.month)
		return month < other.month;
	return day < other.day;
}

static int extractDateComponent(std::string &dateString)
{
	std::string originString = dateString;
	size_t idx = dateString.find("-");
	if (idx == std::string::npos)
		exceptionWithErrMsg("BAD INPUT => " + originString);
	std::string componentString = dateString.substr(0, idx);
	dateString = dateString.substr(idx + 1);
	return myAtoi(componentString);
}

static Date getDate(std::string dateString)
{
	std::string originString = dateString;
	int year;
	int month;
	int day;
	try
	{
		year = extractDateComponent(dateString);
		month = extractDateComponent(dateString);
		day = myAtoi(dateString);
	}
	catch (std::exception &e)
	{
		exceptionWithErrMsg("BAD INPUT => " + originString);
	}
	if (!isValidDate(year, month, day))
		exceptionWithErrMsg("BAD INPUT => " + originString);
	return Date(year, month, day);
}

static double getPrice(std::string &priceString)
{
	std::string originString = priceString;
	if (priceString.find(",") != std::string::npos)
		exceptionWithErrMsg("BAD INPUT => " + originString);
	return myStrToD(priceString);
}

void BitcoinExchange::memorizeData()
{
	std::ifstream dbFile("data.csv");
	if (!dbFile.is_open())
		exceptionWithErrMsg("DB FILE NOT OPEN");

	std::string line;
	std::getline(dbFile, line);
	while (std::getline(dbFile, line))
	{
		size_t idx = line.find(",");
		if (idx == std::string::npos)
			exceptionWithErrMsg("DB FILE NEED DELIMITER");
		std::string dateString = line.substr(0, idx);
		Date date = getDate(dateString);
		std::string priceString = line.substr(idx + 1);
		double price = getPrice(priceString);
		dbMap[date] = price;
	}
	dbFile.close();
}

double BitcoinExchange::calculatePrice(Date originDate)
{
	double price = 0;
	int minDiffDays = -1;
	int originDays = getDaysFromStart(originDate.year, originDate.month, originDate.day);
	for (std::map<Date, double>::iterator it = dbMap.begin(); it != dbMap.end(); ++it)
	{
		Date curDate = it->first;
		double curPrice = it->second;
		int curDays = getDaysFromStart(curDate.year, curDate.month, curDate.day);
		int diff = curDays - originDays;
		if (curDays > originDays)
			continue;
		if (diff < minDiffDays || minDiffDays < 0)
		{
			minDiffDays = diff;
			price = curPrice;
		}
	}
	return price;
}

void BitcoinExchange::processInput()
{
	std::ifstream dbFile(path);
	if (!dbFile.is_open())
		exceptionWithErrMsg("INPUT FILE NOT OPEN");

	std::string line;
	while (std::getline(dbFile, line))
	{
		try
		{
			size_t idx = line.find(" | ");
			if (idx == std::string::npos)
				exceptionWithErrMsg("BAD INPUT => " + line);
			std::string dateString = trim(line.substr(0, idx));
			Date date = getDate(dateString);
			std::string priceString = trim(line.substr(idx + 3));
			double value = getPrice(priceString);
			if (value <= 0 || value >= 1000)
				exceptionWithErrMsg("BAD INPUT => " + priceString);
			double price = calculatePrice(date);
			std::cout << dateString << " => " << value << " = ";
			std::cout << price * value << std::endl;
		}
		catch (const std::runtime_error &e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}
	}
	dbFile.close();
}