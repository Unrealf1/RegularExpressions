#pragma once

#include "IRegularAutomate.hpp"

class ProblemSolver
{
public:
	ProblemSolver(IRegularAutomate* automaton);
	int GetMaxSuffixSize(const std::string&) const;
private:
	IRegularAutomate* automaton_;
};