// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_PATTERN_FILTERS_RGBA8_H__
#define ORION_PATTERN_FILTERS_RGBA8_H__

#include "orion/basics.h"
#include "orion/color_rgba.h"
#include "orion/line_aa_basics.h"


namespace orion {


template <class ColorT>
struct pattern_filter_nn {
  typedef ColorT color_type;
  static unsigned dilation()
  {
    return 0;
  }

  static void AGG_INLINE pixel_low_res(color_type const* const* buf,
    color_type* p,
    int x,
    int y)
  {
    *p = buf[y][x];
  }

  static void AGG_INLINE pixel_high_res(color_type const* const* buf,
    color_type* p,
    int x,
    int y)
  {
    *p = buf[y >> line_subpixel_shift][x >> line_subpixel_shift];
  }
};

typedef pattern_filter_nn<rgba8> pattern_filter_nn_rgba8;
typedef pattern_filter_nn<rgba16> pattern_filter_nn_rgba16;


template <class ColorT>
struct pattern_filter_bilinear_rgba {
  typedef ColorT color_type;
  typedef typename color_type::value_type value_type;
  typedef typename color_type::calc_type calc_type;


  static unsigned dilation()
  {
    return 1;
  }

  static AGG_INLINE void pixel_low_res(color_type const* const* buf,
    color_type* p,
    int x,
    int y)
  {
    *p = buf[y][x];
  }

  static AGG_INLINE void pixel_high_res(color_type const* const* buf,
    color_type* p,
    int x,
    int y)
  {
    calc_type r, g, b, a;
    r = g = b = a = line_subpixel_scale * line_subpixel_scale / 2;

    calc_type weight;
    int x_lr = x >> line_subpixel_shift;
    int y_lr = y >> line_subpixel_shift;

    x &= line_subpixel_mask;
    y &= line_subpixel_mask;
    const color_type* ptr = buf[y_lr] + x_lr;

    weight = (line_subpixel_scale - x) * (line_subpixel_scale - y);
    r += weight * ptr->r;
    g += weight * ptr->g;
    b += weight * ptr->b;
    a += weight * ptr->a;

    ++ptr;

    weight = x * (line_subpixel_scale - y);
    r += weight * ptr->r;
    g += weight * ptr->g;
    b += weight * ptr->b;
    a += weight * ptr->a;

    ptr = buf[y_lr + 1] + x_lr;

    weight = (line_subpixel_scale - x) * y;
    r += weight * ptr->r;
    g += weight * ptr->g;
    b += weight * ptr->b;
    a += weight * ptr->a;

    ++ptr;

    weight = x * y;
    r += weight * ptr->r;
    g += weight * ptr->g;
    b += weight * ptr->b;
    a += weight * ptr->a;

    p->r = (value_type)(r >> line_subpixel_shift * 2);
    p->g = (value_type)(g >> line_subpixel_shift * 2);
    p->b = (value_type)(b >> line_subpixel_shift * 2);
    p->a = (value_type)(a >> line_subpixel_shift * 2);
  }
};

typedef pattern_filter_bilinear_rgba<rgba8> pattern_filter_bilinear_rgba8;
typedef pattern_filter_bilinear_rgba<rgba16> pattern_filter_bilinear_rgba16;
} // namespace orion

#endif
