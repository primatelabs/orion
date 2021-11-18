// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_ROUNDED_RECT_H__
#define ORION_ROUNDED_RECT_H__

#include "orion/arc.h"
#include "orion/basics.h"

namespace orion {

//
// See Implemantation agg_rounded_rect.cpp
//
class rounded_rect {
public:
  rounded_rect()
  {
  }
  rounded_rect(double x1, double y1, double x2, double y2, double r);

  void rect(double x1, double y1, double x2, double y2);
  void radius(double r);
  void radius(double rx, double ry);
  void radius(double rx_bottom, double ry_bottom, double rx_top, double ry_top);
  void radius(double rx1,
    double ry1,
    double rx2,
    double ry2,
    double rx3,
    double ry3,
    double rx4,
    double ry4);
  void normalize_radius();

  void approximation_scale(double s)
  {
    m_arc.approximation_scale(s);
  }
  double approximation_scale() const
  {
    return m_arc.approximation_scale();
  }

  void rewind(unsigned);
  unsigned vertex(double* x, double* y);

private:
  double m_x1;
  double m_y1;
  double m_x2;
  double m_y2;
  double m_rx1;
  double m_ry1;
  double m_rx2;
  double m_ry2;
  double m_rx3;
  double m_ry3;
  double m_rx4;
  double m_ry4;
  unsigned m_status;
  arc m_arc;
};
} // namespace orion

#endif
