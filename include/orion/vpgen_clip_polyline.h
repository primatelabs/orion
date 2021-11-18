// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_VPGEN_CLIP_POLYLINE_H__
#define ORION_VPGEN_CLIP_POLYLINE_H__

#include "orion/basics.h"

namespace orion {


//
// See Implementation agg_vpgen_clip_polyline.cpp
//
class vpgen_clip_polyline {
public:
  vpgen_clip_polyline()
  : m_clip_box(0, 0, 1, 1)
  , m_x1(0)
  , m_y1(0)
  , m_num_vertices(0)
  , m_vertex(0)
  , m_move_to(false)
  {
  }

  void clip_box(double x1, double y1, double x2, double y2)
  {
    m_clip_box.x1 = x1;
    m_clip_box.y1 = y1;
    m_clip_box.x2 = x2;
    m_clip_box.y2 = y2;
    m_clip_box.normalize();
  }

  double x1() const
  {
    return m_clip_box.x1;
  }
  double y1() const
  {
    return m_clip_box.y1;
  }
  double x2() const
  {
    return m_clip_box.x2;
  }
  double y2() const
  {
    return m_clip_box.y2;
  }

  static bool auto_close()
  {
    return false;
  }
  static bool auto_unclose()
  {
    return true;
  }

  void reset();
  void move_to(double x, double y);
  void line_to(double x, double y);
  unsigned vertex(double* x, double* y);

private:
  rect_d m_clip_box;
  double m_x1;
  double m_y1;
  double m_x[2];
  double m_y[2];
  unsigned m_cmd[2];
  unsigned m_num_vertices;
  unsigned m_vertex;
  bool m_move_to;
};
} // namespace orion


#endif
