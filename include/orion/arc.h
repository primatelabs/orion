// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_ARC_H__
#define ORION_ARC_H__

#include <math.h>

#include "orion/basics.h"

namespace orion {


//
// See Implementation agg_arc.cpp
//
class arc {
public:
  arc()
  : m_scale(1.0)
  , m_initialized(false)
  {
  }
  arc(double x, double y, double rx, double ry, double a1, double a2, bool ccw = true);

  void init(double x, double y, double rx, double ry, double a1, double a2, bool ccw = true);

  void approximation_scale(double s);
  double approximation_scale() const
  {
    return m_scale;
  }

  void rewind(unsigned);
  unsigned vertex(double* x, double* y);

private:
  void normalize(double a1, double a2, bool ccw);

  double m_x;
  double m_y;
  double m_rx;
  double m_ry;
  double m_angle;
  double m_start;
  double m_end;
  double m_scale;
  double m_da;
  bool m_ccw;
  bool m_initialized;
  unsigned m_path_cmd;
};
} // namespace orion


#endif
