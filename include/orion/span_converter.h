// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_SPAN_CONVERTER_H__
#define ORION_SPAN_CONVERTER_H__

#include "orion/basics.h"

namespace orion {

template <class SpanGenerator, class SpanConverter>
class span_converter {
public:
  typedef typename SpanGenerator::color_type color_type;

  span_converter(SpanGenerator& span_gen, SpanConverter& span_cnv)
  : m_span_gen(&span_gen)
  , m_span_cnv(&span_cnv)
  {
  }

  void attach_generator(SpanGenerator& span_gen)
  {
    m_span_gen = &span_gen;
  }
  void attach_converter(SpanConverter& span_cnv)
  {
    m_span_cnv = &span_cnv;
  }


  void prepare()
  {
    m_span_gen->prepare();
    m_span_cnv->prepare();
  }


  void generate(color_type* span, int x, int y, unsigned len)
  {
    m_span_gen->generate(span, x, y, len);
    m_span_cnv->generate(span, x, y, len);
  }

private:
  SpanGenerator* m_span_gen;
  SpanConverter* m_span_cnv;
};
} // namespace orion

#endif
