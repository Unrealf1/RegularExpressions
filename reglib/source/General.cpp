#include "General.hpp"

bool Automatons::is_regular(const std::string& str)
{
	if (str.empty())
	{
		return true;
	}

	std::stack<std::string> st;
	for (size_t i = 0; i < str.size(); ++i)
	{
		char c = str[i];
		if ((c < 'a' || c > 'c') && c != '1' && c != '+' && c != '*' && c != '.')
		{
			return false;
		}
		if ((c >= 'a' && c <= 'c') || c == '1')
		{
			st.push(std::string({ c }));
		}
		if (c == '+' || c == '.')
		{
			if (st.empty())
			{
				return false;
			}
			std::string right_part = st.top();
			st.pop();
			if (st.empty())
			{
				return false;
			}
			std::string left_part = st.top();
			st.pop();
			st.push(left_part + right_part + c);
		}
		if (c == '*')
		{
			if (st.empty())
			{
				return false;
			}
			std::string cycle = st.top();
			st.pop();
			st.push(cycle + c);
		}
	}
	if (st.size() == 1 && st.top() == str)
	{
		return true;
	}
	return false;
}
