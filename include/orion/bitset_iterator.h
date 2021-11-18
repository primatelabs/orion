// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_BITSET_ITERATOR_H__
#define ORION_BITSET_ITERATOR_H__

#include "orion/basics.h"

namespace orion {

class bitset_iterator {
public:
  bitset_iterator(const int8u* bits, unsigned offset = 0)
  : m_bits(bits + (offset >> 3))
  , m_mask(0x80 >> (offset & 7))
  {
  }

  void operator++()
  {
    m_mask >>= 1;
    if (m_mask == 0) {
      ++m_bits;
      m_mask = 0x80;
    }
  }

  unsigned bit() const
  {
    return (*m_bits) & m_mask;
  }

private:
  const int8u* m_bits;
  int8u m_mask;
};
} // namespace orion

#endif
