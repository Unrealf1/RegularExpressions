#include "ProblemSolver.hpp"

ProblemSolver::ProblemSolver(IRegularAutomate* automaton)
	:automaton_(automaton)
{

}

int ProblemSolver::GetMaxSuffixSize(const std::string& word) const
{
	for (int i = 0; i < word.size(); ++i)
	{
		if (automaton_->check(word.substr(i, word.size() - 1 - i)))
		{
			return word.size() - i;
		}
	}
	if (automaton_->check(""))
	{
		return 0;
	}
	return -1;
}