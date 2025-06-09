#pragma once
#include "MyString.h"
#include "Category.h"

class Product
{
	MyString name;
	double price;
	int categoryId;
	double productLeft;

public:
	Product(const MyString& name, double price, int categoryId, double productLeft);
};

