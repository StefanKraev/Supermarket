#pragma once
#include "MyString.h";

enum class CitaionDegree
{
	low = 100,
	medium = 200,
	high = 300
};

class Citation
{
	MyString sender;
	MyString description;
	CitaionDegree citDegree;

public:
	Citation();
	Citation(const MyString& sender, const MyString& description, CitaionDegree citDegree);
};

