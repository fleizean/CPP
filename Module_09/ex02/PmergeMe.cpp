#include "PmergeMe.hpp"
#include <stdexcept>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) { (void)other; }

PmergeMe &PmergeMe::operator=(const PmergeMe &other) { (void)other; return *this; }

PmergeMe::~PmergeMe() {}

/* ---- Jacobsthal ekleme sirasi ----
   J(k) = J(k-1) + 2 * J(k-2)  ->  1, 3, 5, 11, 21, 43 ...
   pend elemanlari (J(k-1), J(k)] gruplari halinde, her grup buyukten kucuge eklenir;
   boylece her ikili arama tam 2^k - 1 boyutunda bir araliga denk gelir.
   pend 0-tabanli oldugu icin b(t) = pend[t-1]; 0. indeks uretilmez (basa bedava eklendi).
   Ornek (pend.size() = 12) -> 2 1 4 3 10 9 8 7 6 5 11                          */

std::vector<size_t> PmergeMe::jacobsthalInsertionOrder(size_t n) const
{
	std::vector<size_t> order;
	size_t prev = 1;
	size_t curr = 3;

	while (prev < n)
	{
		size_t hi = (curr < n) ? curr : n;

		for (size_t t = hi; t > prev; --t)
			order.push_back(t - 1);

		size_t next = curr + 2 * prev;
		prev = curr;
		curr = next;
	}

	return order;
}

/* ---- vector implementasyonu ---- */

/* chain[] gercek degerlerin indekslerini tutar, karsilastirma degerler uzerinden yapilir.
   [0, hi) araliginda val'dan kucuk olmayan ilk konumu dondurur (std::lower_bound mantigi). */
size_t PmergeMe::lowerBoundVector(const std::vector<int> &values, const std::vector<size_t> &chain, size_t hi, int val) const
{
	size_t lo = 0;

	while (lo < hi)
	{
		size_t mid = lo + (hi - lo) / 2;
		if (values[chain[mid]] < val)
			lo = mid + 1;
		else
			hi = mid;
	}

	return lo;
}

std::vector<size_t> PmergeMe::fordJohnsonVector(const std::vector<int> &values, std::vector<size_t> indices) const
{
	if (indices.size() <= 1)
		return indices;

	/* 1) tek sayida eleman varsa sondakini ayir, en sonda yerlestirilir */
	bool hasStray = (indices.size() % 2 != 0);
	size_t strayIdx = 0;
	if (hasStray)
	{
		strayIdx = indices.back();
		indices.pop_back();
	}

	/* 2) ikiser eslestir; partner[buyuk] = ciftteki kucuk eleman */
	std::vector<size_t> bigIdx;
	std::vector<size_t> partner(values.size(), 0);
	for (size_t i = 0; i < indices.size(); i += 2)
	{
		bool firstWins = !(values[indices[i]] < values[indices[i + 1]]);
		size_t big = firstWins ? indices[i] : indices[i + 1];

		bigIdx.push_back(big);
		partner[big] = firstWins ? indices[i + 1] : indices[i];
	}

	/* 3) buyukleri rekursif olarak sirala -> ana zincir */
	std::vector<size_t> chain = fordJohnsonVector(values, bigIdx);

	/* 4-6) pend = ana zincir sirasina gore eslerin kucukleri.
	        pend[0] zincirin en kucugunun esidir, yani hepsinden kucuktur:
	        karsilastirmasiz basa eklenir. chainPos[i] = chain[i]'nin result
	        icindeki guncel konumu; bastaki ekleme bastan hesaba katilir.
	        Buraya gelindiginde indices.size() >= 2 oldugu icin chain bos olamaz. */
	std::vector<size_t> result(chain);
	std::vector<size_t> pend;
	std::vector<size_t> chainPos;

	for (size_t i = 0; i < chain.size(); ++i)
	{
		pend.push_back(partner[chain[i]]);
		chainPos.push_back(i + 1);
	}
	result.insert(result.begin(), pend[0]);

	/* 7) kalan pend elemanlari Jacobsthal sirasiyla eklenir.
	      pend[j] esi olan chain[j]'den kucuk oldugu icin arama [0, chainPos[j])
	      araligiyla sinirlidir -> Ford-Johnson'un karsilastirma tasarrufu buradan gelir */
	std::vector<size_t> order = jacobsthalInsertionOrder(pend.size());
	for (size_t k = 0; k < order.size(); ++k)
	{
		size_t j = order[k];
		size_t pos = lowerBoundVector(values, result, chainPos[j], values[pend[j]]);

		result.insert(result.begin() + pos, pend[j]);
		for (size_t i = 0; i < chainPos.size(); ++i)
		{
			if (chainPos[i] >= pos)
				++chainPos[i];
		}
	}

	/* 8) ayrilan tek elemanin esi yok, bu yuzden tum zincirde aranir */
	if (hasStray)
	{
		size_t pos = lowerBoundVector(values, result, result.size(), values[strayIdx]);
		result.insert(result.begin() + pos, strayIdx);
	}

	return result;
}

