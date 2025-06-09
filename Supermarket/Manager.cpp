#include "Manager.h"

Manager::Manager(const MyString& firstName, const MyString& lastName, const MyString& number, size_t age, const MyString& password, int authentificationCode) : Worker(firstName, lastName, number, age, password)
{
	this->authentificationCode = authentificationCode;
}
