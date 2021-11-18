// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_SPAN_INTERPOLATOR_TRANS_H__
#define ORION_SPAN_INTERPOLATOR_TRANS_H__

#include "orion/basics.h"

namespace orion {

template <class Transformer, unsigned SubpixelShift = 8>
class span_interpolator_trans {
public:
  typedef Transformer trans_type;
  enum subpixel_scale_e {
    subpixel_shift = SubpixelShift,
    subpixel_scale = 1 << subpixel_shift
  };


  span_interpolator_trans()
  {
  }
  span_interpolator_trans(const trans_type& trans)
  : m_trans(&trans)
  {
  }
  span_interpolator_trans(const trans_type& trans, double x, double y, unsigned)
  : m_trans(&trans)
  {
    begin(x, y, 0);
  }


  const trans_type& transformer() const
  {
    return *m_trans;
  }
  void transformer(const trans_type& trans)
  {
    m_trans = &trans;
  }


  void begin(double x, double y, unsigned)
  {
    m_x = x;
    m_y = y;
    m_trans->transform(&x, &y);
    m_ix = iround(x * subpixel_scale);
    m_iy = iround(y * subpixel_scale);
  }


  void operator++()
  {
    m_x += 1.0;
    double x = m_x;
    double y = m_y;
    m_trans->transform(&x, &y);
    m_ix = iround(x * subpixel_scale);
    m_iy = iround(y * subpixel_scale);
  }


  void coordinates(int* x, int* y) const
  {
    *x = m_ix;
    *y = m_iy;
  }

private:
  const trans_type* m_trans;
  double m_x;
  double m_y;
  int m_ix;
  int m_iy;
};
} // namespace orion

#endif
