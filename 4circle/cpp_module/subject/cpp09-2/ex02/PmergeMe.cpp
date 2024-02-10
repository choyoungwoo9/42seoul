#include "PmergeMe.hpp"

static void printBefore(std::vector<int> vt)
{
	std::cout << "Before: ";
	for (int i = 0; i < (int)vt.size(); i++)
		std::cout << vt[i] << " ";
	std::cout << std::endl;
}

static void printAfter(std::vector<int> vt)
{
	std::cout << "After: ";
	for (int i = 0; i < (int)vt.size(); i++)
		std::cout << vt[i] << " ";
	std::cout << std::endl;
}

PmergeMe::PmergeMe()
{
}
PmergeMe::PmergeMe(const PmergeMe &obj)
{
	originNumVector = obj.originNumVector;
	sortedNumVector = obj.sortedNumVector;
	vectorTime = obj.vectorTime;
	originNumDeque = obj.originNumDeque;
	sortedNumDeque = obj.sortedNumDeque;
	dequeTime = obj.dequeTime;
}

void PmergeMe::run(int arg, char **argv)
{
	try
	{
		vectorProcess(arg, argv);
		dequeProcess(arg, argv);

		printBefore(originNumVector);
		printAfter(sortedNumVector);
		std::cout << "Time to process a range of " << sortedNumVector.size() << " elements with std::vector: " << vectorTime << " us" << std::endl;
		std::cout << "Time to process a range of " << sortedNumDeque.size() << " elements with std::deque: " << dequeTime << " us" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Error" << std::endl;
	}
	catch (std::string str)
	{
		std::cout << str << std::endl;
	}
}

PmergeMe &PmergeMe::operator=(const PmergeMe &obj)
{
	if (this == &obj)
		return *this;
	originNumVector = obj.originNumVector;
	sortedNumVector = obj.sortedNumVector;
	vectorTime = obj.vectorTime;
	originNumDeque = obj.originNumDeque;
	sortedNumDeque = obj.sortedNumDeque;
	dequeTime = obj.dequeTime;
	return *this;
}
PmergeMe::~PmergeMe()
{
}

static int myAtoi(std::string str)
{
	for (int i = 0; i < (int)str.length(); i++)
		if (!isdigit(str[i]))
			throw std::exception();

	int num = std::atoi(str.c_str());
	if (num <= 0)
		throw std::exception();
	return num;
}

/////////////////////////////////포드 존슨 Vector//////////////////////////////////

static std::vector<int> makeVector(int arg, char **argv)
{
	std::vector<int> vt;
	if (arg == 1)
		throw std::exception();
	for (int i = 1; i < arg; i++)
		vt.push_back(myAtoi(argv[i]));
	return vt;
}

static void dupNumCheckVector(std::vector<int> vt)
{
	for (int j = 0; j < (int)vt.size(); j++)
	{
		for (int i = j + 1; i < (int)vt.size(); i++)
			if (vt[i] == vt[j])
				throw std::exception();
	}
}

static void checkVectorSorted(std::vector<int> originVt, std::vector<int> sortedVt)
{
	for (int i = 0; i < (int)sortedVt.size() - 1; i++)
		if (sortedVt[i] >= sortedVt[i + 1])
			throw std::string("NOT SORTED !!");
	if ((int)originVt.size() != (int)sortedVt.size())
		throw std::string("NOT SORTED !!");
}

static std::vector<numPair> setPairVector(std::vector<int> originNumVector)
{
	std::vector<numPair> pairVt;
	for (int i = 0; i < (int)originNumVector.size(); i += 2)
	{
		numPair np;
		if (i == (int)originNumVector.size() - 1)
			continue;
		else
		{
			np.n1 = std::max(originNumVector[i], originNumVector[i + 1]);
			np.n2 = std::min(originNumVector[i], originNumVector[i + 1]);
		}
		pairVt.push_back(np);
	}
	return pairVt;
}

