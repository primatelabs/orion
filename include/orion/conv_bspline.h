// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_CONV_BSPLINE_H__
#define ORION_CONV_BSPLINE_H__

#include "orion/basics.h"
#include "orion/conv_adaptor_vcgen.h"
#include "orion/vcgen_bspline.h"


namespace orion {


template <class VertexSource>
struct conv_bspline : public conv_adaptor_vcgen<VertexSource, vcgen_bspline> {
  typedef conv_adaptor_vcgen<VertexSource, vcgen_bspline> base_type;

  conv_bspline(VertexSource& vs)
  : conv_adaptor_vcgen<VertexSource, vcgen_bspline>(vs)
  {
  }

  void interpolation_step(double v)
  {
    base_type::generator().interpolation_step(v);
  }
  double interpolation_step() const
  {
    return base_type::generator().interpolation_step();
  }

private:
  conv_bspline(const conv_bspline<VertexSource>&);
  const conv_bspline<VertexSource>& operator=(const conv_bspline<VertexSource>&);
};
} // namespace orion


#endif
