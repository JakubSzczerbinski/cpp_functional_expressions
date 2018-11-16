#pragma once

#include <type_traits>

#include "empty.hpp"
#include "void.hpp"

template <typename T>
class Iterator
{
public:
	T operator* ();
	Iterator& operator++();
};

template <typename Iterator, typename _ = void>
struct is_iterator : std::false_type {};

template <typename Iterator>
struct is_iterator<
	Iterator,
	std::enable_if_t 
		<
			std::is_same<decltype(++(std::declval<Iterator>())), Iterator&>::value,
			void_t <decltype(*std::declval<Iterator>())>
		>
> : std::true_type {};

static_assert(is_iterator<Iterator<int>>::value, "Iterator interface does not meet iterator requirements");
static_assert(not is_iterator<Empty>::value, "Empty interface does meet iterator requirements");

