#pragma once
#include <exception>
#include <iostream>
#include <fstream>
#include <string.h>

class SimplestParsing
{
public:
	SimplestParsing(void);
	virtual ~SimplestParsing(void);

	std::ifstream& operator()();

	bool find(const std::string&);

	bool checkIfNextString(const std::string&);

	bool jumpSeparators();

private:
	std::ifstream stream_;


};
