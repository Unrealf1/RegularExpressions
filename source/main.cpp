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
	//std::cin >> u;
	
	CUndeterminedAutomate ak47(a);
	ak47.print();
}