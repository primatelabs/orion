// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_CONV_TRANSFORM_H__
#define ORION_CONV_TRANSFORM_H__

#include "orion/basics.h"
#include "orion/trans_affine.h"

namespace orion {


template <class VertexSource, class Transformer = trans_affine>
class conv_transform {
public:
  conv_transform(VertexSource& source, const Transformer& tr)
  : m_source(&source)
  , m_trans(&tr)
  {
  }
  void attach(VertexSource& source)
  {
    m_source = &source;
  }

  void rewind(unsigned path_id)
  {
    m_source->rewind(path_id);
  }

  unsigned vertex(double* x, double* y)
  {
    unsigned cmd = m_source->vertex(x, y);
    if (is_vertex(cmd)) {
      m_trans->transform(x, y);
    }
    return cmd;
  }

  void transformer(const Transformer& tr)
  {
    m_trans = &tr;
  }

private:
  conv_transform(const conv_transform<VertexSource>&);
  const conv_transform<VertexSource>& operator=(
    const conv_transform<VertexSource>&);

  VertexSource* m_source;
  const Transformer* m_trans;
};
} // namespace orion

#endif
