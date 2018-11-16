#pragma once

#include <type_traits>

#include "void.hpp"
#include "conjunction.hpp"

class EqualityComparable
{
  friend bool operator == (const EqualityComparable&, const EqualityComparable&);
};

template <typename T, typename _ = void>
struct is_equality_comparable : std::false_type {};

template <typename T>
struct is_equality_comparable 
  < T
  , void_t<decltype(std::declval<T>() == std::declval<T>())>
  > : std::true_type {};

static_assert(is_equality_comparable<EqualityComparable>::value, "Object with equlity operator doesnt satisfy is_equality_comparable");
static_assert(is_equality_comparable<int>::value, "int doesnt satisfy is_equality_comparable");
