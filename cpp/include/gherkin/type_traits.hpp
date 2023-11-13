#include <optional>
#include <vector>

namespace gherkin {

template <
    typename T
>
struct is_cont {
  static const bool value = false;
};

template <
    typename T,
    typename Alloc
>
struct is_cont<std::vector<T,Alloc> > {
  static const bool value = true;
};


template <
    typename T
>
struct is_optional {
  static const bool value = false;
};

template <
    typename T
>
struct is_optional<std::optional<T> > {
  static const bool value = true;
};

template <
    typename T
>
inline
constexpr bool is_container_v = is_cont<T>::value;

template <
    typename T
>
inline
constexpr bool is_optional_v = is_optional<T>::value;

}