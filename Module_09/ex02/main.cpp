#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <ctime>

/* Tek bir argumani dogrular ve sayiya cevirir.
   ">> value" sayiyi okur, "eof()" arkasinda fazlalik kalmadigini garanti eder
   ("1abc" reddedilir), "value < 0" negatifleri eler. Tamsayi tasmasinda
   stream failbit kurar, yani "2147483648" de reddedilir. */
static int parseToken(const char *arg)
{
	std::stringstream stream(arg);
	int value;

	if (!(stream >> value) || !stream.eof() || value < 0)
		throw std::runtime_error("Error");

	return value;
}

static void printSequence(const char *label, const std::vector<int> &seq)
{
	std::cout << label;
	for (size_t i = 0; i < seq.size(); ++i)
		std::cout << seq[i] << (i + 1 < seq.size() ? " " : "");
	std::cout << std::endl;
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}

	try
	{
		PmergeMe sorter;

		/* once tum argumanlar dogrulanir; hatali girdi varsa hic ciktisi olmaz */
		std::vector<int> input;
		for (int i = 1; i < argc; ++i)
			input.push_back(parseToken(argv[i]));

		printSequence("Before: ", input);

		/* olculen sure hem veri yonetimini (container'i doldurmayi) hem siralamayi kapsar */
		std::clock_t startVec = std::clock();
		std::vector<int> vec;
		for (int i = 1; i < argc; ++i)
			vec.push_back(parseToken(argv[i]));
		std::vector<int> sortedVec = sorter.sortVector(vec);
		std::clock_t endVec = std::clock();

		std::clock_t startDeq = std::clock();
		std::deque<int> deq;
		for (int i = 1; i < argc; ++i)
			deq.push_back(parseToken(argv[i]));
		std::deque<int> sortedDeq = sorter.sortDeque(deq);
		std::clock_t endDeq = std::clock();

		printSequence("After: ", sortedVec);

		double vecTime = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1000000.0;
		double deqTime = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1000000.0;

		std::cout << "Time to process a range of " << input.size()
			<< " elements with std::vector : " << vecTime << " us" << std::endl;
		std::cout << "Time to process a range of " << input.size()
			<< " elements with std::deque : " << deqTime << " us" << std::endl;

		(void)sortedDeq;
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}

	return 0;
}
