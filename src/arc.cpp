// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#include "orion/arc.h"

#include <math.h>


namespace orion {

arc::arc(double x, double y, double rx, double ry, double a1, double a2, bool ccw)
: m_x(x)
, m_y(y)
, m_rx(rx)
, m_ry(ry)
, m_scale(1.0)
{
  normalize(a1, a2, ccw);
}


void arc::init(double x, double y, double rx, double ry, double a1, double a2, bool ccw)
{
  m_x = x;
  m_y = y;
  m_rx = rx;
  m_ry = ry;
  normalize(a1, a2, ccw);
}


void arc::approximation_scale(double s)
{
  m_scale = s;
  if (m_initialized) {
    normalize(m_start, m_end, m_ccw);
  }
}


void arc::rewind(unsigned)
{
  m_path_cmd = path_cmd_move_to;
  m_angle = m_start;
}


unsigned arc::vertex(double* x, double* y)
{
  if (is_stop(m_path_cmd))
    return path_cmd_stop;
  if ((m_angle < m_end - m_da / 4) != m_ccw) {
    *x = m_x + cos(m_end) * m_rx;
    *y = m_y + sin(m_end) * m_ry;
    m_path_cmd = path_cmd_stop;
    return path_cmd_line_to;
  }

  *x = m_x + cos(m_angle) * m_rx;
  *y = m_y + sin(m_angle) * m_ry;

  m_angle += m_da;

  unsigned pf = m_path_cmd;
  m_path_cmd = path_cmd_line_to;
  return pf;
}


void arc::normalize(double a1, double a2, bool ccw)
{
  double ra = (fabs(m_rx) + fabs(m_ry)) / 2;
  m_da = acos(ra / (ra + 0.125 / m_scale)) * 2;
  if (ccw) {
    while (a2 < a1)
      a2 += pi * 2.0;
  } else {
    while (a1 < a2)
      a1 += pi * 2.0;
    m_da = -m_da;
  }
  m_ccw = ccw;
  m_start = a1;
  m_end = a2;
  m_initialized = true;
}
} // namespace orion
