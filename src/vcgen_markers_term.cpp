// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#include "orion/vcgen_markers_term.h"

namespace orion {


void vcgen_markers_term::remove_all()
{
  m_markers.remove_all();
}


void vcgen_markers_term::add_vertex(double x, double y, unsigned cmd)
{
  if (is_move_to(cmd)) {
    if (m_markers.size() & 1) {
      // Initial state, the first coordinate was added.
      // If two of more calls of start_vertex() occures
      // we just modify the last one.
      m_markers.modify_last(coord_type(x, y));
    } else {
      m_markers.add(coord_type(x, y));
    }
  } else {
    if (is_vertex(cmd)) {
      if (m_markers.size() & 1) {
        // Initial state, the first coordinate was added.
        // Add three more points, 0,1,1,0
        m_markers.add(coord_type(x, y));
        m_markers.add(m_markers[m_markers.size() - 1]);
        m_markers.add(m_markers[m_markers.size() - 3]);
      } else {
        if (m_markers.size()) {
          // Replace two last points: 0,1,1,0 -> 0,1,2,1
          m_markers[m_markers.size() - 1] = m_markers[m_markers.size() - 2];
          m_markers[m_markers.size() - 2] = coord_type(x, y);
        }
      }
    }
  }
}


void vcgen_markers_term::rewind(unsigned path_id)
{
  m_curr_id = path_id * 2;
  m_curr_idx = m_curr_id;
}


unsigned vcgen_markers_term::vertex(double* x, double* y)
{
  if (m_curr_id > 2 || m_curr_idx >= m_markers.size()) {
    return path_cmd_stop;
  }
  const coord_type& c = m_markers[m_curr_idx];
  *x = c.x;
  *y = c.y;
  if (m_curr_idx & 1) {
    m_curr_idx += 3;
    return path_cmd_line_to;
  }
  ++m_curr_idx;
  return path_cmd_move_to;
}
} // namespace orion