static void mergeVector(std::vector<numPair> &numPairVt, int left, int mid, int right)
{
	std::vector<numPair> vt1;
	std::vector<numPair> vt2;
	for (int i = left; i <= mid; i++)
		vt1.push_back(numPairVt[i]);
	for (int i = mid + 1; i <= right; i++)
		vt2.push_back(numPairVt[i]);
	int i = 0;
	int j = 0;
	int k = left;
	while (i < (int)vt1.size() && j < (int)vt2.size())
	{
		if (vt1[i].n1 < vt2[j].n1)
		{
			numPairVt[k] = vt1[i];
			i++;
		}
		else
		{
			numPairVt[k] = vt2[j];
			j++;
		}
		k++;
	}
	while (i < (int)vt1.size())
	{
		numPairVt[k] = vt1[i];
		i++;
		k++;
	}
	while (j < (int)vt2.size())
	{
		numPairVt[k] = vt2[j];
		j++;
		k++;
	}
}

static void mergeVectorSort(std::vector<numPair> &numPairVt, int left, int right)
{
	if (left >= right)
		return;
	int mid = (left + right) / 2;
	mergeVectorSort(numPairVt, left, mid);
	mergeVectorSort(numPairVt, mid + 1, right);
	mergeVector(numPairVt, left, mid, right);
}

static void insertByBinarySearchVector(std::vector<int> &sortedVt, int right, int target)
{
	int left = 0;
	while (left < right)
	{
		int mid = (left + right) / 2;
		if (sortedVt[mid] < target)
			left = mid + 1;
		else
			right = mid;
	}
	sortedVt.insert(sortedVt.begin() + left, target);
}

static std::vector<int> getJacobVector(int size)
{
	std::vector<int> dp;
	dp.push_back(0);
	dp.push_back(1);
	int i = 2;
	while (1)
	{
		dp.push_back(dp[i - 1] + 2 * dp[i - 2]);
		if (dp[i] > size)
			break;
		i++;
	}
	return dp;
}

std::vector<int> fordJohnsonSortVector(std::vector<int> originNumVector)
{
	if ((int)originNumVector.size() == 1)
		return originNumVector;
	std::vector<numPair> pairVt = setPairVector(originNumVector);
	mergeVectorSort(pairVt, 0, (int)pairVt.size() - 1);
	std::vector<int> sortedVt;
	for (int i = 0; i < (int)pairVt.size(); i++)
		sortedVt.push_back(pairVt[i].n1);

	if ((int)originNumVector.size() % 2 == 1)
	{
		numPair np;
		np.n1 = -1;
		np.n2 = (int)originNumVector[originNumVector.size() - 1];
		pairVt.push_back(np);
	}
	std::vector<int> jacobNumVt = getJacobVector((int)pairVt.size());
	for (int i = 2; i < (int)jacobNumVt.size(); i++)
	{
		if (i == 2)
		{

			insertByBinarySearchVector(sortedVt, 1, pairVt[0].n2);
			continue;
		}
		int j;
		i == (int)jacobNumVt.size() - 1 ? j = (int)pairVt.size() : j = jacobNumVt[i];
		int right = j + jacobNumVt[i - 1] - 1;
		for (; j > jacobNumVt[i - 1]; j--)
		{
			insertByBinarySearchVector(sortedVt, right, pairVt[j - 1].n2);
		}
	}
	return sortedVt;
}

void PmergeMe::vectorProcess(int arg, char **argv)
{
	clock_t start = std::clock();
	originNumVector = makeVector(arg, argv);
	dupNumCheckVector(originNumVector);
	sortedNumVector = fordJohnsonSortVector(originNumVector);
	checkVectorSorted(originNumVector, sortedNumVector);
	clock_t end = std::clock();
	vectorTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
}

/////////////////////////////////포드 존슨 Deque//////////////////////////////////

static std::deque<int> makeDeque(int arg, char **argv)
{
	std::deque<int> dq;
	if (arg == 1)
		throw std::exception();
	for (int i = 1; i < arg; i++)
		dq.push_back(myAtoi(argv[i]));
	return dq;
}

static void dupNumCheckDeque(std::deque<int> dq)
{
	for (int j = 0; j < (int)dq.size(); j++)
	{
		for (int i = j + 1; i < (int)dq.size(); i++)
			if (dq[i] == dq[j])
				throw std::exception();
	}
}

static void checkDequeSorted(std::deque<int> originDq, std::deque<int> sortedDq)
{
	for (int i = 0; i < (int)sortedDq.size() - 1; i++)
		if (sortedDq[i] >= sortedDq[i + 1])
			throw std::string("NOT SORTED !!");
	if ((int)originDq.size() != (int)sortedDq.size())
		throw std::string("NOT SORTED !!");
}

