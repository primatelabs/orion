// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_SPAN_GRADIENT_ALPHA_H__
#define ORION_SPAN_GRADIENT_ALPHA_H__

#include "orion/span_gradient.h"

namespace orion {

template <class ColorT, class Interpolator, class GradientF, class AlphaF>
class span_gradient_alpha {
public:
  typedef Interpolator interpolator_type;
  typedef ColorT color_type;
  typedef typename color_type::value_type alpha_type;

  enum downscale_shift_e {
    downscale_shift = interpolator_type::subpixel_shift - gradient_subpixel_shift
  };


  span_gradient_alpha()
  {
  }


  span_gradient_alpha(interpolator_type& inter,
    const GradientF& gradient_function,
    const AlphaF& alpha_function,
    double d1,
    double d2)
  : m_interpolator(&inter)
  , m_gradient_function(&gradient_function)
  , m_alpha_function(&alpha_function)
  , m_d1(iround(d1 * gradient_subpixel_scale))
  , m_d2(iround(d2 * gradient_subpixel_scale))
  {
  }


  interpolator_type& interpolator()
  {
    return *m_interpolator;
  }
  const GradientF& gradient_function() const
  {
    return *m_gradient_function;
  }
  const AlphaF& alpha_function() const
  {
    return *m_alpha_function;
  }
  double d1() const
  {
    return double(m_d1) / gradient_subpixel_scale;
  }
  double d2() const
  {
    return double(m_d2) / gradient_subpixel_scale;
  }


  void interpolator(interpolator_type& i)
  {
    m_interpolator = &i;
  }
  void gradient_function(const GradientF& gf)
  {
    m_gradient_function = &gf;
  }
  void alpha_function(const AlphaF& af)
  {
    m_alpha_function = &af;
  }
  void d1(double v)
  {
    m_d1 = iround(v * gradient_subpixel_scale);
  }
  void d2(double v)
  {
    m_d2 = iround(v * gradient_subpixel_scale);
  }


  void prepare()
  {
  }


  void generate(color_type* span, int x, int y, unsigned len)
  {
    int dd = m_d2 - m_d1;
    if (dd < 1)
      dd = 1;
    m_interpolator->begin(x + 0.5, y + 0.5, len);
    do {
      m_interpolator->coordinates(&x, &y);
      int d = m_gradient_function->calculate(x >> downscale_shift,
        y >> downscale_shift,
        m_d2);
      d = ((d - m_d1) * (int)m_alpha_function->size()) / dd;
      if (d < 0)
        d = 0;
      if (d >= (int)m_alpha_function->size())
        d = m_alpha_function->size() - 1;
      span->a = (*m_alpha_function)[d];
      ++span;
      ++(*m_interpolator);
    } while (--len);
  }

private:
  interpolator_type* m_interpolator;
  const GradientF* m_gradient_function;
  const AlphaF* m_alpha_function;
  int m_d1;
  int m_d2;
};


template <class ColorT>
struct gradient_alpha_x {
  typedef typename ColorT::value_type alpha_type;
  alpha_type operator[](alpha_type x) const
  {
    return x;
  }
};


struct gradient_alpha_x_u8 {
  typedef int8u alpha_type;
  alpha_type operator[](alpha_type x) const
  {
    return x;
  }
};


struct gradient_alpha_one_munus_x_u8 {
  typedef int8u alpha_type;
  alpha_type operator[](alpha_type x) const
  {
    return 255 - x;
  }
};
} // namespace orion

#endif
