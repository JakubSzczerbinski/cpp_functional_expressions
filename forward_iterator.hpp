#pragma once

#include <type_traits>
#include "iterator.hpp"
#include "void.hpp"
#include "empty.hpp"
#include "conjunction.hpp"

template <typename T>
class ForwardIterator
{};

template <typename T, typename _ = void>
struct is_forward_iterator : std::false_type {};

