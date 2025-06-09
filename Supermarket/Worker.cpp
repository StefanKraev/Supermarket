#include "Worker.h"
#include <cstdlib>

Worker::Worker(const MyString& firstName, const MyString& lastName, const MyString& number, size_t age, const MyString& password)
{
	srand(time(0));
	id = rand();
	this->firstName = firstName;
	this->lastName = lastName;
	this->number = number;
	this->age = age;
	this->password = password;
}

