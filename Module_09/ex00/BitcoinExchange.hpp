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
		std::map<std::string, float> _database;

		bool isValidDate(const std::string &date) const;
		bool splitLine(const std::string &line, char sep, std::string &left, std::string &right) const;
		float findRate(const std::string &date) const;
};

#endif
