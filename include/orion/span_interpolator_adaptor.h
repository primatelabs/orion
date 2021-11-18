// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_SPAN_INTERPOLATOR_ADAPTOR_H__
#define ORION_SPAN_INTERPOLATOR_ADAPTOR_H__

#include "orion/basics.h"

namespace orion {


template <class Interpolator, class Distortion>
class span_interpolator_adaptor : public Interpolator {
public:
  typedef Interpolator base_type;
  typedef typename base_type::trans_type trans_type;
  typedef Distortion distortion_type;


  span_interpolator_adaptor()
  {
  }
  span_interpolator_adaptor(const trans_type& trans, const distortion_type& dist)
  : base_type(trans)
  , m_distortion(&dist)
  {
  }


  span_interpolator_adaptor(const trans_type& trans,
    const distortion_type& dist,
    double x,
    double y,
    unsigned len)
  : base_type(trans, x, y, len)
  , m_distortion(&dist)
  {
  }


  const distortion_type& distortion() const
  {
    return *m_distortion;
  }


  void distortion(const distortion_type& dist)
  {
    m_distortion = dist;
  }


  void coordinates(int* x, int* y) const
  {
    base_type::coordinates(x, y);
    m_distortion->calculate(x, y);
  }

private:
  const distortion_type* m_distortion;
};
} // namespace orion


#endif
