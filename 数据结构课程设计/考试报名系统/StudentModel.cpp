#include "StudentModel.h"

//构造函数
Student::Student(int id, int num, string name, string sex, short int age, string category) :
	_id(id), _number(num), _name(name), _sex(sex), _age(age), _category(category) {}

int Student::getId() const {
	return _id;
}

int Student::getNumber() const {
	return _number;
}

string Student::getName() const {
	return _name;
}

string Student::getSex() const {
	return _sex;
}

int Student::getAge() const {
	return _age;
}

string Student::getCategory() const {
	return _category;
}

void Student::setId(int id) {
	_id = id;
}

void Student::setNumber(int num) {
	_number = num;
}

void Student::setName(string name) {
	_name = name;
}

void Student::setSex(string sex) {
	_sex = sex;
}

void Student::setAge(short int age) {
	_age = age;
}

void Student::setCategory(string category) {
	_category = category;
}

//输出重载
ostream& operator<<(ostream& output, const Student& stu) {
	cout << stu.getId() << " " << stu.getNumber()
		<< " " << stu.getName() << " " << stu.getSex()
		<< " " << stu.getAge() << " " << stu.getCategory();
	return output;
}

//输入重载
istream& operator>>(istream& input, Student& stu) {
	int number;
	string name, category, sex;
	short int age;
	cin >> number >> name >> sex >> age >> category;
	stu = Student(-1, number, name, sex, age, category);
	return input;
}