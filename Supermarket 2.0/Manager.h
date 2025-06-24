#pragma once
#include "Worker.h"
#include "MyString.h"

class Manager : public Worker
{
public:
	char authentificationCode[8];

public:
	Manager(const MyString& firstName, const MyString& lastName, const MyString& number, size_t age, const MyString& password, const char* authenticationCode);
};