#pragma once

#include <type_traits>
#include <vector>

#include "conjunction.hpp"
#include "equality_comparable.hpp"
#include "iterator.hpp"
#include "void.hpp"

template <typename T> class InputIterator {
public:
  using value_type = T;
  using reference = T&;
  T& operator*();
  T &operator->();
  InputIterator &operator++(int);
  InputIterator &operator++();
  friend bool operator==<InputIterator>(const InputIterator &, const InputIterator &);
  friend bool operator!=<InputIterator>(const InputIterator &, const InputIterator &);
};

template <typename T, typename _ = void>
struct is_input_iterator : std::false_type {};

template <typename T>
struct is_input_iterator<
    T, std::enable_if_t<
           conjunction<is_iterator<T>, is_equality_comparable<T>, std::is_same<decltype(++(std::declval<T>())), T&>, std::is_convertible<decltype(*(std::declval<T>()++)), typename std::iterator_traits<T>::value_type>>::value,
           void_t<decltype(std::declval<T>()++),
                  decltype(++(std::declval<T>()))>>> : std::true_type {};

static_assert(is_input_iterator<InputIterator<int>>::value,
              "InputIterator doesnt satisfy is_input_iterator");
static_assert(is_input_iterator<std::vector<int>::iterator>::value,
              "Vector itertorr doesnt satisfy is_input_iterator");
