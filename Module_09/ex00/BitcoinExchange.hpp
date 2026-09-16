#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		void loadDatabase(const std::string &path);
		void processInput(const std::string &path) const;

	private:
		std::map<std::string, double> _database;

		bool isHeader(const std::string &line) const;
		bool isValidDate(const std::string &date) const;
		bool splitLine(const std::string &line, char sep, std::string &left, std::string &right) const;
		double findRate(const std::string &date) const;
};

#endif
