// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_VPGEN_SEGMENTATOR_H__
#define ORION_VPGEN_SEGMENTATOR_H__

#include <math.h>

#include "orion/basics.h"

namespace orion {


//
// See Implementation agg_vpgen_segmentator.cpp
//
class vpgen_segmentator {
public:
  vpgen_segmentator()
  : m_approximation_scale(1.0)
  {
  }

  void approximation_scale(double s)
  {
    m_approximation_scale = s;
  }
  double approximation_scale() const
  {
    return m_approximation_scale;
  }

  static bool auto_close()
  {
    return false;
  }
  static bool auto_unclose()
  {
    return false;
  }

  void reset()
  {
    m_cmd = path_cmd_stop;
  }
  void move_to(double x, double y);
  void line_to(double x, double y);
  unsigned vertex(double* x, double* y);

private:
  double m_approximation_scale;
  double m_x1;
  double m_y1;
  double m_dx;
  double m_dy;
  double m_dl;
  double m_ddl;
  unsigned m_cmd;
};
} // namespace orion

#endif
