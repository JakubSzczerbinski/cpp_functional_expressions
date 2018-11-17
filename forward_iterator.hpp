#pragma once

#include <iterator>
#include <type_traits>

#include "conjunction.hpp"
#include "empty.hpp"
#include "input_iterator.hpp"
#include "output_iterator.hpp"
#include "void.hpp"

template <typename T>
class ForwardIterator {
 public:
  ForwardIterator();
  using value_type = T;
  using difference_type = int;
  using pointer = T *;
  using reference = T &;
  using iterator_category = std::forward_iterator_tag;
  T &operator*();
  T &operator->();
  ForwardIterator operator++(int);
  ForwardIterator &operator++();
};

template <typename T>
bool operator==(const ForwardIterator<T> &, const ForwardIterator<T> &);

template <typename T>
bool operator!=(const ForwardIterator<T> &, const ForwardIterator<T> &);

template <typename T, typename _ = void>
struct is_forward_iterator : std::false_type {};

template <typename T>
struct is_forward_iterator<
    T,
    std::enable_if_t<
        conjunction<
            is_input_iterator<T>, std::is_default_constructible<T>,
            std::is_same<
                typename std::iterator_traits<T>::reference,
                std::conditional_t<
                    is_output_iterator<T>::value,
                    typename std::iterator_traits<T>::value_type &,
                    const typename std::iterator_traits<T>::value_type &>>,
            std::is_same<decltype(std::declval<T &>()++), T>,
            std::is_same<decltype(*(std::declval<T &>()++)),
                         typename std::iterator_traits<T>::reference>,
            std::is_convertible<decltype(std::declval<T &>()++),
                                const T &>>::value,
               void>>
    : std::true_type {};

static_assert(is_forward_iterator<ForwardIterator<int>>::value,
              "OutputIterator doesnt satisfy is_output_iterator");
static_assert(is_forward_iterator<int*>::value,
              "int* doesnt satisfy is_output_iterator");
static_assert(is_forward_iterator<std::vector<int>::iterator>::value,
              "Vector iterator doesnt satisfy is_forward_iterator");
static_assert(not is_output_iterator<Empty>::value,
              "Vector iterator doesnt satisfy is_output_iterator");

