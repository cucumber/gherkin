#include <type_traits>

namespace cucumber::gherkin {

template <
    typename T,
    template <typename...> typename Primary
>
struct is_specialization_of : std::false_type {};

template <
    template <typename...> typename Primary,
    typename... Args
>
struct is_specialization_of<Primary<Args...>, Primary> : std::true_type {};

template <
    typename T,
    template <typename...> class Primary
>
using
is_specialization_of_t = is_specialization_of<T, Primary>;

template <
    typename T,
    template <typename...> class Primary
>
inline
constexpr bool
is_specialization_of_v = is_specialization_of_t<T, Primary>::value;

}
