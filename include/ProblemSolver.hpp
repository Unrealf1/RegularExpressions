#pragma once

#include "IRegularAutomaton.hpp"

class ProblemSolver
{
public:
	ProblemSolver(Automatons::IRegularAutomaton*);
	~ProblemSolver() = default;
	int GetMaxSuffixSize(const std::string&) const;
private:
	Automatons::IRegularAutomaton* automaton_;
};
