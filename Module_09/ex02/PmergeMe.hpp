#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <cstddef>

class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe &operator=(const PmergeMe &other);
		~PmergeMe();

		void run(int argc, char **argv) const;

	private:
		std::vector<int> parseArgs(int argc, char **argv) const;
		std::deque<int> parseArgsDeque(int argc, char **argv) const;

		std::vector<int> sortVector(std::vector<int> seq) const;
		std::deque<int> sortDeque(std::deque<int> seq) const;

		std::vector<size_t> fordJohnsonVector(const std::vector<int> &values, std::vector<size_t> indices) const;
		std::deque<size_t> fordJohnsonDeque(const std::deque<int> &values, std::deque<size_t> indices) const;

		std::vector<size_t> jacobsthalInsertionOrder(size_t n) const;
};

#endif
