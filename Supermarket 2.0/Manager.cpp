#include "Manager.h"
#pragma warning (disable: 4996)

Manager::Manager(const MyString& firstName, const MyString& lastName, const MyString& number, size_t age, const MyString& password, const char* authenticficationCode) : Worker(firstName, lastName, number, age, password)
{

	strcpy(this->authentificationCode,authentificationCode);
}
