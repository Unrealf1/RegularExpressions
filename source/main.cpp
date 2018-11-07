#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "CUndeterminedAutomate.hpp"

int main()
{
	std::string a;
	std::cin >> a;
	std::string u;
	std::cin >> u;
	
	CUndeterminedAutomate ak47(a);
	std::cout << ak47.check(u) << std::endl;
	for (int i = 0; i < u.size(); ++i)
	{

	}
}