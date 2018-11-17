#pragma once

#include <iterator>
#include <type_traits>
#include <vector>

#include "conjunction.hpp"
#include "empty.hpp"
#include "iterator.hpp"

template <typename T>
class OutputIterator {
 public:
  using value_type = T;
  using difference_type = int;
  using pointer = T *;
  using reference = const T &;
  using iterator_category = std::input_iterator_tag;
  const T &operator*();
  OutputIterator &operator++(int);
  OutputIterator &operator++();
};

template <typename T, typename _ = void>
struct is_output_iterator : std::false_type {};

template <typename T>
struct is_output_iterator<
    T,
    std::enable_if_t<
        conjunction<is_iterator<T>,
                    std::is_same<decltype(++(std::declval<T&>())), T &>,
                    std::is_convertible<decltype(std::declval<T&>()++),
                                        const T &>>::value,
        void_t<decltype(std::declval<T&>()++), decltype(++(std::declval<T&>())),
               decltype(*std::declval<T>()), decltype(*(std::declval<T&>()++))>>>
    : std::true_type {};

static_assert(is_output_iterator<OutputIterator<int>>::value,
              "OutputIterator doesnt satisfy is_output_iterator");
static_assert(is_output_iterator<std::vector<int>::iterator>::value,
              "Vector itertorr doesnt satisfy is_output_iterator");
static_assert(is_output_iterator<char*>::value,
              "char* doesnt satisfy output_iterator_requirement");
static_assert(not is_output_iterator<Empty>::value,
              "Empty object satisfies is_output_iterator");

