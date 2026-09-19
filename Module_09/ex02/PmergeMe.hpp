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

		std::vector<int> sortVector(std::vector<int> seq) const;
		std::deque<int> sortDeque(std::deque<int> seq) const;

	private:
		std::vector<size_t> jacobsthalInsertionOrder(size_t n) const;

		std::vector<size_t> fordJohnsonVector(const std::vector<int> &values, std::vector<size_t> indices) const;
		size_t lowerBoundVector(const std::vector<int> &values, const std::vector<size_t> &chain, size_t hi, int val) const;

		std::deque<size_t> fordJohnsonDeque(const std::deque<int> &values, std::deque<size_t> indices) const;
		size_t lowerBoundDeque(const std::deque<int> &values, const std::deque<size_t> &chain, size_t hi, int val) const;
};

#endif
