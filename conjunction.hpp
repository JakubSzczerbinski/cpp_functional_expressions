#pragma once

#include <type_traits>

template <typename ... Bools>
struct conjunction : std::true_type {};

template <typename Bool>
struct conjunction<Bool> : std::conditional_t<bool(Bool::value), std::true_type, std::false_type> {};

template <typename Bool, typename ... Bools>
struct conjunction<Bool, Bools ...> : std::conditional_t<bool(Bool::value), conjunction<Bools ...>, std::false_type> {};

