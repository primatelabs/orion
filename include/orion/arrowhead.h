// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_ARROWHEAD_H__
#define ORION_ARROWHEAD_H__

#include "orion/basics.h"

namespace orion {


//
// See implementation agg_arrowhead.cpp
//
class arrowhead {
public:
  arrowhead();

  void head(double d1, double d2, double d3, double d4)
  {
    m_head_d1 = d1;
    m_head_d2 = d2;
    m_head_d3 = d3;
    m_head_d4 = d4;
    m_head_flag = true;
  }

  void head()
  {
    m_head_flag = true;
  }
  void no_head()
  {
    m_head_flag = false;
  }

  void tail(double d1, double d2, double d3, double d4)
  {
    m_tail_d1 = d1;
    m_tail_d2 = d2;
    m_tail_d3 = d3;
    m_tail_d4 = d4;
    m_tail_flag = true;
  }

  void tail()
  {
    m_tail_flag = true;
  }
  void no_tail()
  {
    m_tail_flag = false;
  }

  void rewind(unsigned path_id);
  unsigned vertex(double* x, double* y);

private:
  double m_head_d1;
  double m_head_d2;
  double m_head_d3;
  double m_head_d4;
  double m_tail_d1;
  double m_tail_d2;
  double m_tail_d3;
  double m_tail_d4;
  bool m_head_flag;
  bool m_tail_flag;
  double m_coord[16];
  unsigned m_cmd[8];
  unsigned m_curr_id;
  unsigned m_curr_coord;
};
} // namespace orion

#endif
