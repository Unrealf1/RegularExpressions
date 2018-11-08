#pragma once

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
		bool check(const std::string& word) const;
		void print() const;
	private:
		Node * root;

		void addEpsilon(std::set<Node*>& active) const;
		bool build(Node*, std::set<Node*>&);
		std::stack<std::string> buildStackFromExpression(const std::string&) const;
	};
}