static std::deque<numPair> setPairDeque(std::deque<int> originNumDeque)
{
	std::deque<numPair> pairDq;
	for (int i = 0; i < (int)originNumDeque.size(); i += 2)
	{
		numPair np;
		if (i == (int)originNumDeque.size() - 1)
			continue;
		else
		{
			np.n1 = std::max(originNumDeque[i], originNumDeque[i + 1]);
			np.n2 = std::min(originNumDeque[i], originNumDeque[i + 1]);
		}
		pairDq.push_back(np);
	}
	return pairDq;
}

static void mergeDeque(std::deque<numPair> &numPairDq, int left, int mid, int right)
{
	std::deque<numPair> dq1;
	std::deque<numPair> dq2;
	for (int i = left; i <= mid; i++)
		dq1.push_back(numPairDq[i]);
	for (int i = mid + 1; i <= right; i++)
		dq2.push_back(numPairDq[i]);
	int i = 0;
	int j = 0;
	int k = left;
	while (i < (int)dq1.size() && j < (int)dq2.size())
	{
		if (dq1[i].n1 < dq2[j].n1)
		{
			numPairDq[k] = dq1[i];
			i++;
		}
		else
		{
			numPairDq[k] = dq2[j];
			j++;
		}
		k++;
	}
	while (i < (int)dq1.size())
	{
		numPairDq[k] = dq1[i];
		i++;
		k++;
	}
	while (j < (int)dq2.size())
	{
		numPairDq[k] = dq2[j];
		j++;
		k++;
	}
}

static void mergeDequeSort(std::deque<numPair> &numPairDq, int left, int right)
{
	if (left >= right)
		return;
	int mid = (left + right) / 2;
	mergeDequeSort(numPairDq, left, mid);
	mergeDequeSort(numPairDq, mid + 1, right);
	mergeDeque(numPairDq, left, mid, right);
}

static void insertByBinarySearchDeque(std::deque<int> &sortedDq, int right, int target)
{
	int left = 0;
	while (left < right)
	{
		int mid = (left + right) / 2;
		if (sortedDq[mid] < target)
			left = mid + 1;
		else
			right = mid;
	}
	sortedDq.insert(sortedDq.begin() + left, target);
}

static std::deque<int> getJacobDeque(int size)
{
	std::deque<int> dp;
	dp.push_back(0);
	dp.push_back(1);
	int i = 2;
	while (1)
	{
		dp.push_back(dp[i - 1] + 2 * dp[i - 2]);
		if (dp[i] > size)
			break;
		i++;
	}
	return dp;
}

std::deque<int> fordJohnsonSortDeque(std::deque<int> originNumDeque)
{
	if ((int)originNumDeque.size() == 1)
		return originNumDeque;
	std::deque<numPair> pairDq = setPairDeque(originNumDeque);
	mergeDequeSort(pairDq, 0, (int)pairDq.size() - 1);
	std::deque<int> sortedDq;
	for (int i = 0; i < (int)pairDq.size(); i++)
		sortedDq.push_back(pairDq[i].n1);

	if ((int)originNumDeque.size() % 2 == 1)
	{
		numPair np;
		np.n1 = -1;
		np.n2 = originNumDeque[(int)originNumDeque.size() - 1];
		pairDq.push_back(np);
	}
	std::deque<int> jacobNumDq = getJacobDeque((int)pairDq.size());
	for (int i = 2; i < (int)jacobNumDq.size(); i++)
	{
		if (i == 2)
		{

			insertByBinarySearchDeque(sortedDq, 1, pairDq[0].n2);
			continue;
		}
		int j;
		i == (int)jacobNumDq.size() - 1 ? j = (int)pairDq.size() : j = jacobNumDq[i];
		int right = j + jacobNumDq[i - 1] - 1;
		for (; j > jacobNumDq[i - 1]; j--)
		{
			insertByBinarySearchDeque(sortedDq, right, pairDq[j - 1].n2);
		}
	}
	return sortedDq;
}

void PmergeMe::dequeProcess(int arg, char **argv)
{
	clock_t start = std::clock();
	originNumDeque = makeDeque(arg, argv);
	dupNumCheckDeque(originNumDeque);
	sortedNumDeque = fordJohnsonSortDeque(originNumDeque);
	checkDequeSorted(originNumDeque, sortedNumDeque);
	clock_t end = std::clock();
	dequeTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
}
