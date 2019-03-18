#include <iostream>
#include <string>
#include "CUndeterminedAutomaton.hpp"
#include "ProblemSolver.hpp"
#include "UniversalException.hpp"

int main(int argc, char* argv[])
{
	std::string a;
	std::cin >> a;
	std::string u;
	std::cin >> u;

	Automatons::IRegularAutomaton* automaton;

	try
	{
		automaton = new Automatons::CUndeterminedAutomaton(a);
	}
	catch (Automatons::UniversalException& e)
	{
		std::cout << e.what();
		return -1;
	}

	ProblemSolver solver(automaton);

	int solution = solver.GetMaxSuffixSize(u);
	if (solution >= 0)
	{
		std:: cout << solution << std::endl;
	}
	else
	{
		std::cout << "INF" << std::endl;
	}
	delete automaton;
}
