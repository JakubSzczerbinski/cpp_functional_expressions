#pragma once

#include <type_traits>

#include "void.hpp"

template <typename T, typename _ = void>
struct has_member_of_pointer_operator : std::false_type {};

template <typename T>
struct has_member_of_pointer_operator<
    T, void_t<decltype(std::declval<T>().operator->())>> : std::true_type {};

template <typename T>
struct has_member_of_pointer_operator<
    T, std::enable_if_t<std::is_pointer<T>::value, void>> : std::true_type {};
