#include "Product.h"

Product::Product(const MyString& name, double price, int categoryId, double productLeft)
{
	this->name = name;
	this->price = price;
	this->categoryId = categoryId;
	this->productLeft = productLeft;
}

Product::Product(const Product& other)
{
	name = other.name;
	price = other.price;
	categoryId = other.categoryId;
	productLeft = other.productLeft;
}

const MyString Product::getProductName() const
{
	return this->name;
}

const double Product::getProductPrice() const
{
	return this->price;
}

const int Product::getProductCategoryId() const
{
	return this->categoryId;
}

const double Product::getProductLeft() const
{
	return this->productLeft;
}


