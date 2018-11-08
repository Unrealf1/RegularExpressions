#include "UniversalException.hpp"

namespace Automatons
{
	UniversalException::UniversalException(const UniversalException& other)
		: message_(other.message_.str()), cache_(message_.str())
	{

	}

	UniversalException& UniversalException::operator=(const UniversalException& other)
	{
		message_.str(other.message_.str());
		cache_ = message_.str();
		return *this;
	}

	const char* UniversalException::what() const noexcept
	{
		cache_ = message_.str();
		return cache_.c_str();
	}

	void UniversalException::Apply(std::ostream& (*function)(std::ostream&)) const
	{
		function(message_);
	}
}
