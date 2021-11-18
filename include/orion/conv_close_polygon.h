// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_CONV_CLOSE_POLYGON_H__
#define ORION_CONV_CLOSE_POLYGON_H__

#include "orion/basics.h"

namespace orion {


template <class VertexSource>
class conv_close_polygon {
public:
  explicit conv_close_polygon(VertexSource& vs)
  : m_source(&vs)
  {
  }
  void attach(VertexSource& source)
  {
    m_source = &source;
  }

  void rewind(unsigned path_id);
  unsigned vertex(double* x, double* y);

private:
  conv_close_polygon(const conv_close_polygon<VertexSource>&);
  const conv_close_polygon<VertexSource>& operator=(
    const conv_close_polygon<VertexSource>&);

  VertexSource* m_source;
  unsigned m_cmd[2];
  double m_x[2];
  double m_y[2];
  unsigned m_vertex;
  bool m_line_to;
};


template <class VertexSource>
void conv_close_polygon<VertexSource>::rewind(unsigned path_id)
{
  m_source->rewind(path_id);
  m_vertex = 2;
  m_line_to = false;
}


template <class VertexSource>
unsigned conv_close_polygon<VertexSource>::vertex(double* x, double* y)
{
  unsigned cmd = path_cmd_stop;
  for (;;) {
    if (m_vertex < 2) {
      *x = m_x[m_vertex];
      *y = m_y[m_vertex];
      cmd = m_cmd[m_vertex];
      ++m_vertex;
      break;
    }

    cmd = m_source->vertex(x, y);

    if (is_end_poly(cmd)) {
      cmd |= path_flags_close;
      break;
    }

    if (is_stop(cmd)) {
      if (m_line_to) {
        m_cmd[0] = path_cmd_end_poly | path_flags_close;
        m_cmd[1] = path_cmd_stop;
        m_vertex = 0;
        m_line_to = false;
        continue;
      }
      break;
    }

    if (is_move_to(cmd)) {
      if (m_line_to) {
        m_x[0] = 0.0;
        m_y[0] = 0.0;
        m_cmd[0] = path_cmd_end_poly | path_flags_close;
        m_x[1] = *x;
        m_y[1] = *y;
        m_cmd[1] = cmd;
        m_vertex = 0;
        m_line_to = false;
        continue;
      }
      break;
    }

    if (is_vertex(cmd)) {
      m_line_to = true;
      break;
    }
  }
  return cmd;
}
} // namespace orion

#endif
