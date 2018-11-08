#include "ProblemSolver.hpp"

ProblemSolver::ProblemSolver(Automatons::IRegularAutomaton* automaton)
	:automaton_(automaton)
{

}

int ProblemSolver::GetMaxSuffixSize(const std::string& word) const
{
	for (size_t i = 0; i < word.size(); ++i)
	{
		if (automaton_->check(word.substr(i, word.size() - i)))
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
