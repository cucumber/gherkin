#include <type_traits>

namespace gherkin {

namespace detail {

template <
    template <typename> class Container,
    template <typename> class Other,
    typename T
>
std::is_same<Container<T>, Other<T>>
test_is_container(Other<T>*);

template <
    template <typename> class Container,
    typename T
>
std::false_type test_is_container(T*);

} // namespace detail

template <
    template <typename> class C,
    typename T
>
using is_container = decltype(
    detail::test_is_container<C>(static_cast<T*>(nullptr))
);

template <
    template <typename> class C,
    typename T
>
inline
constexpr bool is_container_v = is_container<C, T>::value;

}
