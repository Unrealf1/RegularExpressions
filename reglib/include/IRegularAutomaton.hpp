#pragma once
#include <string> 

namespace Automatons
{
	class IRegularAutomaton
	{
	public:
		virtual ~IRegularAutomaton() = default;
		virtual bool check(const std::string& word) const = 0;
	};
}
