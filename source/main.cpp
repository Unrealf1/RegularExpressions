#include <iostream>
#include <string>
#include "CUndeterminedAutomate.hpp"
#include "ProblemSolver.hpp"

int main()
{
	std::string a;
	std::cin >> a;
	std::string u;
	std::cin >> u;

	CUndeterminedAutomate ak47(a);
	ProblemSolver solver(&ak47);
	int solution = solver.GetMaxSuffixSize(u);
	if (solution >= 0)
	{
		std:: cout << solution << std::endl;
	}
	else
	{
		std::cout << "INF" << std::endl;
	}
}