// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_CONV_MARKER_ADAPTOR_H__
#define ORION_CONV_MARKER_ADAPTOR_H__

#include "orion/basics.h"
#include "orion/conv_adaptor_vcgen.h"
#include "orion/vcgen_vertex_sequence.h"

namespace orion {


template <class VertexSource, class Markers = null_markers>
struct conv_marker_adaptor
: public conv_adaptor_vcgen<VertexSource, vcgen_vertex_sequence, Markers> {
  typedef Markers marker_type;
  typedef conv_adaptor_vcgen<VertexSource, vcgen_vertex_sequence, Markers> base_type;

  conv_marker_adaptor(VertexSource& vs)
  : conv_adaptor_vcgen<VertexSource, vcgen_vertex_sequence, Markers>(vs)
  {
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
  conv_marker_adaptor(const conv_marker_adaptor<VertexSource, Markers>&);
  const conv_marker_adaptor<VertexSource, Markers>& operator=(
    const conv_marker_adaptor<VertexSource, Markers>&);
};
} // namespace orion

#endif
