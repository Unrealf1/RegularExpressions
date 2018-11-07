#pragma once

#include <iostream>
#include <set>
#include <stack>
#include <vector>

#include "IRegularAutomate.hpp"
#include "General.hpp"

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

class CUndeterminedAutomate : public IRegularAutomate
{
	public:
		CUndeterminedAutomate(const std::string& regularExpression);
		~CUndeterminedAutomate();
		bool check(const std::string& word) const;
		void print() const;
	private:
		Node* root;

		void addEpsilon(std::set<Node*>& active) const;
		bool build(Node*, std::set<Node*>&);
		std::stack<std::string> buildStackFromExpression(const std::string&) const;
};
