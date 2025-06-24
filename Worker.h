#pragma once
#include "MyString.h"

class Worker
{
public:
	int id = 0;
	MyString firstName;
	MyString lastName;
	MyString number;
	size_t age = 0;
	MyString password;

public:
	Worker(const MyString& firstName, const MyString& lastName, const MyString& number, size_t age, const MyString& password);

};

