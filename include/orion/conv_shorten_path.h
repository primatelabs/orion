// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_CONV_SHORTEN_PATH_H__
#define ORION_CONV_SHORTEN_PATH_H__

#include "orion/basics.h"
#include "orion/conv_adaptor_vcgen.h"
#include "orion/vcgen_vertex_sequence.h"

namespace orion {


template <class VertexSource>
class conv_shorten_path
: public conv_adaptor_vcgen<VertexSource, vcgen_vertex_sequence> {
public:
  typedef conv_adaptor_vcgen<VertexSource, vcgen_vertex_sequence> base_type;

  conv_shorten_path(VertexSource& vs)
  : conv_adaptor_vcgen<VertexSource, vcgen_vertex_sequence>(vs)
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
  conv_shorten_path(const conv_shorten_path<VertexSource>&);
  const conv_shorten_path<VertexSource>& operator=(
    const conv_shorten_path<VertexSource>&);
};
} // namespace orion

#endif
