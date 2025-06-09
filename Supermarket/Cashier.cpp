#include "Cashier.h"

void Cashier::free()
{
	delete[] citations;
	citations = nullptr;
	numOfTransactions = size = 0;
}

void Cashier::copyFrom(const Cashier& other)
{
	citations = new Citation[other.size];
	size = other.size;
	numOfTransactions = other.numOfTransactions;
}

void Cashier::moveFrom(Cashier&& other)
{
	citations = other.citations;
	other.citations = nullptr;
	size = other.size;
	numOfTransactions = other.numOfTransactions;
}

Cashier::Cashier(const MyString& firstName, const MyString& lastName, const MyString& number, size_t age, const MyString& password, size_t numOfTransactions, const Citation* citations, size_t size) : Worker::Worker(firstName, lastName, number, age, password)
{
	this->citations = new Citation[size];
	for (int i = 0; i < size; i++)
		this->citations[i] = citations[i];
	this->numOfTransactions = numOfTransactions;
	this->size = size;
}

Cashier::Cashier(const Cashier& other) : Worker(other)
{
	copyFrom(other);
}

Cashier::Cashier(Cashier&& other) noexcept : Worker(std::move(other))
{
	moveFrom(std::move(other));
}

Cashier& Cashier::operator=(const Cashier& other)
{
	if (this != &other)
	{
		Worker::operator=(other);
		free();
		copyFrom(other);
	}
	return *this;
}

Cashier& Cashier::operator=(Cashier&& other) noexcept
{
	if (this != &other)
	{
		Worker::operator=(std::move(other));
		free();
		copyFrom(other);
	}
	return *this;
}

Cashier::~Cashier()
{
	free();
}