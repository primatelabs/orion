// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#include "orion/trans_warp_magnifier.h"

#include <math.h>

namespace orion {


void trans_warp_magnifier::transform(double* x, double* y) const
{
  double dx = *x - m_xc;
  double dy = *y - m_yc;
  double r = sqrt(dx * dx + dy * dy);
  if (r < m_radius) {
    *x = m_xc + dx * m_magn;
    *y = m_yc + dy * m_magn;
    return;
  }

  double m = (r + m_radius * (m_magn - 1.0)) / r;
  *x = m_xc + dx * m;
  *y = m_yc + dy * m;
}


void trans_warp_magnifier::inverse_transform(double* x, double* y) const
{
  // New version by Andrew Skalkin

  double dx = *x - m_xc;
  double dy = *y - m_yc;
  double r = sqrt(dx * dx + dy * dy);

  if (r < m_radius * m_magn) {
    *x = m_xc + dx / m_magn;
    *y = m_yc + dy / m_magn;
  } else {
    double rnew = r - m_radius * (m_magn - 1.0);
    *x = m_xc + rnew * dx / r;
    *y = m_yc + rnew * dy / r;
  }

  // Old version

  // trans_warp_magnifier t(*this);
  // t.magnification(1.0 / m_magn);
  // t.radius(m_radius * m_magn);
  // t.transform(x, y);
}
} // namespace orion
