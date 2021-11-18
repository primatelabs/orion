// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

// polyline clipping converter
// There an optimized Liang-Basky algorithm is used.
// The algorithm doesn't optimize the degenerate edges, i.e. it will never
// break a closed polyline into two or more ones, instead, there will be
// degenerate edges coinciding with the respective clipping boundaries.
// This is a sub-optimal solution, because that optimization would require
// extra, rather expensive math while the rasterizer tolerates it quite well,
// without any considerable overhead.
//

#ifndef ORION_CONV_CLIP_polyline_H__
#define ORION_CONV_CLIP_polyline_H__

#include "orion/basics.h"
#include "orion/conv_adaptor_vpgen.h"
#include "orion/vpgen_clip_polyline.h"

namespace orion {


template <class VertexSource>
struct conv_clip_polyline
: public conv_adaptor_vpgen<VertexSource, vpgen_clip_polyline> {
  typedef conv_adaptor_vpgen<VertexSource, vpgen_clip_polyline> base_type;

  conv_clip_polyline(VertexSource& vs)
  : conv_adaptor_vpgen<VertexSource, vpgen_clip_polyline>(vs)
  {
  }

  void clip_box(double x1, double y1, double x2, double y2)
  {
    base_type::vpgen().clip_box(x1, y1, x2, y2);
  }

  double x1() const
  {
    return base_type::vpgen().x1();
  }
  double y1() const
  {
    return base_type::vpgen().y1();
  }
  double x2() const
  {
    return base_type::vpgen().x2();
  }
  double y2() const
  {
    return base_type::vpgen().y2();
  }

private:
  conv_clip_polyline(const conv_clip_polyline<VertexSource>&);
  const conv_clip_polyline<VertexSource>& operator=(
    const conv_clip_polyline<VertexSource>&);
};
} // namespace orion

#endif
