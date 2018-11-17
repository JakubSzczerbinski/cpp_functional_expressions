#pragma once

#include <iterator>
#include <type_traits>
#include <vector>

#include "empty.hpp"
#include "void.hpp"

template <typename T>
class Iterator {
 public:
  T operator*();
  Iterator& operator++();
  using value_type = T;
  using difference_type = int;
  using pointer = T*;
  using reference = T&;
  class iterator_tag {};
  using iterator_category = iterator_tag;
};

template <typename Iterator, typename _ = void>
struct is_iterator : std::false_type {};

template <typename Iterator>
struct is_iterator<
    Iterator,
    std::enable_if_t<
        std::is_same<decltype(++(std::declval<Iterator&>())), Iterator&>::value,
        void_t<decltype(*std::declval<Iterator>()),
               typename std::iterator_traits<Iterator>::value_type,
               typename std::iterator_traits<Iterator>::difference_type,
               typename std::iterator_traits<Iterator>::pointer,
               typename std::iterator_traits<Iterator>::reference,
               typename std::iterator_traits<Iterator>::iterator_category>>>
    : std::true_type {};

static_assert(is_iterator<Iterator<int>>::value,
              "Iterator interface does not meet iterator requirements");
static_assert(is_iterator<std::vector<int>::iterator>::value,
              "Iterator interface does not meet iterator requirements");
static_assert(is_iterator<int*>::value,
              "Iterator interface does not meet iterator requirements");
static_assert(not is_iterator<Empty>::value,
              "Empty interface does meet iterator requirements");

