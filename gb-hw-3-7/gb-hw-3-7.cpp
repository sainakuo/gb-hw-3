#include <iostream>
#include <fstream>
#include "myspace.pb.h"
#include <string>

class IRepository {
	virtual void Open() = 0; // бинарная десериализация в файл
	virtual void Save() = 0; // бинарная сериализация в файл
};

class IMethods {
	virtual double GetAverageScore(const myspace::Fullname& name) = 0;
	virtual std::string GetAllInfo(const myspace::Fullname& name) = 0;
	virtual std::string GetAllInfo() = 0;
};

class StudentsGroup : public IRepository, IMethods {
private:
	myspace::StudentsGroup studentsGroup;

public:
	void Open() override {
		std::ifstream in("StudentsGroup.bin", std::ios_base::binary);

		if (studentsGroup.ParseFromIstream(&in)) {
			print();
		}
		else {
			std::cout << "Error!" << std::endl;
		}
	}

	void Save() override {

		myspace::Student* student1 = studentsGroup.add_students();
		myspace::Fullname fullname1;
		fullname1.set_name("Grigoriy");
		fullname1.set_lastname("Nazarov");
		fullname1.set_patronymic("Viktorovich");
		student1->set_allocated_fullname(&fullname1);

		student1->add_marks(3);
		student1->add_marks(4);
		student1->add_marks(5);
		student1->set_average(4);

		myspace::Student* student2 = studentsGroup.add_students();;
		myspace::Fullname fullname2;
		fullname2.set_name("Robert");
		fullname2.set_lastname("Kotlov");
		student2->set_allocated_fullname(&fullname2);

		student2->add_marks(3);
		student2->add_marks(4);
		student2->add_marks(5);
		student2->add_marks(5);

		student2->set_average(4.25);

		print();

		std::ofstream out("StudentsGroup.bin", std::ios_base::binary);
		studentsGroup.SerializeToOstream(&out);

	}

	void print() {
		for (size_t i = 0; i < studentsGroup.students_size(); i++)
		{
			const myspace::Student& student = studentsGroup.students(i);
			const myspace::Fullname& fullname = student.fullname();
			std::cout << fullname.name() << " " << fullname.lastname() << " " << fullname.patronymic() << std::endl;

			std::cout << "Marks: ";
			for (size_t j = 0; j < student.marks_size(); j++)
			{
				std::cout << student.marks(j) << " ";
			}

			std::cout << "Average: " << student.average() << std::endl;
		}
	}

	double GetAverageScore(const myspace::Fullname& name) override {

		for (size_t i = 0; i < studentsGroup.students_size(); i++) {
			myspace::Fullname name2 = studentsGroup.students(i).fullname();

			if (isEqual(name, name2))
			{
				return studentsGroup.students(i).average();
			}
			else
			{
				return 0;
			}
		}
	}

	bool isEqual(const myspace::Fullname& name1, const myspace::Fullname& name2) {
		if (name1.name() == name2.name() && name1.lastname() == name2.lastname() && name1.patronymic() == name2.patronymic())
			return true;
		else
			return false;
	}

	std::string GetAllInfo(const myspace::Fullname& name) {
		std::string res = "";
		for (size_t i = 0; i < studentsGroup.students_size(); i++) {
			myspace::Student student = studentsGroup.students(i);
			myspace::Fullname name2 = student.fullname();

			if (isEqual(name, name2))
			{
				res = "name: " + name2.name() + ", lastname: " + name2.lastname() + ", patronymic: " + name2.patronymic();

				res += ", marks: ";
				for (size_t j = 0; j < student.marks_size(); j++)
				{
					res += student.marks(j) + " ";
				}

				res += "average: " + std::to_string(student.average());

				break;
			}


		}
		return res;
	}

	std::string GetAllInfo() {
		std::string res = "";
		for (size_t i = 0; i < studentsGroup.students_size(); i++) {
			myspace::Student student = studentsGroup.students(i);
			myspace::Fullname name = student.fullname();

			res += "student " + i;
			res += ": name: " + name.name() + ", lastname: " + name.lastname() + ", patronymic: " + name.patronymic();
			res += ", marks: ";
			for (size_t j = 0; j < student.marks_size(); j++)
			{
				res += student.marks(j) + " ";
			}

			res += "average: " + std::to_string(student.average());
		}

		return res;
	}
};

int main() {

    StudentsGroup stg;

    stg.Save();

    //stg.Open();

    return 0;
}