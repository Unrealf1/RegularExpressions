#pragma once

#ifndef IREGULARAUTOMATON_HPP_
#define IREGULARAUTOMATON_HPP_

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

#endif //IREGULARAUTOMATON_HPP_

