// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_VCGEN_MARKERS_TERM_H__
#define ORION_VCGEN_MARKERS_TERM_H__

#include "orion/basics.h"
#include "orion/vertex_sequence.h"

namespace orion {


//
// See Implemantation agg_vcgen_markers_term.cpp
// Terminal markers generator (arrowhead/arrowtail)
//

class vcgen_markers_term {
public:
  vcgen_markers_term()
  : m_curr_id(0)
  , m_curr_idx(0)
  {
  }

  // Vertex Generator Interface
  void remove_all();
  void add_vertex(double x, double y, unsigned cmd);

  // Vertex Source Interface
  void rewind(unsigned path_id);
  unsigned vertex(double* x, double* y);

private:
  vcgen_markers_term(const vcgen_markers_term&);
  const vcgen_markers_term& operator=(const vcgen_markers_term&);

  struct coord_type {
    double x, y;

    coord_type()
    {
    }
    coord_type(double x_, double y_)
    : x(x_)
    , y(y_)
    {
    }
  };

  typedef pod_bvector<coord_type, 6> coord_storage;

  coord_storage m_markers;
  unsigned m_curr_id;
  unsigned m_curr_idx;
};
} // namespace orion

#endif
