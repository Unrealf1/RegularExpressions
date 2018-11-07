#include "CUndeterminedAutomate.hpp"

bool operator<(const Edge& left, const Edge& right)
{
	return left.expression < right.expression;
}


CUndeterminedAutomate::CUndeterminedAutomate(
	const std::string& regularExpression)
	:root(new Node)
{
	if (!is_regular(regularExpression))
	{
		std::cout << "ERROR";
		return;
	}
	if (regularExpression.size() == 1 && regularExpression[0] == '1')
	{
		root->terminal = true;
		return;
	}
	Node* new_node = new Node;
	new_node->terminal = true;
	root->children.insert({regularExpression, new_node});
	std::set<Node*> been;
	while(build(root, been))
	{
		been.clear();
		while(build(root, been))
		{
			been.clear();
		}
	}
	
}

bool CUndeterminedAutomate::build(Node* currentNode, std::set<Node*>& been)
{
	bool changed = false;
	been.insert(currentNode);
	std::cout << "Has " << currentNode->children.size() << " children" << std::endl;
	for (Edge child : currentNode->children)
	{
		/*if (child.nd == currentNode)
		{
			std::cout << "It's cycle!" << std::endl;
			continue;
		}*/

		std::cout << "Now parcing " << child.expression << std::endl;
		std::stack<std::string> buildStack = 
			buildStackFromExpression(child.expression);
		std::stack<std::string> t_st = buildStack;
		std::cout << "Stack:" << std::endl;
		while(!t_st.empty())
		{
			std::cout << "\t" << t_st.top() << std::endl;
			t_st.pop();
		}
		if (buildStack.size() == 1)
		{
			std::cout << "Already OK" << std::endl;
			continue;
		}
		changed = true;
		currentNode->children.erase(child);
		char operation = buildStack.top()[0];
		std::cout << "Operation is "<< operation << std::endl;
		buildStack.pop();
		if (operation == '*')
		{
			///////////////////////?????????????????
			std::string cicle = buildStack.top();
			currentNode->children.insert({cicle, currentNode});
			currentNode->children.insert({"1", child.nd});
			continue;
		}
		std::string right_part = buildStack.top();
		buildStack.pop();
		std::string left_part = buildStack.top();
		buildStack.pop();
		if (operation == '.')
		{
			Node* new_node = new Node;
			currentNode->children.insert({left_part, new_node});
			new_node->children.insert(
				{right_part, child.nd});
		}
		if (operation == '+')
		{
			currentNode->children.insert({left_part, child.nd});
			currentNode->children.insert({right_part, child.nd});
		}
	}
	for (Edge child : currentNode->children)
	{
		if (child.nd == currentNode || been.find(child.nd) != been.end())
		{
			continue;
		}
		changed |= build(child.nd, been);
	}
	return changed;
}

std::stack<std::string> CUndeterminedAutomate::buildStackFromExpression(
	const std::string& reg) const
{
	std::stack<std::string> buildStack;
	for (int i = 0; i < reg.size() - 1; ++i)
	{
		char c = reg[i];
		if ((c >= 'a' && c <= 'c') || c == '1')
		{
			buildStack.push(std::string({c}));
		}
		if (c == '+' || c == '.')
		{
			std::string right_part = buildStack.top();
			buildStack.pop();
			std::string left_part = buildStack.top();
			buildStack.pop();
			buildStack.push(right_part+left_part+c);
		}
		if (c == '*')
		{
			std::string cycle = buildStack.top();
			buildStack.pop();
			buildStack.push(cycle+c);
		}
	}
	buildStack.push(std::string{reg[reg.size() - 1]});
	return buildStack;
}

CUndeterminedAutomate::~CUndeterminedAutomate()
{;

}

bool CUndeterminedAutomate::check(const std::string& word) const
{
	Node* cur = root;
	for (char c : word)
	{
		continue;
	}
}


#include <iostream>
void CUndeterminedAutomate::print() const
{
	std::stack<std::pair<Node*, std::string>> st;
	std::stack<int> st2;

	st2.push(-1);
	st.push({root, " "});
	while (!st.empty())
	{
		Node* cur = st.top().first;
		std::cout << "I am " << cur->id << " from " << st2.top() << " by \"" 
			<< st.top().second << "\"" << std::endl;
		st.pop();
		st2.pop();
		for (Edge i : cur->children)
		{
			if (i.nd == cur)
			{
				std::cout << "Has cycle to self by " 
					<< i.expression << std::endl;
				continue;
			}
			st.push({i.nd, i.expression});
			st2.push(cur->id);
		}
	}

}

Node::Node()
{
	//extern int g_id;
	//id = g_id++;
}