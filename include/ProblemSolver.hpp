#pragma once

#include "IRegularAutomate.hpp"

class ProblemSolver
{
public:
	ProblemSolver(IRegularAutomate*);
	~ProblemSolver() = default;
	int GetMaxSuffixSize(const std::string&) const;
private:
	IRegularAutomate* automaton_;
};
