#include "Student.h"

Student::Student()
{
    _yearOfBirht = 0;
    _averMark = 0.0;
}

Student::Student(const Student& right)
{
    *this = right;
}

void Student::setName(std::basic_string<TCHAR>& name)
{
	_name = name;
}

std::basic_string<TCHAR> Student::getName() const
{
	return _name;
}

void Student::setLastname (std::basic_string<TCHAR>& lastname)
{
	_lastname = lastname;
}

std::basic_string<TCHAR> Student::getLastname() const
{
	return _lastname;
}

void Student::setSurname(std::basic_string<TCHAR>& surname)
{
    _surname = surname;
}

std::basic_string<TCHAR> Student::getSurname() const
{
    return _surname;
}

void Student::setYearOfBirht(int year)
{
	_yearOfBirht = year;
}

short int Student::getYearOfBirht() const
{
	return _yearOfBirht;
}

void Student::setAverMark(float averMark)
{
	_averMark = averMark;
}

float Student::getAverMark() const
{
	return _averMark;
}

Student& Student::operator=(const Student& right)
{
	if (this != &right)
	{
		_name = right._name;
		_lastname = right._lastname;
        _surname = right._surname;
		_yearOfBirht = right._yearOfBirht;
		_averMark = right._averMark;
	}

	return *this;
}

int Student::compareStudents(const Student& right) const
{
	int result = _surname.compare(right._surname);

	if (result == 0)
	{
		result = _name.compare(right._name);

		if (result == 0)
		{
            result = _lastname.compare(right._lastname);
		}
	}

	return result;
}

bool Student::operator==(const Student& right)
{
	return compareStudents(right) == 0;
}

bool Student::operator!=(const Student& right)
{
	return compareStudents(right) != 0;
}

bool Student::operator>=(const Student& right) 
{
	return compareStudents(right) != -1;
}

bool Student::operator<=(const Student& right) 
{
	return compareStudents(right) != 1;
}

bool Student::operator>(const Student& right) 
{
	return compareStudents(right) == 1;
}

bool Student::operator<(const Student& right)
{
	return compareStudents(right) == -1;
}

outstream& operator<<(outstream& output, Student& right)
{
	output << right._surname << __T(" ") 
        << right._name << __T(" ")
		<< right._lastname << __T(" ") 
        << right._yearOfBirht << __T(" ")
		<< right._averMark << std::endl;

	return output;
}


inStream& operator >> (inStream& input, Student& right)
{
	input >> right._surname 
        >> right._name 
        >> right._lastname
		>> right._yearOfBirht 
        >> right._averMark;

	return input;
}
