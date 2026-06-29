#include "PmergeMe.hpp"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cctype>
#include <climits>
#include <ctime>
#include <string>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other)
{
	(void)other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	(void)other;
	return *this;
}

PmergeMe::~PmergeMe() {}

std::vector<int> PmergeMe::parseArgs(int argc, char **argv) const
{
	std::vector<int> numbers;

	for (int i = 1; i < argc; ++i)
	{
		std::string token(argv[i]);
		size_t start = 0;

		if (!token.empty() && token[0] == '+')
			start = 1;
		if (start >= token.size())
			throw std::runtime_error("Error");

		for (size_t j = start; j < token.size(); ++j)
		{
			if (!std::isdigit(static_cast<unsigned char>(token[j])))
				throw std::runtime_error("Error");
		}

		long value = std::strtol(token.c_str(), NULL, 10);
		if (value < 0 || value > INT_MAX)
			throw std::runtime_error("Error");

		numbers.push_back(static_cast<int>(value));
	}

	if (numbers.empty())
		throw std::runtime_error("Error");

	return numbers;
}

std::vector<size_t> PmergeMe::jacobsthalInsertionOrder(size_t n) const
{
	std::vector<size_t> order;
	if (n <= 1)
		return order;

	std::vector<size_t> jacobsthal;
	jacobsthal.push_back(0);
	jacobsthal.push_back(1);
	while (jacobsthal.back() < n)
		jacobsthal.push_back(jacobsthal[jacobsthal.size() - 1] + 2 * jacobsthal[jacobsthal.size() - 2]);

	std::vector<bool> used(n, false);
	used[0] = true;

	for (size_t i = 2; i < jacobsthal.size(); ++i)
	{
		size_t hi = jacobsthal[i];
		size_t lo = jacobsthal[i - 1];
		if (hi > n - 1)
			hi = n - 1;
		for (size_t j = hi; j > lo; --j)
		{
			if (!used[j])
			{
				order.push_back(j);
				used[j] = true;
			}
		}
	}

	for (size_t j = 0; j < n; ++j)
	{
		if (!used[j])
		{
			order.push_back(j);
			used[j] = true;
		}
	}

	return order;
}

/* ---- vector implementation ---- */

std::vector<size_t> PmergeMe::fordJohnsonVector(const std::vector<int> &values, std::vector<size_t> indices) const
{
	if (indices.size() <= 1)
		return indices;

	bool hasStray = (indices.size() % 2 != 0);
	size_t strayIdx = 0;
	if (hasStray)
	{
		strayIdx = indices.back();
		indices.pop_back();
	}

	std::vector<size_t> bigIdx, smallIdx;
	for (size_t i = 0; i < indices.size(); i += 2)
	{
		size_t i1 = indices[i], i2 = indices[i + 1];
		if (values[i1] > values[i2])
		{
			bigIdx.push_back(i1);
			smallIdx.push_back(i2);
		}
		else
		{
			bigIdx.push_back(i2);
			smallIdx.push_back(i1);
		}
	}

	std::vector<size_t> sortedBig = fordJohnsonVector(values, bigIdx);

	std::vector<size_t> pend;
	for (size_t i = 0; i < sortedBig.size(); ++i)
	{
		for (size_t j = 0; j < bigIdx.size(); ++j)
		{
			if (bigIdx[j] == sortedBig[i])
			{
				pend.push_back(smallIdx[j]);
				break;
			}
		}
	}

	std::vector<size_t> result(sortedBig);
	if (!pend.empty())
		result.insert(result.begin(), pend[0]);

	std::vector<size_t> order = jacobsthalInsertionOrder(pend.size());
	for (size_t k = 0; k < order.size(); ++k)
	{
		size_t valIdx = pend[order[k]];
		int val = values[valIdx];

		std::vector<size_t>::iterator pos = result.begin();
		while (pos != result.end() && values[*pos] < val)
			++pos;
		result.insert(pos, valIdx);
	}

	if (hasStray)
	{
		int val = values[strayIdx];
		std::vector<size_t>::iterator pos = result.begin();
		while (pos != result.end() && values[*pos] < val)
			++pos;
		result.insert(pos, strayIdx);
	}

	return result;
}

