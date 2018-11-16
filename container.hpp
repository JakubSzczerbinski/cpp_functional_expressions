#pragma once

#include <type_traits>
#include <vector>

#include "conjunction.hpp"
#include "void.hpp"
#include "iterator.hpp"
#include "empty.hpp"


template <typename T>
class Container
{
  public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using diffrence_type = int;
    using size_type = unsigned int;
    using iterator = Iterator<T>;
    using const_iterator = const iterator;
    Container();
    Container(const Container<T>&);
    ~Container();
    Container<T>& operator=(const Container<T>&);
    bool operator==(const Container<T>&);
    bool operator!=(const Container<T>&);
    const_reference cbegin();
    const_reference cend();
    reference begin();
    reference end();
    size_type size();
    size_type max_size();
    bool empty();
    void swap(Container<T>&);
};

template <typename T>
void swap(Container<T>, Container<T>);




template <typename Container, typename Element, typename _ = void>
struct is_container : std::false_type {};

template <typename Container, typename Element>
struct is_container <
  Container,
  Element,
  std::enable_if_t
    <
      conjunction<
        std::is_same<typename Container::value_type, Element>,
        std::is_same<typename Container::reference, Element&>,
        std::is_same<typename Container::const_reference, const Element&>,
        is_iterator<typename Container::iterator>
      >::value,
      void_t<
        decltype(Container()),
        decltype(Container(Container())),
        decltype(Container().begin()),
        decltype(Container().end()),
        decltype(Container().cbegin()),
        decltype(Container().cend()),
        decltype(Container().size()),
        decltype(Container().max_size()),
        decltype(Container().empty()),
        decltype(std::declval<Container>().swap(std::declval<Container&>())),
        decltype(swap(std::declval<Container&>(), std::declval<Container&>())),
        decltype(bool(Container() == Container())),
        decltype(bool(Container() != Container()))
      > 
    > 
  > : std::true_type {};

/* is_container should be true Container<T> and T for all T, but we cant test that, so we test some instances :P */
static_assert(is_container<Container<int>, int>::value, "Container interface doesnt pass is_container check");
static_assert(is_container<Container<char>, char>::value, "Container interface doesnt pass is_container check");

/* is_container should fail for class that doesnt implement container interface */
static_assert(not is_container<Empty, int>::value, "Object that doesnt implement Container interface passes is_container check");