std::vector<int> PmergeMe::sortVector(std::vector<int> seq) const
{
	/* deger yerine indeks siralanir: tekrarli sayilarda hangi elemanin hangi
	   ciftten geldigi ancak indeksle kesin olarak ayirt edilebilir */
	std::vector<size_t> indices;
	for (size_t i = 0; i < seq.size(); ++i)
		indices.push_back(i);

	std::vector<size_t> sortedIdx = fordJohnsonVector(seq, indices);

	std::vector<int> result;
	for (size_t i = 0; i < sortedIdx.size(); ++i)
		result.push_back(seq[sortedIdx[i]]);

	return result;
}

/* ---- deque implementasyonu ---- */

size_t PmergeMe::lowerBoundDeque(const std::deque<int> &values, const std::deque<size_t> &chain, size_t hi, int val) const
{
	size_t lo = 0;

	while (lo < hi)
	{
		size_t mid = lo + (hi - lo) / 2;
		if (values[chain[mid]] < val)
			lo = mid + 1;
		else
			hi = mid;
	}

	return lo;
}

std::deque<size_t> PmergeMe::fordJohnsonDeque(const std::deque<int> &values, std::deque<size_t> indices) const
{
	if (indices.size() <= 1)
		return indices;

	/* 1) tek sayida eleman varsa sondakini ayir, en sonda yerlestirilir */
	bool hasStray = (indices.size() % 2 != 0);
	size_t strayIdx = 0;
	if (hasStray)
	{
		strayIdx = indices.back();
		indices.pop_back();
	}

	/* 2) ikiser eslestir; partner[buyuk] = ciftteki kucuk eleman */
	std::deque<size_t> bigIdx;
	std::deque<size_t> partner(values.size(), 0);
	for (size_t i = 0; i < indices.size(); i += 2)
	{
		bool firstWins = !(values[indices[i]] < values[indices[i + 1]]);
		size_t big = firstWins ? indices[i] : indices[i + 1];

		bigIdx.push_back(big);
		partner[big] = firstWins ? indices[i + 1] : indices[i];
	}

	/* 3) buyukleri rekursif olarak sirala -> ana zincir */
	std::deque<size_t> chain = fordJohnsonDeque(values, bigIdx);

	/* 4-6) pend = ana zincir sirasina gore eslerin kucukleri.
	        pend[0] zincirin en kucugunun esidir, yani hepsinden kucuktur:
	        karsilastirmasiz basa eklenir. chainPos[i] = chain[i]'nin result
	        icindeki guncel konumu; bastaki ekleme bastan hesaba katilir.
	        Buraya gelindiginde indices.size() >= 2 oldugu icin chain bos olamaz. */
	std::deque<size_t> result(chain);
	std::deque<size_t> pend;
	std::deque<size_t> chainPos;

	for (size_t i = 0; i < chain.size(); ++i)
	{
		pend.push_back(partner[chain[i]]);
		chainPos.push_back(i + 1);
	}
	result.insert(result.begin(), pend[0]);

	/* 7) kalan pend elemanlari Jacobsthal sirasiyla eklenir.
	      pend[j] esi olan chain[j]'den kucuk oldugu icin arama [0, chainPos[j])
	      araligiyla sinirlidir -> Ford-Johnson'un karsilastirma tasarrufu buradan gelir */
	std::vector<size_t> order = jacobsthalInsertionOrder(pend.size());
	for (size_t k = 0; k < order.size(); ++k)
	{
		size_t j = order[k];
		size_t pos = lowerBoundDeque(values, result, chainPos[j], values[pend[j]]);

		result.insert(result.begin() + pos, pend[j]);
		for (size_t i = 0; i < chainPos.size(); ++i)
		{
			if (chainPos[i] >= pos)
				++chainPos[i];
		}
	}

	/* 8) ayrilan tek elemanin esi yok, bu yuzden tum zincirde aranir */
	if (hasStray)
	{
		size_t pos = lowerBoundDeque(values, result, result.size(), values[strayIdx]);
		result.insert(result.begin() + pos, strayIdx);
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
