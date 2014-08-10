/**
 * @file  bits_io.inl
 * @brief Low-level integer series (de-)serialization mechanisms
 */

#include "detail_bits_io.inl"

#include <iterator_traits>

namespace fpdelta { namespace encodings {

////////////////////////////////////////////////////////////////
template <typename FwdIt>
inline size_t
BinaryReader<FwdIt>::peek (T& out, size_t count) const
{
  auto tmp = *this;
  return tmp.get (out, count);
}

////////////////////////////////////////////////////////////////
template <typename FwdIt>
inline size_t
BinaryReader<FwdIt>::get (T& out, size_t count)
{
  using value_type = 
    typename std::iterator_traits<FwdIt>::value_type;

  constexpr size_t word_size =
    detail::word_size <value_type>();

  size_t read = 0; // count of read bits
  
  out = 0;
  while (count && is_valid ())
  {
    // fetch current stream word
    auto word = *m_data;
    size_t to_read = std::min (count, word_size - m_bit_offset);

    word <<= (word_size - (m_bit_offset + to_read));
    word >>= (word_size - to_read);

    // append bits in output
    out |= (word << read);

    // advance stream position
    if (m_bit_offset + to_read < word_size)
    {
      m_bit_offset += to_read;
    }
    else
    {
      ++m_data;
      m_bit_offset = 0;
    }

    read += to_read;
    count -= to_read;
  }

  return read; 
}

////////////////////////////////////////////////////////////////
template <typename FwdIt>
inline void BinaryReader<FwdIt>::advance (size_t count)
{
  using value_type =
    std::iterator_traits<FwdIt>::value_type;

  constexpr size_t word_size =
    detail::log_word_size <value_type> ();

  const size_t to_offset = bit_offset + count;
  const size_t words_to_advance = to_offset >> log_word_size;

  m_bit_offset = to_offset - (word_to_advance << log_word_size);
  std::advance (m_data, words_to_advance);
}

////////////////////////////////////////////////////////////////
template <typename FwdIt>
bool BinaryReader<FwdIt>::is_valid () const
{
  return (m_data == m_data_end);
}

////////////////////////////////////////////////////////////////
template <typename FwdIt>
operator BinaryReader<FwdIt>::bool () const
{
  return is_valid ();
}

////////////////////////////////////////////////////////////////
template <typename FwdIt>
BinaryReader<FwdIt>::BinaryReader (ForwardIt first,
				   ForwardIt last)
: m_data (first)
, m_data_end (last)
, m_bit_offset (0)
{
}

////////////////////////////////////////////////////////////////
template <typename FwdIt>
static BinaryReader<FwdIt>::From (const FwdIt &first,
				  const FwdIt &last)
{
  return BinaryReader (first, last);
}

}} // namespace fpdelta { namespace encoding { 
