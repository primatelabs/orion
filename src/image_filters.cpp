// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#include "orion/image_filters.h"


namespace orion {

void image_filter_lut::realloc_lut(double radius)
{
  m_radius = radius;
  m_diameter = uceil(radius) * 2;
  m_start = -int(m_diameter / 2 - 1);
  unsigned size = m_diameter << image_subpixel_shift;
  if (size > m_weight_array.size()) {
    m_weight_array.resize(size);
  }
}


// This function normalizes integer values and corrects the rounding
// errors. It doesn't do anything with the source floating point values
// (m_weight_array_dbl), it corrects only integers according to the rule
// of 1.0 which means that any sum of pixel weights must be equal to 1.0.
// So, the filter function must produce a graph of the proper shape.

void image_filter_lut::normalize()
{
  unsigned i;
  int flip = 1;

  for (i = 0; i < image_subpixel_scale; i++) {
    for (;;) {
      int sum = 0;
      unsigned j;
      for (j = 0; j < m_diameter; j++) {
        sum += m_weight_array[j * image_subpixel_scale + i];
      }

      if (sum == image_filter_scale)
        break;

      double k = double(image_filter_scale) / double(sum);
      sum = 0;
      for (j = 0; j < m_diameter; j++) {
        sum += m_weight_array[j * image_subpixel_scale + i] =
          iround(m_weight_array[j * image_subpixel_scale + i] * k);
      }

      sum -= image_filter_scale;
      int inc = (sum > 0) ? -1 : 1;

      for (j = 0; j < m_diameter && sum; j++) {
        flip ^= 1;
        unsigned idx = flip ? m_diameter / 2 + j / 2 : m_diameter / 2 - j / 2;
        int v = m_weight_array[idx * image_subpixel_scale + i];
        if (v < image_filter_scale) {
          m_weight_array[idx * image_subpixel_scale + i] += inc;
          sum += inc;
        }
      }
    }
  }

  unsigned pivot = m_diameter << (image_subpixel_shift - 1);

  for (i = 0; i < pivot; i++) {
    m_weight_array[pivot + i] = m_weight_array[pivot - i];
  }
  unsigned end = (diameter() << image_subpixel_shift) - 1;
  m_weight_array[0] = m_weight_array[end];
}
} // namespace orion
