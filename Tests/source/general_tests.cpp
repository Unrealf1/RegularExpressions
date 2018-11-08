#include <string>
#include "../../include/CUndeterminedAutomaton.hpp"
#include "../../include/UniversalException.hpp"
#include "gtest/gtest.h"

std::string generateRegularExpression(size_t sz)
{
	if (sz == 2)
	{
		return std::string({ char('a' + rand() % 3) }) + "*";
	}
	if (sz == 1)
	{
		char res = 'a';
		if (rand() % 3)
		{
			res = 'a' + rand() % 3;
		}
		else
		{
			res = '1';
		}
		return std::string({ res });
	}
	if (rand() % 4)
	{
		char operation = ' ';
		rand() % 2 ? operation = '+' : operation = '.';

		if (sz % 2)
		{
			return std::string(generateRegularExpression((sz - 1) / 2) + 
				generateRegularExpression((sz - 1) / 2) + std::string({ operation }));
		}
		else
		{
			return std::string(generateRegularExpression((sz) / 2) + 
				generateRegularExpression((sz - 2) / 2) + std::string({ operation }));
		}
	}
	else
	{
		return std::string(generateRegularExpression(sz - 1) + "*");
	}
}

TEST(GeneralTests, IncorrectInput)
{
	Automatons::IRegularAutomaton* a;

	bool catched;

	std::string str = generateRegularExpression(5);

	try
	{
		a = new Automatons::CUndeterminedAutomaton(str);
	}
	catch (Automatons::UniversalException& e)
	{
		catched = (e.what() == "ERROR");
	}
}