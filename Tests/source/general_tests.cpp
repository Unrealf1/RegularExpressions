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

	for (size_t i = 0; i < 80; ++i)
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

TEST(GeneralTests, IncorrectInput4)
{

	Automatons::IRegularAutomaton* a;
	for (size_t i = 0; i < 20; ++i)
	{
		bool catched = false;

		std::string str = generateRegularExpression(rand()%(i+20)+2);
		str[rand()%str.size()] = 'd' + rand()%10;
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

TEST(GeneralTests, HardCheckTests)
{
	std::vector<test> hTests = 
	{ { "1a+b*+", {"", "a", "bbb", "bbbbbbbbbbbbb", "ab", "c", "aa"}, {1, 1, 1, 1, 0, 0, 0} },
	  { "ab+ab+.", {"a", "b", "", "ab", "ba", "aa", "c", "aaa", "bb"}, {0, 0, 0, 1, 1, 1, 0, 0, 1} },
          { "bc.ac..", {"bcac", "bc", "ac", "bca", "bcbc", "acac", "cacb", ""}, {1, 0, 0, 0, 0, 0, 0, 0} },
	  { "b1.a*.", {"b", "ba", "baaaaaaa", "", "a", "aaaaa"}, {1, 1, 1, 0, 0, 0}	}, 
          {"a***c*1..", {"", "aaaaaaaaaaaaaaaa", "aaaaaaaaaaccccccccc", "c", "a", "ccca"}, {1, 1, 1, 1, 1, 0}	} };
	
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
			ASSERT_TRUE(false);	
		}
		if (!catched)
		{
			for (int i = 0; i < curTest.words.size(); ++i)
			{
				ASSERT_EQ(a->check(curTest.words[i]), curTest.answers[i]);
			}
			delete a;
		}
	}



}

TEST(GeneralTests, HardTests)
{
	std::vector<test> hTests = 
	{ {"ab+ab+.ac+b.a+.", {"abc", "abcb", "ccccbba"}, {-1, 4, 3} },
	  {"ab+c.aba.*.bac.+.+*", {"babc"}, {2}},
	  {"acb..bab.c.*.ab.ba.+.+*a.", {"cbaa"}, {1}} };

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

std::string generateRandomString(size_t sz)
{
	std::string str;
	for (size_t i = 0; i < sz; ++i)
	{
		str.push_back('a' + rand()%3);
	}
	return str;
}

TEST (GeneralTests, RandomBlindTests)
{
	Automatons::IRegularAutomaton* a;
	for (size_t i = 0; i < 80; ++i)
	{
		bool catched = false;
		std::string str = generateRegularExpression(rand()%(i+20)+2);
		try
		{
			a = new Automatons::CUndeterminedAutomaton(str);
		}
		catch (Automatons::UniversalException& e)
		{
			catched = true;
			ASSERT_TRUE(false);
			
		}
		if (!catched)
		{
			ProblemSolver solver(a);
			int solution = solver.GetMaxSuffixSize(generateRandomString(rand()%(i+15)+1));
			bool flg = solution > -2;
			ASSERT_TRUE(flg);
			delete a;
		}
	}
}

