#include "CUndeterminedAutomaton.hpp"
#include "UniversalException.hpp"

namespace Automatons
{
	bool operator<(const Edge& left, const Edge& right)
	{
		return left.expression < right.expression;
	}

	CUndeterminedAutomaton::~CUndeterminedAutomaton()
	{
		if (root == nullptr)
		{
			return;
		}
		std::stack<Node*> st;
		std::vector<int> been(Node::g_id, 0);
		st.push(root);
		been[root->id] = 1;
		std::vector<Node*> toDelete = {root};
		while (!st.empty())
		{
			Node* cur = st.top();
			st.pop();
			for (Edge i : cur->children)
			{
				if (i.nd == nullptr || been[i.nd->id])
				{
					continue;
				}
				st.push(i.nd);
				toDelete.push_back(i.nd);
				been[i.nd->id] = 1;
			}
		}
		for (Node* nd : toDelete)
		{
			delete nd;
		}
	}

	CUndeterminedAutomaton::CUndeterminedAutomaton(const std::string& regularExpression)
		:root(new Node)
	{
		if (!is_regular(regularExpression))
		{
			throw UniversalException() << "ERROR";
			return;
		}
		Node* new_node = new Node;
		new_node->terminal = true;
		root->children.push_back({ regularExpression, new_node });
		std::set<Node*> been;
		while (build(root, been))
		{
			been.clear();
			while (build(root, been))
			{
				been.clear();
			}
		}

	}

	bool CUndeterminedAutomaton::build(Node* currentNode, std::set<Node*>& been)
	{
		bool changed = false;
		been.insert(currentNode);

#ifdef DEBUG_
		std::cout << currentNode->id << " has " << currentNode->children.size() << " children" << std::endl;
#endif // DEBUG_

		std::vector<Edge> newChildren;
		for (size_t i = 0; i < currentNode->children.size(); ++i)
		{
			Edge child = currentNode->children[i];

			std::stack<std::string> buildStack =
				buildStackFromExpression(child.expression);
			std::stack<std::string> t_st = buildStack;
#ifdef DEBUG_
			std::cout << "Now parcing " << child.expression << std::endl;
			std::cout << "Stack:" << std::endl;
			while (!t_st.empty())
			{
				std::cout << "\t" << t_st.top() << std::endl;
				t_st.pop();
			}
#endif // DEBUG_

			if (buildStack.size() == 1)
			{
#ifdef DEBUG_
				std::cout << "Already OK" << std::endl;
#endif // DEBUG_
				newChildren.push_back(child);
				continue;
			}

			changed = true;
			char operation = buildStack.top()[0];

#ifdef DEBUG_
			std::cout << "Operation is " << operation << std::endl;
#endif // DEBUG

			buildStack.pop();
			if (operation == '*')
			{
				std::string cicle = buildStack.top();
				newChildren.push_back({ cicle, currentNode });
				newChildren.push_back({ "1", child.nd });

#ifdef DEBUG_
				std::cout << "Added " << currentNode->id << " -> " << currentNode->id << " by " << cicle << std::endl;
				std::cout << "Added " << currentNode->id << " -> " << child.nd->id << " by " << "1" << std::endl;
#endif // DEBUG_

				continue;
			}
			std::string right_part = buildStack.top();
			buildStack.pop();
			std::string left_part = buildStack.top();
			buildStack.pop();
			if (operation == '.')
			{
				Node* new_node = new Node;
				newChildren.push_back({ left_part, new_node });
				new_node->children.push_back({ right_part, child.nd });
#ifdef DEBUG_
				std::cout << "Added " << currentNode->id << " -> " << new_node->id << " by " << left_part << std::endl;
				std::cout << "Added " << new_node->id << " -> " << child.nd->id << " by " << right_part << std::endl;
#endif // DEBUG_			
			}
			if (operation == '+')
			{
				newChildren.push_back({ left_part, child.nd });
				newChildren.push_back({ right_part, child.nd });
#ifdef DEBUG_
				std::cout << "Added " << currentNode->id << " -> " << child.nd->id << " by " << left_part << std::endl;
				std::cout << "Added " << currentNode->id << " -> " << child.nd->id << " by " << right_part << std::endl;

#endif // DEBUG_

			}
		}

		currentNode->children = newChildren;

		/*Just regular dfs*/
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

	std::stack<std::string> CUndeterminedAutomaton::buildStackFromExpression(
		const std::string& reg) const
	{
		std::stack<std::string> buildStack;
		for (size_t i = 0; i < reg.size() - 1; ++i)
		{
			char c = reg[i];
			if ((c >= 'a' && c <= 'c') || c == '1')
			{
				buildStack.push(std::string({ c }));
			}
			if (c == '+' || c == '.')
			{
				std::string right_part = buildStack.top();
				buildStack.pop();
				std::string left_part = buildStack.top();
				buildStack.pop();
				buildStack.push(left_part + right_part + c);
			}
			if (c == '*')
			{
				std::string cycle = buildStack.top();
				buildStack.pop();
				buildStack.push(cycle + c);
			}
		}
		buildStack.push(std::string{ reg[reg.size() - 1] });
		return buildStack;
	}

	inline void CUndeterminedAutomaton::addEpsilon(std::set<Node*>& active) const
	{
		bool added = true;
		while (added)
		{
			added = false;
			for (Node* cur : active)
			{
				for (Edge child : cur->children)
				{
					if (child.expression == "1" && active.find(child.nd) == active.end())
					{
						active.insert(child.nd);
						added = true;
					}
				}
			}
		}
	}

	bool CUndeterminedAutomaton::check(const std::string& word) const
	{
#ifdef DEBUG_
		std::cout << "Checking " << word << std::endl;
#endif // DEBUG_

		std::set<Node*> active = { root };
		addEpsilon(active);

		for (char c : word)
		{
#ifdef DEBUG_
			std::cout << "Active: \n";
			for (auto i : active)
			{
				std::cout << i->id << ' ';
			}
			std::cout << std::endl;
#endif // DEBUG_

			std::set<Node*> new_active;
			addEpsilon(active);
			for (Node* cur : active)
			{
				for (Edge child : cur->children)
				{
					if (child.expression == std::string({ c }))
					{
						new_active.insert(child.nd);
					}
				}
			}
			addEpsilon(new_active);
			active = new_active;
		}

		for (Node* nd : active)
		{
			if (nd->terminal)
			{
				return true;
			}
		}
		return false;
	}

	void CUndeterminedAutomaton::print() const
	{
		std::stack<std::pair<Node*, std::string>> st;
		std::stack<int> st2;

		std::vector<int> been(Node::g_id, 0);

		st2.push(-1);
		st.push({ root, " " });

		while (!st.empty())
		{
			Node* cur = st.top().first;
			std::cout << "I am " << cur->id << " from " << st2.top() << " by \""
				<< st.top().second << "\" " << " has " << cur->children.size();
			if (cur->terminal)
			{
				std::cout << " X";
			}
			std::cout << std::endl;
			st.pop();
			st2.pop();
			if (been[cur->id])
			{
				continue;
			}
			been[cur->id] = 1;
			for (Edge i : cur->children)
			{
				if (i.nd == cur)
				{
					std::cout << cur->id << " has cycle to self by "
						<< i.expression << std::endl;
					continue;
				}
				st.push({ i.nd, i.expression });
				st2.push(cur->id);

			}
		}

	}

	Node::Node()
	{
		id = g_id++;
	}

	int Node::g_id = 0;
}
