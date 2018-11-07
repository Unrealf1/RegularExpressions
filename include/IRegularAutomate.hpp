#pragma once
#include <string> 

class IRegularAutomate
{
	public:
		virtual ~IRegularAutomate() = default;
		virtual bool check(const std::string& word) const = 0;
};
