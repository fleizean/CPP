#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <cctype>
#include <iomanip>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
	: _database(other._database)
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		_database = other._database;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::splitLine(const std::string &line, char sep, std::string &left, std::string &right) const
{
	size_t pos = line.find(sep);
	if (pos == std::string::npos)
		return false;

	left = line.substr(0, pos);
	right = line.substr(pos + 1);

	while (!left.empty() && (left[left.size() - 1] == ' ' || left[left.size() - 1] == '\t'))
		left.erase(left.size() - 1);
	while (!right.empty() && (right[0] == ' ' || right[0] == '\t'))
		right.erase(0, 1);
	while (!right.empty() && (right[right.size() - 1] == ' ' || right[right.size() - 1] == '\t' || right[right.size() - 1] == '\r'))
		right.erase(right.size() - 1);

	return true;
}

bool BitcoinExchange::isHeader(const std::string &line) const
{
	std::string left, right;

	if (splitLine(line, '|', left, right))
		return (left == "date");
	if (splitLine(line, ',', left, right))
		return (left == "date");
	return false;
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	for (size_t i = 0; i < date.size(); ++i)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(static_cast<unsigned char>(date[i])))
			return false;
	}

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (year < 1000 || month < 1 || month > 12 || day < 1)
		return false;

	int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	bool leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
	if (month == 2 && leap)
		daysInMonth[1] = 29;

	if (day > daysInMonth[month - 1])
		return false;

	return true;
}

void BitcoinExchange::loadDatabase(const std::string &path)
{
	std::ifstream file(path.c_str());
	if (!file.is_open())
		throw std::runtime_error("could not open file");

	std::string line;
	bool first = true;

	while (std::getline(file, line))
	{
		if (line.empty())
			continue;
		if (first)
		{
			first = false;
			if (isHeader(line)) // "date,exchange_rate"
				continue;
		}

		std::string date, rateStr;
		if (!splitLine(line, ',', date, rateStr))
			continue;
		if (!isValidDate(date))
			continue;

		double rate = std::atof(rateStr.c_str());
		_database[date] = rate;
	}
}

double BitcoinExchange::findRate(const std::string &date) const
{
	std::map<std::string, double>::const_iterator it = _database.lower_bound(date);

	if (it != _database.end() && it->first == date)
		return it->second;
	if (it == _database.begin())
		throw std::runtime_error("no earlier date available");

	--it;
	return it->second;
}

void BitcoinExchange::processInput(const std::string &path) const
{
	std::ifstream file(path.c_str());
	if (!file.is_open())
		throw std::runtime_error("could not open file");

	std::string line;
	bool first = true;

	std::cout << std::setprecision(10);

	while (std::getline(file, line))
	{
		if (line.empty())
			continue;
		if (first)
		{
			first = false;
			if (isHeader(line)) // "date | value"
				continue;
		}

		std::string date, valueStr;
		if (!splitLine(line, '|', date, valueStr) || !isValidDate(date))
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::istringstream iss(valueStr);
		double value;
		char extra;
		if (!(iss >> value) || (iss >> extra))
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}

		if (value < 0)
		{
			std::cout << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000)
		{
			std::cout << "Error: too large a number." << std::endl;
			continue;
		}

		try
		{
			double rate = findRate(date);
			std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
		}
		catch (const std::exception &e)
		{
			std::cout << "Error: bad input => " << line << std::endl;
		}
	}
}
