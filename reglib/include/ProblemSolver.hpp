#pragma once

#ifndef PROBLEMSOLVER_HPP_
#define PROBLEMSOLVER_HPP_

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

#endif //PROBLEMSOLVER_HPP_
