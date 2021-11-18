// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_SPAN_ALLOCATOR_H__
#define ORION_SPAN_ALLOCATOR_H__

#include "orion/array.h"

namespace orion {

template <class ColorT>
class span_allocator {
public:
  typedef ColorT color_type;


  AGG_INLINE color_type* allocate(unsigned span_len)
  {
    if (span_len > m_span.size()) {
      // To reduce the number of reallocs we align the
      // span_len to 256 color elements.
      // Well, I just like this number and it looks reasonable.

      m_span.resize(((span_len + 255) >> 8) << 8);
    }
    return &m_span[0];
  }

  AGG_INLINE color_type* span()
  {
    return &m_span[0];
  }
  AGG_INLINE unsigned max_span_len() const
  {
    return m_span.size();
  }

private:
  pod_array<color_type> m_span;
};
} // namespace orion


#endif
