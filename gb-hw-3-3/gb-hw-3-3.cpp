#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <cmath>

//--------------task 1---------------

void pushBackAver(std::vector<float>& data) {
	if (!data.empty())
	{
		float average = std::accumulate(data.begin(), data.end(), 0.0) / data.size();
		data.push_back(average);
	}

}

std::ostream& operator<<(std::ostream& out, const std::vector<float>& data) {
	for (float value : data) {
		out << value << " ";
	}
	return out;
}

//--------------task 2---------------

class Matrix {
private:
	int n; //размерность
	std::vector<int> data;

public: 
	Matrix(int inN, std::vector<int>& inData) {
		assert(inData.size() == inN*inN);

		n = inN;
		data = inData;		
	}

	Matrix addMinorMatrix(int pos) {
		std::vector<int> dataMinorMatrix;

		for (size_t i = 0; i < n; i++) {
			for (size_t j = 0; j < n; j++) {

				if (i != 0 && j != pos) {
					dataMinorMatrix.push_back(data[j + i * n]);
				}
			}
		}

		return Matrix(n - 1, dataMinorMatrix);
	}

	//рекурсивный способ вычисления определителя с помощью дополнительного минора
	int determinant() {
		if (n == 1) {
			return data[0];
		}
		else if (n == 2)
		{
			return (data[0] * data[3] - data[2] * data[1]);
		}
		else
		{
			int sum = 0;
			for (size_t j = 0; j < n; j++) {
				Matrix addMinor = addMinorMatrix(j);
				sum += pow(-1, 1 + j + 1)* data[j] * addMinor.determinant();
			}
			return sum;
		}
	}

	friend std::ostream& operator<<(std::ostream& out, Matrix& matrix);

};

std::ostream& operator<<(std::ostream& out, Matrix& matrix) {

	for (size_t i = 0; i < matrix.n; i++) {
		for (size_t j = 0; j < matrix.n; j++) {
			out << matrix.data[j + i * matrix.n] << " ";
		}
		out << std::endl;
	}

	return out;
}

//--------------task 3---------------
struct Node {
	int value;
	Node* next;

	Node(int inValue) : value(inValue) {};
};

struct Container {

	struct Iterator {

		Node* ptr;
		
		Iterator(Node* p) : ptr(p) {}

		Iterator& operator++() {

				ptr = ptr->next;
				return *this;

		}
		Iterator& operator++(int) {
			Iterator prev = *this;
			ptr = ptr->next;
			return prev;
		}

		int operator*() {

			return ptr->value;
		}

		friend bool operator!=(Iterator lhs, Iterator rhs);
	};

	Iterator begin() {
		return Iterator(head);
	}
	Iterator end() {
		Iterator it = begin();
		while (it != nullptr)
		{
			it++;
		}
		return it;
	}

	Node* head;

	Container(std::vector<int>& init) {
		
		head = new Node(init[0]);
		Node* temp_data = head;

		for (size_t i = 1; i < init.size(); i++) {
			Node* new_data = new Node(init[i]);
			temp_data->next = new_data;
			temp_data = new_data;
			new_data->next = nullptr;
		}
		
	}

	~Container() {
		Node* temp = head; 
		Node* next;

		while (temp != nullptr)
		{
			next = temp->next;
			delete temp;
			temp = next;
		}
	}
};

bool operator!=(Container::Iterator lhs, Container::Iterator rhs) {
	if (lhs.ptr != rhs.ptr)
		return true;
	else
		return false;
}

int main()
{
//----------task 1---------------
	std::cout << "task 1: " << std::endl;
	std::vector<float> data = { 1.2, 3.4, 5.6 };
	std::cout << data << std::endl;
	pushBackAver(data);
	std::cout << data << std::endl;

//----------task 2---------------
	std::cout << "task 2: " << std::endl;
	std::vector<int> dataMatrix3 = { 1, 5, 3, 
									 2, 6, 7, 
									 1, 4, 8 };

	std::vector<int> dataMatrix4 = { 3, 4, 2, 1, 
									 1, 2, 3, 3,
	                                 4, 4, 5, 3,
	                                 2, 3, 9, 8};
	Matrix matrix3(3, dataMatrix3);
	std::cout << matrix3;
	std::cout << "Determinator: " << matrix3.determinant()<< std::endl;
	std::cout << std::endl;

	Matrix matrix4(4, dataMatrix4);
	std::cout << matrix4;
	std::cout << "Determinator: " << matrix4.determinant() << std::endl;

	//----------task 3---------------
	std::cout << "task 3: " << std::endl;
	std::vector<int> init = { 1,2,3,4,5,6 };
	Container container(init);

	for (int value : container) {
		std::cout << value << " ";
	}


	return 0;
}

