#include <iostream>
#include <string>
#include <optional>
#include <tuple>
#include <vector>
#include <fstream>
#include <ctype.h>
#include <algorithm>
#include <iomanip>

struct Person {
	std::string lastName;
	std::string name;
	std::optional<std::string> patronymic;

	Person() {}

	Person(std::string inLastName, std::string inName, std::optional<std::string> inPatronymic) :
		lastName(inLastName), name(inName), patronymic(inPatronymic) {}

	bool operator<(const Person& person2) {
		return (std::tie(lastName, name, patronymic) < std::tie(person2.lastName, person2.name, person2.patronymic));
	}
	bool operator==(const Person& person2) {
		return (std::tie(lastName, name, patronymic) == std::tie(person2.lastName, person2.name, person2.patronymic));
	}
};

std::ostream& operator<<(std::ostream& out, const Person& person) {
	out << std::left << std::setw(15) << person.lastName << std::setw(10) << person.name;
	out << std::setw(15);
	if (person.patronymic.has_value())
		out << person.patronymic.value();
	else
		out << " ";

	return out;
}

struct PhoneNumber {
	int codeCountry;
	int codeCity;
	std::string number;
	std::optional<int> addNumber;

	PhoneNumber() {}

	PhoneNumber(int inCodeCountry, int inCodeCity, std::string inNumber, std::optional<int> inAddNumber) :
		codeCountry(inCodeCountry), codeCity(inCodeCity), number(inNumber), addNumber(inAddNumber) {}

	bool operator<(const PhoneNumber& phoneNumber2) {
		return (std::tie(codeCountry, codeCity, number, addNumber) < std::tie(phoneNumber2.codeCountry, phoneNumber2.codeCity, phoneNumber2.number, phoneNumber2.addNumber));
	}
};

std::ostream& operator<<(std::ostream& out, const PhoneNumber& phoneNumber) {
	out << "+" << phoneNumber.codeCountry << "(" << phoneNumber.codeCity << ")" << phoneNumber.number;
	if (phoneNumber.addNumber.has_value())
	{
		out << " " << phoneNumber.addNumber.value();
	}
	return out;
}

class PhoneBook {
private:
	std::vector<std::pair<Person, PhoneNumber>> book;
public: 
	PhoneBook(std::ifstream& inf) {
		std::string str;
		std::string temp;

		Person person;
		PhoneNumber phoneNumber;

		while (inf.is_open() && !inf.eof()) {
			getline(inf, str);

			person.lastName = str.substr(0, str.find(' '));
			str.erase(0, person.lastName.length() + 1);

			person.name = str.substr(0, str.find(' '));
			str.erase(0, person.name.length() + 1);

			temp = str.substr(0, str.find(' '));
			str.erase(0, temp.length() + 1);

			person.patronymic = std::nullopt;

			if (temp.find("+") == std::string::npos)
			{
				person.patronymic = temp;

				temp = str.substr(0, str.find(' '));
				str.erase(0, temp.length() + 1);
			}

			phoneNumber.codeCountry = stoi(temp.substr(1, 1));
			phoneNumber.codeCity = stoi(temp.substr(3, 5));
			phoneNumber.number = temp.substr(7, 13);
			phoneNumber.addNumber = std::nullopt;

			if (!str.empty())
			{
				phoneNumber.addNumber = stoi(str);
			}

			book.push_back(std::make_pair(person, phoneNumber));

		}
		
	}

	void SortByName() {
		sort(book.begin(), book.end(), [](auto& x, auto& y) {return x.first < y.first; });
	}

	void SortByPhone() {
		sort(book.begin(), book.end(), [](auto& x, auto& y) {return x.second < y.second; });
	}

	std::tuple<std::string, PhoneNumber> GetPhoneNumber(std::string lastName) {
		std::vector<std::pair<Person, PhoneNumber>>::iterator it;
		std::tuple<std::string, PhoneNumber> temp_tuple;

		int sum = 0;
		PhoneNumber phoneNumber;

		for (it = book.begin(); it != book.end(); it++)
		{
			if (it->first.lastName == lastName)
			{
				sum++;
				phoneNumber = it->second;
			}
		}

		switch (sum) {
		case 0: 
			temp_tuple = std::make_tuple("not found", phoneNumber);
			break;
		case 1:
			temp_tuple = std::make_tuple("", phoneNumber);
			break;
		default: 
			temp_tuple = std::make_tuple("found more than 1", phoneNumber);
			break;
		}

		return temp_tuple;
	}

	void ChangePhoneNumber(Person person, PhoneNumber newPhoneNumber) {
		std::vector<std::pair<Person, PhoneNumber>>::iterator it;
		for (it = book.begin(); it != book.end(); it++)
		{
			if (it->first == person)
			{
				it->second = newPhoneNumber;
			}
		}
	}

	friend std::ostream& operator<<(std::ostream& out, PhoneBook& phoneBook);
};


std::ostream& operator<<(std::ostream& out, PhoneBook& phoneBook) {
	std::vector<std::pair<Person, PhoneNumber>>::iterator it;

	for (it = phoneBook.book.begin(); it != phoneBook.book.end(); it++)
	{
		out << it->first << " " << it->second << std::endl;
	}

	return out;
}



int main()
{
	std::ifstream file("PhoneBook.txt"); // путь к файлу PhoneBook.txt
	PhoneBook book(file);

	std::cout << book;

	std::cout << "------SortByPhone-------" << std::endl;
	book.SortByPhone();
	std::cout << book;

	std::cout << "------SortByName--------" << std::endl;
	book.SortByName();
	std::cout << book;

	std::cout << "-----GetPhoneNumber-----" << std::endl;
	// лямбда функция, которая принимает фамилию и выводит номер телефона этого человека, либо строку с ошибкой
	auto print_phone_number = [&book](const std::string& surname) {
		std::cout << surname << "\t";
		auto answer = book.GetPhoneNumber(surname);
		if (std::get<0>(answer).empty())
			std::cout << std::get<1>(answer);
		else
			std::cout << std::get<0>(answer);
		std::cout << std::endl;
	};

	// вызовы лямбды
	print_phone_number("Frolov");
	print_phone_number("Petrov");

	std::cout << "----ChangePhoneNumber----" << std::endl;
	book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" }, PhoneNumber{ 7, 123, "15344458", std::nullopt });
	book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" }, PhoneNumber{ 16, 465, "9155448", 13 });
	std::cout << book;
	return 0;
}

