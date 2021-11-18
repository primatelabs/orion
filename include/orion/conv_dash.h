// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_CONV_DASH_H__
#define ORION_CONV_DASH_H__

#include "orion/basics.h"
#include "orion/conv_adaptor_vcgen.h"
#include "orion/vcgen_dash.h"

namespace orion {


template <class VertexSource, class Markers = null_markers>
struct conv_dash : public conv_adaptor_vcgen<VertexSource, vcgen_dash, Markers> {
  typedef Markers marker_type;
  typedef conv_adaptor_vcgen<VertexSource, vcgen_dash, Markers> base_type;

  conv_dash(VertexSource& vs)
  : conv_adaptor_vcgen<VertexSource, vcgen_dash, Markers>(vs)
  {
  }

  void remove_all_dashes()
  {
    base_type::generator().remove_all_dashes();
  }

  void add_dash(double dash_len, double gap_len)
  {
    base_type::generator().add_dash(dash_len, gap_len);
  }

  void dash_start(double ds)
  {
    base_type::generator().dash_start(ds);
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
  conv_dash(const conv_dash<VertexSource, Markers>&);
  const conv_dash<VertexSource, Markers>& operator=(
    const conv_dash<VertexSource, Markers>&);
};
} // namespace orion

#endif
