#include "RPN.hpp"
#include <vector>
#include <sstream>
#include <stdexcept>
#include <cctype>

RPN::RPN() {}

RPN::RPN(const RPN &other)
{
	(void)other;
}

RPN &RPN::operator=(const RPN &other)
{
	(void)other;
	return *this;
}

RPN::~RPN() {}

int RPN::evaluate(const std::string &expression) const
{
	std::vector<int> values;
	std::istringstream iss(expression);
	std::string token;

	while (iss >> token)
	{
		if (token.size() == 1 && std::isdigit(static_cast<unsigned char>(token[0])))
		{
			values.push_back(token[0] - '0');
			continue;
		}

		if (token.size() != 1 || (token[0] != '+' && token[0] != '-' && token[0] != '*' && token[0] != '/'))
			throw std::runtime_error("Error");

		if (values.size() < 2)
			throw std::runtime_error("Error");

		int b = values.back();
		values.pop_back();
		int a = values.back();
		values.pop_back();
		int result = 0;

		switch (token[0])
		{
			case '+':
				result = a + b;
				break;
			case '-':
				result = a - b;
				break;
			case '*':
				result = a * b;
				break;
			case '/':
				if (b == 0)
					throw std::runtime_error("Error");
				result = a / b;
				break;
		}

		values.push_back(result);
	}

	if (values.size() != 1)
		throw std::runtime_error("Error");

	return values.back();
}
