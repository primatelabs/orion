// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_TRANS_SINGLE_PATH_H__
#define ORION_TRANS_SINGLE_PATH_H__

#include "orion/basics.h"
#include "orion/vertex_sequence.h"

namespace orion {

// See also: agg_trans_single_path.cpp
//

class trans_single_path {
  enum status_e { initial, making_path, ready };

public:
  typedef vertex_sequence<vertex_dist, 6> vertex_storage;

  trans_single_path();


  void base_length(double v)
  {
    m_base_length = v;
  }
  double base_length() const
  {
    return m_base_length;
  }


  void preserve_x_scale(bool f)
  {
    m_preserve_x_scale = f;
  }
  bool preserve_x_scale() const
  {
    return m_preserve_x_scale;
  }


  void reset();
  void move_to(double x, double y);
  void line_to(double x, double y);
  void finalize_path();


  template <class VertexSource>
  void add_path(VertexSource& vs, unsigned path_id = 0)
  {
    double x;
    double y;

    unsigned cmd;
    vs.rewind(path_id);
    while (!is_stop(cmd = vs.vertex(&x, &y))) {
      if (is_move_to(cmd)) {
        move_to(x, y);
      } else {
        if (is_vertex(cmd)) {
          line_to(x, y);
        }
      }
    }
    finalize_path();
  }


  double total_length() const;
  void transform(double* x, double* y) const;

private:
  vertex_storage m_src_vertices;
  double m_base_length;
  double m_kindex;
  status_e m_status;
  bool m_preserve_x_scale;
};
} // namespace orion

#endif
