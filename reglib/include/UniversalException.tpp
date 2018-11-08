#include "UniversalException.hpp"

namespace Automatons
{
	template<class T>
	void UniversalException::Append(const T& t) const
	{
		message_ << t;
	}

	template<class E, class T, typename>
	E&& operator<<(E&& e, const T& t)
	{
		e.Append(t);

		return std::forward<E>(e);
	}

	template<class E, typename>
	E&& operator<<(E&& e, std::ostream& (*function)(std::ostream&))
	{
		e.Apply(function);

		return std::forward<E>(e);
	}
}
