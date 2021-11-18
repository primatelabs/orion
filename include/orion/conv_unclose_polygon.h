// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_CONV_UNCLOSE_POLYGON_H__
#define ORION_CONV_UNCLOSE_POLYGON_H__

#include "orion/basics.h"

namespace orion {

template <class VertexSource>
class conv_unclose_polygon {
public:
  explicit conv_unclose_polygon(VertexSource& vs)
  : m_source(&vs)
  {
  }
  void attach(VertexSource& source)
  {
    m_source = &source;
  }

  void rewind(unsigned path_id)
  {
    m_source->rewind(path_id);
  }

  unsigned vertex(double* x, double* y)
  {
    unsigned cmd = m_source->vertex(x, y);
    if (is_end_poly(cmd))
      cmd &= ~path_flags_close;
    return cmd;
  }

private:
  conv_unclose_polygon(const conv_unclose_polygon<VertexSource>&);
  const conv_unclose_polygon<VertexSource>& operator=(
    const conv_unclose_polygon<VertexSource>&);

  VertexSource* m_source;
};
} // namespace orion

#endif
