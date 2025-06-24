#pragma once
#include "Worker.h"
#include "Citation.h"

class Cashier : public Worker
{
public:
	size_t numOfTransactions = 0;
	Citation* citations;
	size_t size = 0;

	void free();
	void copyFrom(const Cashier& other);
	void moveFrom(Cashier&& other);
public:
	Cashier(const MyString& firstName, const MyString& lastName, const MyString& number, size_t age, const MyString& password, size_t numOfTransactions,const Citation* citations, size_t size);
	Cashier(const Cashier& other);
	Cashier(Cashier&& other) noexcept;
	Cashier& operator=(const Cashier& other);
	Cashier& operator=(Cashier&& other) noexcept;
	~Cashier();

};

