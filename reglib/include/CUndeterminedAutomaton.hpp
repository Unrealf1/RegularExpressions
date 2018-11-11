#pragma once

#ifndef CUNDETERMINEDAUTOMATON_HPP_
#define CUNDETERMINEDAUTOMATON_HPP_

//#define DEBUG_

#include <iostream>
#include <set>
#include <stack>
#include <vector>

#include "IRegularAutomaton.hpp"
#include "General.hpp"
#include "UniversalException.hpp"

namespace Automatons
{

	struct Node;

	struct Edge
	{
		std::string expression;
		Node* nd;
	};

	bool operator<(const Edge& left, const Edge& right);

	struct Node
	{
		Node();
		int id;
		static int g_id;
		std::vector<Edge> children;
		bool terminal = false;
	};

	class CUndeterminedAutomaton : public IRegularAutomaton
	{
	public:
		CUndeterminedAutomaton(const std::string& regularExpression);
		~CUndeterminedAutomaton();
		/**check function checks if the word given is in the language*/
		bool check(const std::string& word) const;

		/**print function prints internals of the automaton*/
		void print() const;
	private:
		Node * root;

		/**addEpsilon adds all epcilon transitions to the set of active nodes*/
		void addEpsilon(std::set<Node*>& active) const;

		/**build is intended to "relax" all the edges*/
		bool build(Node*, std::set<Node*>&);

		/**buildStackFromExpression returns stack with the last operation on 
		the top and	two arguments below*/
		std::stack<std::string> buildStackFromExpression(const std::string&) const;
	};
}

#endif //CUNDETERMINEDAUTOMATON_HPP_
