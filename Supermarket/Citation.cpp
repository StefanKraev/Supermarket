#include "Citation.h"

Citation::Citation()
{
	sender = "Unknown";
	description = "Undescribed";
	citDegree = CitaionDegree::low;
}

Citation::Citation(const MyString& sender, const MyString& description, CitaionDegree citDegree)
{
	this->sender = sender;
	this->description = description;
	this->citDegree = citDegree;
}