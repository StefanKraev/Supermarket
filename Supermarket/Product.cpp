#include "Product.h"

Product::Product(const MyString& name, double price, int categoryId, double productLeft)
{
	this->name = name;
	this->price = price;
	this->categoryId = categoryId;
	this->productLeft = productLeft;
}