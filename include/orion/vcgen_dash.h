// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_VCGEN_DASH_H__
#define ORION_VCGEN_DASH_H__

#include "orion/basics.h"
#include "orion/vertex_sequence.h"

namespace orion {


//
// See Implementation agg_vcgen_dash.cpp
//
class vcgen_dash {
  enum max_dashes_e { max_dashes = 32 };

  enum status_e { initial, ready, polyline, stop };

public:
  typedef vertex_sequence<vertex_dist, 6> vertex_storage;

  vcgen_dash();

  void remove_all_dashes();
  void add_dash(double dash_len, double gap_len);
  void dash_start(double ds);

  void shorten(double s)
  {
    m_shorten = s;
  }
  double shorten() const
  {
    return m_shorten;
  }

  // Vertex Generator Interface
  void remove_all();
  void add_vertex(double x, double y, unsigned cmd);

  // Vertex Source Interface
  void rewind(unsigned path_id);
  unsigned vertex(double* x, double* y);

private:
  vcgen_dash(const vcgen_dash&);
  const vcgen_dash& operator=(const vcgen_dash&);

  void calc_dash_start(double ds);

  double m_dashes[max_dashes];
  double m_total_dash_len;
  unsigned m_num_dashes;
  double m_dash_start;
  double m_shorten;
  double m_curr_dash_start;
  unsigned m_curr_dash;
  double m_curr_rest;
  const vertex_dist* m_v1;
  const vertex_dist* m_v2;

  vertex_storage m_src_vertices;
  unsigned m_closed;
  status_e m_status;
  unsigned m_src_vertex;
};
} // namespace orion

#endif
