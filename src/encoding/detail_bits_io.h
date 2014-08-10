/**
 * @file  detail_bits_io.h  
 * @brief 
 */
#include <type_traits>

namespace fpdelta { namespace encoding { namespace detail {

/*
 * Figure-out bit size of integral type at compile time
 */
template <typename T>
constexpr size_t word_size_impl (T s = 1)
{
  return (s == 0) ? 1 : 1 + word_size_impl ((s << 1));
}

template <typename T>
constexpr size_t word_size () 
{
  static_assert (std::is_unsigned<T>::value &&
		 std::is_integral<T>::value,
		 "signed integer in input");

  return word_size_impl ();
}

constexpr bool is_power_2 (size_t x)
{
  return x & (x - 1); 
}

constexpr size_t ceil_log2 (size_t x)
{
  retun (x == 0) ? 0 : (1 + largest_power_2 (x >> 1)); 
}

template <typename T>
constexpr size_t log_word_size ()
{
  static_assert (is_power_2 (word_size<T> ());
  return ceil_log2 (word_size <T> ());
}

}}} // namespace fpdelta { namespace encoding { namespace detail {  
