#pragma once

#include <type_traits>
#include <vector>

#include "conjunction.hpp"
#include "empty.hpp"
#include "equality_comparable.hpp"
#include "has_member_of_pointer_operator.hpp"
#include "iterator.hpp"
#include "void.hpp"

template <typename T>
class InputIterator {
 public:
  using value_type = T;
  using difference_type = int;
  using pointer = T *;
  using reference = T &;
  using iterator_category = std::input_iterator_tag;
  T &operator*();
  T &operator->();
  InputIterator &operator++(int);
  InputIterator &operator++();
};

template <typename T>
bool operator==(const InputIterator<T> &, const InputIterator<T> &);

template <typename T>
bool operator!=(const InputIterator<T> &, const InputIterator<T> &);

template <typename T, typename _ = void>
struct is_input_iterator : std::false_type {};

template <typename T>
struct is_input_iterator<
    T,
    std::enable_if_t<
        conjunction<
            is_iterator<T>, is_equality_comparable<T>,
            std::is_same<decltype(++(std::declval<T &>())), T &>,
            std::is_convertible<decltype(*(std::declval<T &>()++)),
                                typename std::iterator_traits<T>::value_type>,
            has_member_of_pointer_operator<T>,
            disjunction<std::is_convertible<
                            decltype(*std::declval<T>()),
                            typename std::iterator_traits<T>::value_type>,
                        std::is_convertible<decltype(*std::declval<T>()),
                                            typename std::iterator_traits<
                                                T>::reference>>>::value,
        void_t<decltype(std::declval<T &>()++),
               decltype(++(std::declval<T &>()))>>> : std::true_type {};

static_assert(is_input_iterator<InputIterator<int>>::value,
              "InputIterator doesnt satisfy is_input_iterator");
static_assert(is_input_iterator<std::vector<int>::iterator>::value,
              "Vector iterator doesnt satisfy is_input_iterator");
static_assert(is_input_iterator<char *>::value,
              "char* doesnt satisfy is_input_iterator");
static_assert(not is_input_iterator<Empty>::value,
              "Empty object satisfies is_input_iterator");

