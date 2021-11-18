// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_CONV_SEGMENTATOR_H__
#define ORION_CONV_SEGMENTATOR_H__

#include "orion/basics.h"
#include "orion/conv_adaptor_vpgen.h"
#include "orion/vpgen_segmentator.h"

namespace orion {


template <class VertexSource>
struct conv_segmentator
: public conv_adaptor_vpgen<VertexSource, vpgen_segmentator> {
  typedef conv_adaptor_vpgen<VertexSource, vpgen_segmentator> base_type;

  conv_segmentator(VertexSource& vs)
  : conv_adaptor_vpgen<VertexSource, vpgen_segmentator>(vs)
  {
  }

  void approximation_scale(double s)
  {
    base_type::vpgen().approximation_scale(s);
  }
  double approximation_scale() const
  {
    return base_type::vpgen().approximation_scale();
  }

private:
  conv_segmentator(const conv_segmentator<VertexSource>&);
  const conv_segmentator<VertexSource>& operator=(
    const conv_segmentator<VertexSource>&);
};
} // namespace orion

#endif
