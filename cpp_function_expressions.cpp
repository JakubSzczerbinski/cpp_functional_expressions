#include <boost/type_index.hpp>
#include <iostream>
#include <type_traits>
#include <vector>

using namespace boost::typeindex;

template <typename Container, typename Function>
class MapExp {
 public:
  MapExp(Container&& container, Function&& func)
      : container_(container), function_(func) {}
  
  typedef typename std::remove_reference<Container>::type ContainerT;
  typedef
      typename std::result_of<Function(typename ContainerT::value_type)>::type
          value_type;

  std::size_t size() { return container_.size(); }

  class const_iterator {
   public:
    const_iterator(const MapExp<Container, Function>& me,
                   typename ContainerT::const_iterator&& it)
        : mapExp_(me), it_(it) {}
    const_iterator& operator++() {
      ++it_;
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator result(*this);
      it_++;
      return result;
    }

    value_type operator*() { return mapExp_.function_(*it_); }

    value_type operator->() const { return mapExp_.function_(*it_); }

    bool operator==(const_iterator other) const { return it_ == other.it_; }

    bool operator!=(const_iterator other) const { return it_ != other.it_; }

   private:
    const MapExp<Container, Function>& mapExp_;
    typename ContainerT::const_iterator it_;
    friend MapExp<Container, Function>;
  };
  const_iterator begin() { return const_iterator(*this, container_.begin()); }
  const_iterator end() { return const_iterator(*this, container_.end()); }

 private:
  const Container container_;
  const Function function_;
};

template <typename Container, typename Function>
MapExp<Container, Function> map(Container&& container, Function&& func) {
  return MapExp<Container, Function>(std::forward<Container>(container),
                                     std::forward<Function>(func));
}

int main() {
  std::vector<int> vec = {1, 2};
  auto vec_map = map(std::vector<int>{1, 2, 3, 4}, [](int i) { return i * i; });
  for (auto&& i : vec_map) {
    std::cout << i << std::endl;
  }
}
