#include <iostream>
#include <vector>
#include <string>


#define ASSERT_TRUE(expression) \
		assert_true((expression), __func__)

#define ASSERT_FALSE(expression) \
		assert_false((expression), __func__)

#define ASSERT_EQUALS(lhs, rhs) \
		assert_equals((lhs), (rhs), __func__)

#define EXCEPT_EXCEPTION(code, exception)										   \
		try {																	   \
			code																   \
			std::cerr << "[" << __func__ << "] - " << "Test failed" << std::endl;  \
		}																		   \
		catch(const exception&){												   \
			std::cout << "[" << __func__ << "] - " << "Test passed" << std::endl;  \
}																				   \


void assert_true(bool expression, std::string& test_name) {
	if (expression)
	{
		std::cout << "[" << test_name << "] - " << "Test passed" << std::endl;
	}
	else
	{
		std::cout << "[" << test_name << "] - " << "Test failed" << std::endl;
	}
}

void assert_false(bool expression, std::string& test_name) {
	if (!expression)
	{
		std::cout << "[" << test_name << "] - " << "Test passed" << std::endl;
	}
	else
	{
		std::cout << "[" << test_name << "] - " << "Test failed" << std::endl;
	}
}

template<typename T>
void assert_equals(T lhs, T rhs, const std::string& test_name) {

	if (lhs == rhs)
	{
		std::cout << "[" << test_name << "] - " << "Test passed" << std::endl;
	}
	else
	{
		std::cerr << "[" << test_name << "] - " << "Test failed" << std::endl;
	}
}

std::vector<int> sort(const std::vector<int>& data) {

	if (data.empty())
	{
		throw std::invalid_argument("Data is empty");
	}

	std::vector<int> result{ data };

	for (size_t i = 1; i < result.size(); i++) {
		for (size_t j = i; j > 0 && result[j] < result[j - 1]; j--)
		{
			std::swap(result[j], result[j - 1]);
		}
	}

	return result;
}

void test_sort_with_empty_data() {

	EXCEPT_EXCEPTION({ sort({}); }, std::invalid_argument);

}

void test_sort_with_one_data() {

	ASSERT_EQUALS(std::vector<int>{1}, sort({1}));

}

void test_sort_with_many_data() {
	std::vector<int> lhs{ 1, 2, 3, 4, 4, 5, 6, 8 };
	std::vector<int> rhs = sort({ 1, 4, 3, 6, 5, 8, 2, 4 });

	ASSERT_EQUALS(lhs, rhs);

}

int main()
{
	test_sort_with_empty_data();
	test_sort_with_one_data();
	test_sort_with_many_data();

	return EXIT_SUCCESS;

	return 0;
}
