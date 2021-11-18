// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_VCGEN_BSPLINE_H__
#define ORION_VCGEN_BSPLINE_H__

#include "orion/array.h"
#include "orion/basics.h"
#include "orion/bspline.h"


namespace orion {


class vcgen_bspline {
  enum status_e { initial, ready, polygon, end_poly, stop };

public:
  typedef pod_bvector<point_d, 6> vertex_storage;

  vcgen_bspline();

  void interpolation_step(double v)
  {
    m_interpolation_step = v;
  }
  double interpolation_step() const
  {
    return m_interpolation_step;
  }

  // Vertex Generator Interface
  void remove_all();
  void add_vertex(double x, double y, unsigned cmd);

  // Vertex Source Interface
  void rewind(unsigned path_id);
  unsigned vertex(double* x, double* y);

private:
  vcgen_bspline(const vcgen_bspline&);
  const vcgen_bspline& operator=(const vcgen_bspline&);

  vertex_storage m_src_vertices;
  bspline m_spline_x;
  bspline m_spline_y;
  double m_interpolation_step;
  unsigned m_closed;
  status_e m_status;
  unsigned m_src_vertex;
  double m_cur_abscissa;
  double m_max_abscissa;
};
} // namespace orion


#endif
