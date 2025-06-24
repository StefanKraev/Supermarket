#pragma once
#include "MyString.h"
#include "Category.h"

class Product
{
protected:
	MyString name;
	double price;
	int categoryId;
	double productLeft;

public:
	Product(const MyString& name, double price, int categoryId, double productLeft);
	Product(const Product& other);

	const MyString getProductName() const;
	const double getProductPrice() const;
	const int getProductCategoryId() const;
	const double getProductLeft() const;
};