std::vector<int> PmergeMe::sortVector(std::vector<int> seq) const
{
	std::vector<size_t> indices;
	for (size_t i = 0; i < seq.size(); ++i)
		indices.push_back(i);

	std::vector<size_t> sortedIdx = fordJohnsonVector(seq, indices);

	std::vector<int> result;
	for (size_t i = 0; i < sortedIdx.size(); ++i)
		result.push_back(seq[sortedIdx[i]]);

	return result;
}

/* ---- deque implementation ---- */

std::deque<size_t> PmergeMe::fordJohnsonDeque(const std::deque<int> &values, std::deque<size_t> indices) const
{
	if (indices.size() <= 1)
		return indices;

	bool hasStray = (indices.size() % 2 != 0);
	size_t strayIdx = 0;
	if (hasStray)
	{
		strayIdx = indices.back();
		indices.pop_back();
	}

	std::deque<size_t> bigIdx, smallIdx;
	for (size_t i = 0; i < indices.size(); i += 2)
	{
		size_t i1 = indices[i], i2 = indices[i + 1];
		if (values[i1] > values[i2])
		{
			bigIdx.push_back(i1);
			smallIdx.push_back(i2);
		}
		else
		{
			bigIdx.push_back(i2);
			smallIdx.push_back(i1);
		}
	}

	std::deque<size_t> sortedBig = fordJohnsonDeque(values, bigIdx);

	std::deque<size_t> pend;
	for (size_t i = 0; i < sortedBig.size(); ++i)
	{
		for (size_t j = 0; j < bigIdx.size(); ++j)
		{
			if (bigIdx[j] == sortedBig[i])
			{
				pend.push_back(smallIdx[j]);
				break;
			}
		}
	}

	std::deque<size_t> result(sortedBig);
	if (!pend.empty())
		result.insert(result.begin(), pend[0]);

	std::vector<size_t> order = jacobsthalInsertionOrder(pend.size());
	for (size_t k = 0; k < order.size(); ++k)
	{
		size_t valIdx = pend[order[k]];
		int val = values[valIdx];

		std::deque<size_t>::iterator pos = result.begin();
		while (pos != result.end() && values[*pos] < val)
			++pos;
		result.insert(pos, valIdx);
	}

	if (hasStray)
	{
		int val = values[strayIdx];
		std::deque<size_t>::iterator pos = result.begin();
		while (pos != result.end() && values[*pos] < val)
			++pos;
		result.insert(pos, strayIdx);
	}

	return result;
}

std::deque<int> PmergeMe::sortDeque(std::deque<int> seq) const
{
	std::deque<size_t> indices;
	for (size_t i = 0; i < seq.size(); ++i)
		indices.push_back(i);

	std::deque<size_t> sortedIdx = fordJohnsonDeque(seq, indices);

	std::deque<int> result;
	for (size_t i = 0; i < sortedIdx.size(); ++i)
		result.push_back(seq[sortedIdx[i]]);

	return result;
}

/* ---- run ---- */

void PmergeMe::run(int argc, char **argv) const
{
	std::vector<int> numbers = parseArgs(argc, argv);
	std::deque<int> dq(numbers.begin(), numbers.end());

	std::cout << "Before: ";
	for (size_t i = 0; i < numbers.size(); ++i)
		std::cout << numbers[i] << (i + 1 < numbers.size() ? " " : "");
	std::cout << std::endl;

	std::clock_t startVec = std::clock();
	std::vector<int> sortedVec = sortVector(numbers);
	std::clock_t endVec = std::clock();

	std::clock_t startDeq = std::clock();
	std::deque<int> sortedDeq = sortDeque(dq);
	std::clock_t endDeq = std::clock();

	std::cout << "After: ";
	for (size_t i = 0; i < sortedVec.size(); ++i)
		std::cout << sortedVec[i] << (i + 1 < sortedVec.size() ? " " : "");
	std::cout << std::endl;

	double vecTime = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1000000.0;
	double deqTime = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1000000.0;

	std::cout << "Time to process a range of " << numbers.size()
		<< " elements with std::vector : " << vecTime << " us" << std::endl;
	std::cout << "Time to process a range of " << numbers.size()
		<< " elements with std::deque : " << deqTime << " us" << std::endl;

	(void)sortedDeq;
}
