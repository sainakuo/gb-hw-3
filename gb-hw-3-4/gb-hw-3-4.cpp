#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

//---------task 1-------------
template<typename T>
void insert_sorted(std::vector<T>& data, const T in) {
	int begin = 0;
	int end = data.size()-1;
	int middle;

	while (begin <= end) {
		
		middle = begin + (end - begin) / 2;

		if (in == data[middle])
		{
			begin = middle + 1;
			break;
		} 
		else if (in > data[middle])
		{
			begin = middle + 1;
		}
		else if (in < data[middle])
		{
			end = middle - 1;
		}

	}

	data.insert(data.begin()+begin, in);
}

//---------task 2-------------

void generateA(std::vector<double>& vec) {
	std::generate(vec.begin(), vec.end(), []() {double f = (double)rand() / RAND_MAX;
												return 0.1 + f * (10.9 - 0.1); });
}

void generateB(std::vector<double>& vecA, std::vector<int>& vecB) {
	std::generate(vecB.begin(), vecB.end(), [vecA, n = 0]() mutable { return (int)vecA[n++]; });
}

double countError(std::vector<double>& vecA, std::vector<int>& vecB) {
	std::vector<double> vecC(100);
	std::generate(vecC.begin(), vecC.end(), [vecA, vecB, n = 0]() mutable {double d = pow((vecA[n] - vecB[n]), 2); n++; return d; });
	return std::accumulate(vecC.begin(), vecC.end(), 0.0);
}

int main()
{
	//---------task 1-------------
	std::cout << "task 1:" << std::endl;
	std::vector<int> intData = { 3, 4, 7, 8, 12, 15 };
	
	for (int value : intData)
	{
		std::cout << value << " ";
	}
	std::cout << std::endl;

	insert_sorted(intData, 9);

	for (int value : intData)
	{
		std::cout << value << " ";
	}
	std::cout << std::endl;

	//---------task 2-------------
	std::cout << "task 2:" << std::endl;

	std::vector<double> vecA(100);
	generateA(vecA);
	for (double value : vecA) {
		std::cout << value << " ";
	}
	std::cout << std::endl;
	
	std::vector<int> vecB(100);
	generateB(vecA, vecB);
	for (int value : vecB) {
		std::cout << value << " ";
	}
	std::cout << std::endl;

	std::cout << "count: " << countError(vecA, vecB);

	return 0;
}