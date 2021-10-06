#include "StudentModel.h"

Student::Student(int id, int num, string name, char sex, short int age) :
	_id(id), _number(num), _name(name), _sex(sex), _age(age) {}

int Student::getId() const
{
	return _id;
}

int Student::getNumber() const
{
	return _number;
}

string Student::getName() const
{
	return _name;
}

char Student::getSex() const
{
	return _sex;
}

int Student::getAge() const
{
	return _age;
}

void Student::setId(int id)
{
	_id = id;
}

void Student::setNumber(int num)
{
	_number = num;
}

void Student::setName(string name)
{
	_name = name;
}

void Student::setSex(char sex)
{
	_sex = sex;
}

void Student::setAge(short int age)
{
	_age = age;
}

ostream& operator<<(ostream& output, const Student& stu)
{
	cout << stu.getId() << " " << stu.getNumber()
		<< " " << stu.getName() << " " << stu.getSex()
		<< " " << stu.getAge();
	return output;
}

istream& operator>>(istream& input, Student& stu)
{
	int number;
	string name;
	char sex;
	short int age;
	cin >> number >> name >> sex >> age;
	stu = Student(-1, number, name, sex, age);
	return input;
}