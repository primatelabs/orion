// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_CONV_STROKE_H__
#define ORION_CONV_STROKE_H__

#include "orion/basics.h"
#include "orion/conv_adaptor_vcgen.h"
#include "orion/vcgen_stroke.h"

namespace orion {


template <class VertexSource, class Markers = null_markers>
struct conv_stroke
: public conv_adaptor_vcgen<VertexSource, vcgen_stroke, Markers> {
  typedef Markers marker_type;
  typedef conv_adaptor_vcgen<VertexSource, vcgen_stroke, Markers> base_type;

  conv_stroke(VertexSource& vs)
  : conv_adaptor_vcgen<VertexSource, vcgen_stroke, Markers>(vs)
  {
  }

  void line_cap(line_cap_e lc)
  {
    base_type::generator().line_cap(lc);
  }
  void line_join(line_join_e lj)
  {
    base_type::generator().line_join(lj);
  }
  void inner_join(inner_join_e ij)
  {
    base_type::generator().inner_join(ij);
  }

  line_cap_e line_cap() const
  {
    return base_type::generator().line_cap();
  }
  line_join_e line_join() const
  {
    return base_type::generator().line_join();
  }
  inner_join_e inner_join() const
  {
    return base_type::generator().inner_join();
  }

  void width(double w)
  {
    base_type::generator().width(w);
  }
  void miter_limit(double ml)
  {
    base_type::generator().miter_limit(ml);
  }
  void miter_limit_theta(double t)
  {
    base_type::generator().miter_limit_theta(t);
  }
  void inner_miter_limit(double ml)
  {
    base_type::generator().inner_miter_limit(ml);
  }
  void approximation_scale(double as)
  {
    base_type::generator().approximation_scale(as);
  }

  double width() const
  {
    return base_type::generator().width();
  }
  double miter_limit() const
  {
    return base_type::generator().miter_limit();
  }
  double inner_miter_limit() const
  {
    return base_type::generator().inner_miter_limit();
  }
  double approximation_scale() const
  {
    return base_type::generator().approximation_scale();
  }

  void shorten(double s)
  {
    base_type::generator().shorten(s);
  }
  double shorten() const
  {
    return base_type::generator().shorten();
  }

private:
  conv_stroke(const conv_stroke<VertexSource, Markers>&);
  const conv_stroke<VertexSource, Markers>& operator=(
    const conv_stroke<VertexSource, Markers>&);
};
} // namespace orion

#endif
