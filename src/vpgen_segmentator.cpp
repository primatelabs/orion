// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#include "orion/vpgen_segmentator.h"

#include <math.h>

namespace orion {

void vpgen_segmentator::move_to(double x, double y)
{
  m_x1 = x;
  m_y1 = y;
  m_dx = 0.0;
  m_dy = 0.0;
  m_dl = 2.0;
  m_ddl = 2.0;
  m_cmd = path_cmd_move_to;
}

void vpgen_segmentator::line_to(double x, double y)
{
  m_x1 += m_dx;
  m_y1 += m_dy;
  m_dx = x - m_x1;
  m_dy = y - m_y1;
  double len = sqrt(m_dx * m_dx + m_dy * m_dy) * m_approximation_scale;
  if (len < 1e-30)
    len = 1e-30;
  m_ddl = 1.0 / len;
  m_dl = (m_cmd == path_cmd_move_to) ? 0.0 : m_ddl;
  if (m_cmd == path_cmd_stop)
    m_cmd = path_cmd_line_to;
}

unsigned vpgen_segmentator::vertex(double* x, double* y)
{
  if (m_cmd == path_cmd_stop)
    return path_cmd_stop;

  unsigned cmd = m_cmd;
  m_cmd = path_cmd_line_to;
  if (m_dl >= 1.0 - m_ddl) {
    m_dl = 1.0;
    m_cmd = path_cmd_stop;
    *x = m_x1 + m_dx;
    *y = m_y1 + m_dy;
    return cmd;
  }
  *x = m_x1 + m_dx * m_dl;
  *y = m_y1 + m_dy * m_dl;
  m_dl += m_ddl;
  return cmd;
}
} // namespace orion
