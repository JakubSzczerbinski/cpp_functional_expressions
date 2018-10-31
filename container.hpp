#include <type_traits>
#include <vector>

template <typename ... Bools>
struct conjunction : std::true_type {};

template <typename Bool>
struct conjunction<Bool> : std::conditional_t<bool(Bool::value), std::true_type, std::false_type> {};

template <typename Bool, typename ... Bools>
struct conjunction<Bool, Bools ...> : std::conditional_t<bool(Bool::value), conjunction<Bools ...>, std::false_type> {};

template <typename T>
class Iterator;

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
        std::is_same<typename Container::const_reference, const Element&>
      >::value,
      std::void_t<
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
        decltype(Container() == Container()),
        decltype(Container() != Container())
      > 
    > 
  > : std::true_type {};
static_assert(is_container<Container<int>, int>::value, "Object does not meet Container requirement");
static_assert(is_container<std::vector<int>, int>::value, "Object does not meet Container requirement");

