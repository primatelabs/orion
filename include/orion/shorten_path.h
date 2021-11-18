// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_SHORTEN_PATH_H__
#define ORION_SHORTEN_PATH_H__

#include "orion/basics.h"
#include "orion/vertex_sequence.h"

namespace orion {


template <class VertexSequence>
void shorten_path(VertexSequence& vs, double s, unsigned closed = 0)
{
  typedef typename VertexSequence::value_type vertex_type;

  if (s > 0.0 && vs.size() > 1) {
    double d;
    int n = int(vs.size() - 2);
    while (n) {
      d = vs[n].dist;
      if (d > s)
        break;
      vs.remove_last();
      s -= d;
      --n;
    }
    if (vs.size() < 2) {
      vs.remove_all();
    } else {
      n = vs.size() - 1;
      vertex_type& prev = vs[n - 1];
      vertex_type& last = vs[n];
      d = (prev.dist - s) / prev.dist;
      double x = prev.x + (last.x - prev.x) * d;
      double y = prev.y + (last.y - prev.y) * d;
      last.x = x;
      last.y = y;
      if (!prev(last))
        vs.remove_last();
      vs.close(closed != 0);
    }
  }
}
} // namespace orion

#endif
