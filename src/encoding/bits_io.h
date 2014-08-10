/**
 * @file  bits_io.h
 * @brief Low-level integer series (de-)serialization mechanisms
 */

#ifndef FPDELTA_ENCODING_BITS_IO_H
#define FPDELTA_ENCODING_BITS_IO_H

namespace fpdelta { namespace encodings {

/**
 * Give a view over a stream of bits offering a "stream-like"
 * interface with get, peek and advance methods.  
 */
template <typename ForwardIt = void*>
class BinaryReader
{
public:

  /**
   * Get next @p count bits and store their value as memory 
   * word into @p out, advancing position in the stream by
   * @p count bits forward. 
   *
   * Reading bits beyond last bits result emit 0s in output.
   *
   * T is only allowed to be an integral type.
   */
  template <typename T>
  inline size_t get (T& out, size_t count);
  
  /**
   * Extract next @p count bits from the underlying stream
   * and store their value into @p out without modifyint the
   * stream position.
   *
   * Reading bits beyond last bits result emit 0s in output.
   *
   * T is only allowed to be an integral type.
   */
  template <typename T>
  inline size_t peek (T& out, size_t count);

  /**
   * Move reading position by @p count. No boundary checks.
   * No compile if underlying stream is single pass. 
   */
  inline void advance (int offset);
  
  /**
   * Return true iff more bits are available in the stream
   * for reading.
   */
  bool is_valid () const;

  /**
   * identical to is_valid ()
   */
  operator bool () const;

  /**
   * Construct a BitView from iterator to fist, last   
   */
  template <typename FwdIt>
  static BitView<FwdIt> From (const FwdIt &first,
			      const FwdIt &last);

private:
  // Construct from factory
  BitView (ForwardIt, ForwardIt);

private:
  ForwardIt m_data;
  ForwardIt m_data_end;
  size_t    m_bit_offset;
};

}} // namespace fpdelta { namespace encodings {

#include "bits_io.inl"

#endif // FPDELTA_ENCODINGS_BITS_IO_H
