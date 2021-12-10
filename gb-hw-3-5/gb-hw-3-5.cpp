#include <iostream>
#include <unordered_set>
#include <string>
#include <set>
#include <map>
#include <queue>

//----------task 1-------------
/* т.к. в ассоциативных контейнерах одинаковые значения хранятся рядом, 
перед выводом слово сравнивается с предыдущим значением*/
template <typename T>
void uniqueWords(T p1, T p2) {
	T prev = p1;

	std::cout << *p1 << " ";
	p1++;

	for (; p1 != p2; p1++) {
		
		if (*prev != *p1)
		{
			std::cout << *p1 << " ";
		}
		prev = p1;
	}
	std::cout << std::endl;
}

//----------task 2-------------
void inputData(std::multimap<int, std::string>& data) {
	
	std::string s;
	char temp;

	while (std::getline(std::cin, s, '.') && !s.empty()) {
		
		data.insert({s.size(), s});

		std::cin.get(temp);
		if (temp == '\n')
			break;
	}
}

void outputSortedData(std::multimap<int, std::string>& data) {
	
	for (auto it = data.begin(); it != data.end(); it++) {
		std::cout << it->second << std::endl;
	}
}

int main()
{
	std::cout << "----------task 1-------------" << std::endl;
	std::unordered_set<std::string> words;
	words.insert("fox");
	words.insert("aerobus");
	words.insert("bar");
	words.insert("fox");
	uniqueWords(words.begin(), words.end());

	std::unordered_multiset<std::string> multiwords;
	multiwords.insert("mother");
	multiwords.insert("father");
	multiwords.insert("sister");
	multiwords.insert("brother");
	multiwords.insert("sister");
	multiwords.insert("mother");
	uniqueWords(multiwords.begin(), multiwords.end());

	std::cout << "----------task 2-------------" << std::endl;
	std::multimap<int, std::string> sentences;
	inputData(sentences);
	outputSortedData(sentences);


	return 0;

}

