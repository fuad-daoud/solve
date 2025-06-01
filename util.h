#include <iostream>
#include <iterator>
#include <ostream>

// Overload << operator for std::pair
template <typename T1, typename T2>
std::ostream &operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
  os << "{" << p.first << ", " << p.second << "}";
  return os;
}

template <typename Container> void print(const Container &container) {
  std::cout << "[";

  auto it = std::begin(container);
  auto end_it = std::end(container);

  if (it != end_it) {
    std::cout << *it;
    ++it;

    while (it != end_it) {
      std::cout << ", " << *it;
      ++it;
    }
  }

  std::cout << "]" << std::endl;
}

// Overload << operator for any iterable container
template <typename Container>
auto operator<<(std::ostream &os, const Container &container) ->
    typename std::enable_if<
        !std::is_same<Container, std::string>::value &&
            !std::is_array<Container>::value &&
            !std::is_same<typename std::decay<Container>::type,
                          const char *>::value &&
            !std::is_same<typename std::decay<Container>::type, char *>::value,
        decltype(std::begin(container), std::end(container), os)>::type {

  os << "[";

  auto it = std::begin(container);
  auto end_it = std::end(container);

  if (it != end_it) {
    os << *it;
    ++it;

    while (it != end_it) {
      os << ", " << *it;
      ++it;
    }
  }

  os << "]";
  return os;
}
