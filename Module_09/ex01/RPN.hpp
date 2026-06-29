#ifndef RPN_HPP
#define RPN_HPP

#include <string>

class RPN
{
	public:
		RPN();
		RPN(const RPN &other);
		RPN &operator=(const RPN &other);
		~RPN();

		int evaluate(const std::string &expression) const;
};

#endif
