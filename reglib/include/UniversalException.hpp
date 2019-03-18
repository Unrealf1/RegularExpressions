#pragma once

#ifndef REGULAR_EXCEPTION_HPP_
#define REGULAR_EXCEPTION_HPP_

#include <exception>
#include <sstream>
#include <type_traits>

namespace Automatons
{
	class UniversalException : public std::exception
	{
	public:
		UniversalException() = default;
		UniversalException(const UniversalException& other);
		UniversalException(UniversalException&&) = default;
		UniversalException& operator=(const UniversalException&);
		UniversalException& operator=(UniversalException&&) = default;

		const char* what() const noexcept override;

		template<class T>
		void Append(const T& t) const;
		void Apply(std::ostream& (*f)(std::ostream&)) const;

	private:
		mutable std::stringstream message_;
		mutable std::string cache_;
	};

	template<
		class E,
		class T,
		typename = std::enable_if_t<std::is_same<UniversalException, std::decay_t<E>>::value>>
		E&& operator<<(E&& e, const T& t);

	template<
		class E,
		typename = std::enable_if_t<std::is_same<UniversalException, std::decay_t<E>>::value>>
		E&& operator<<(E&& e, std::ostream& (*function)(std::ostream&));
}

#include "UniversalException.tpp"
#endif //REGULAR_EXCEPTION_HPP_
