// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_CONV_CONCAT_H__
#define ORION_CONV_CONCAT_H__

#include "orion/basics.h"

namespace orion {

// Concatenation of two paths. Usually used to combine lines or curves
// with markers such as arrowheads
template <class VS1, class VS2>
class conv_concat {
public:
  conv_concat(VS1& source1, VS2& source2)
  : m_source1(&source1)
  , m_source2(&source2)
  , m_status(2)
  {
  }
  void attach1(VS1& source)
  {
    m_source1 = &source;
  }
  void attach2(VS2& source)
  {
    m_source2 = &source;
  }


  void rewind(unsigned path_id)
  {
    m_source1->rewind(path_id);
    m_source2->rewind(0);
    m_status = 0;
  }

  unsigned vertex(double* x, double* y)
  {
    unsigned cmd;
    if (m_status == 0) {
      cmd = m_source1->vertex(x, y);
      if (!is_stop(cmd))
        return cmd;
      m_status = 1;
    }
    if (m_status == 1) {
      cmd = m_source2->vertex(x, y);
      if (!is_stop(cmd))
        return cmd;
      m_status = 2;
    }
    return path_cmd_stop;
  }

private:
  conv_concat(const conv_concat<VS1, VS2>&);
  const conv_concat<VS1, VS2>& operator=(const conv_concat<VS1, VS2>&);

  VS1* m_source1;
  VS2* m_source2;
  int m_status;
};
} // namespace orion


#endif
