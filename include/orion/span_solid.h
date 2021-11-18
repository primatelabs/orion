// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_SPAN_SOLID_H__
#define ORION_SPAN_SOLID_H__

#include "orion/basics.h"

namespace orion {

template <class ColorT>
class span_solid {
public:
  typedef ColorT color_type;


  void color(const color_type& c)
  {
    m_color = c;
  }
  const color_type& color() const
  {
    return m_color;
  }


  void prepare()
  {
  }


  void generate(color_type* span, int x, int y, unsigned len)
  {
    do {
      *span++ = m_color;
    } while (--len);
  }

private:
  color_type m_color;
};
} // namespace orion

#endif
