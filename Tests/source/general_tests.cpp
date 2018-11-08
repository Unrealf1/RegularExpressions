#include <string>
#include "CUndeterminedAutomaton.hpp"
#include "UniversalException.hpp"
#include "gtest/gtest.h"
#include "ProblemSolver.hpp"

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

TEST(GeneralTests, CorrectInput)
{
	Automatons::IRegularAutomaton* a;

	for (size_t i = 0; i < 50; ++i)
	{
		bool catched = false;

		std::string str = generateRegularExpression(rand()%(i+2)+2);
		
		try
		{
			a = new Automatons::CUndeterminedAutomaton(str);
		}
		catch (Automatons::UniversalException& e)
		{
			catched = (e.what() == "ERROR");
		}
		if (!catched)
		{
			delete a;
		}
		ASSERT_TRUE((!catched) && Automatons::is_regular(str));
	}
}

TEST(GeneralTests, IncorrectInput1)
{
	Automatons::IRegularAutomaton* a;

	for (size_t i = 0; i < 20; ++i)
	{
		bool catched = false;

		std::string str = generateRegularExpression(rand()%(i+20)+2);
		str.push_back('+');
		try
		{
			a = new Automatons::CUndeterminedAutomaton(str);
		}
		catch (Automatons::UniversalException& e)
		{
			catched = true;
		}

		if (!catched)
		{
			delete a;
		}

		ASSERT_TRUE(!((!catched) && Automatons::is_regular(str)));
	}
}

TEST(GeneralTests, IncorrectInput2)
{

	Automatons::IRegularAutomaton* a;
	for (size_t i = 0; i < 20; ++i)
	{
		bool catched = false;

		std::string str = generateRegularExpression(rand()%(i+20)+2);
		str.push_back('.');
		try
		{
			a = new Automatons::CUndeterminedAutomaton(str);
		}
		catch (Automatons::UniversalException& e)
		{
			catched = true;
		}
		if (!catched)
		{
			delete a;
		}
		ASSERT_TRUE(!((!catched) && Automatons::is_regular(str)));
	}	
}

TEST(GeneralTests, IncorrectInput3)
{

	Automatons::IRegularAutomaton* a;
	for (size_t i = 0; i < 20; ++i)
	{
		bool catched = false;

		std::string str = generateRegularExpression(rand()%(i+20)+2);
		str = str.substr(1, str.size() - 1);
		try
		{
			a = new Automatons::CUndeterminedAutomaton(str);
		}
		catch (Automatons::UniversalException& e)
		{
			catched = true;
		}
		if (!catched)
		{
			delete a;
		}
		ASSERT_TRUE(!((!catched) && Automatons::is_regular(str)));
	}	
}

struct test
{
	std::string reg;
	std::vector<std::string> words;
	// -1 here for INF, -2 for ERROR
	std::vector<int> answers;
};

TEST(GeneralTests, HardTests)
{
	std::vector<test> hTests = 
	{ {"ab+ab+.ac+b.a+.", {"abc", "abcb", "ccccbba"}, {-1, 4, 3} } };

	for (test curTest : hTests)
	{
		Automatons::IRegularAutomaton* a;
		bool catched = false;
		try
		{
			a = new Automatons::CUndeterminedAutomaton(curTest.reg);
		}
		catch (Automatons::UniversalException& e)
		{
			catched = true;
			for (int ans : curTest.answers)
			{
				ASSERT_EQ(ans, -2);
			}
			
		}
		if (!catched)
		{
			for (int i = 0; i < curTest.words.size(); ++i)
			{
				ProblemSolver solver(a);

				int solution = solver.GetMaxSuffixSize(curTest.words[i]);
				ASSERT_EQ(solution, curTest.answers[i]);
			}
			delete a;
		}
	}
}