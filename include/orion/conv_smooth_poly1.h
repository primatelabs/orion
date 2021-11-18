// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_CONV_SMOOTH_POLY1_H__
#define ORION_CONV_SMOOTH_POLY1_H__

#include "orion/basics.h"
#include "orion/conv_adaptor_vcgen.h"
#include "orion/conv_curve.h"
#include "orion/vcgen_smooth_poly1.h"


namespace orion {


template <class VertexSource>
struct conv_smooth_poly1
: public conv_adaptor_vcgen<VertexSource, vcgen_smooth_poly1> {
  typedef conv_adaptor_vcgen<VertexSource, vcgen_smooth_poly1> base_type;

  conv_smooth_poly1(VertexSource& vs)
  : conv_adaptor_vcgen<VertexSource, vcgen_smooth_poly1>(vs)
  {
  }

  void smooth_value(double v)
  {
    base_type::generator().smooth_value(v);
  }
  double smooth_value() const
  {
    return base_type::generator().smooth_value();
  }

private:
  conv_smooth_poly1(const conv_smooth_poly1<VertexSource>&);
  const conv_smooth_poly1<VertexSource>& operator=(
    const conv_smooth_poly1<VertexSource>&);
};


template <class VertexSource>
struct conv_smooth_poly1_curve
: public conv_curve<conv_smooth_poly1<VertexSource>> {
  conv_smooth_poly1_curve(VertexSource& vs)
  : conv_curve<conv_smooth_poly1<VertexSource>>(m_smooth)
  , m_smooth(vs)
  {
  }

  void smooth_value(double v)
  {
    m_smooth.generator().smooth_value(v);
  }
  double smooth_value() const
  {
    return m_smooth.generator().smooth_value();
  }

private:
  conv_smooth_poly1_curve(const conv_smooth_poly1_curve<VertexSource>&);
  const conv_smooth_poly1_curve<VertexSource>& operator=(
    const conv_smooth_poly1_curve<VertexSource>&);

  conv_smooth_poly1<VertexSource> m_smooth;
};
} // namespace orion


#endif
