// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_PATH_LENGTH_H__
#define ORION_PATH_LENGTH_H__

#include "orion/math.h"

namespace orion {
template <class VertexSource>
double path_length(VertexSource& vs, unsigned path_id = 0)
{
  double len = 0.0;
  double start_x = 0.0;
  double start_y = 0.0;
  double x1 = 0.0;
  double y1 = 0.0;
  double x2 = 0.0;
  double y2 = 0.0;
  bool first = true;

  unsigned cmd;
  vs.rewind(path_id);
  while (!is_stop(cmd = vs.vertex(&x2, &y2))) {
    if (is_vertex(cmd)) {
      if (first || is_move_to(cmd)) {
        start_x = x2;
        start_y = y2;
      } else {
        len += calc_distance(x1, y1, x2, y2);
      }
      x1 = x2;
      y1 = y2;
      first = false;
    } else {
      if (is_close(cmd) && !first) {
        len += calc_distance(x1, y1, start_x, start_y);
      }
    }
  }
  return len;
}
} // namespace orion

#endif
