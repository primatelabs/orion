// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_PIXFMT_TRANSPOSER_H__
#define ORION_PIXFMT_TRANSPOSER_H__

#include "orion/basics.h"

namespace orion {

template <class PixFmt>
class pixfmt_transposer {
public:
  typedef PixFmt pixfmt_type;
  typedef typename pixfmt_type::color_type color_type;
  typedef typename pixfmt_type::row_data row_data;
  typedef typename color_type::value_type value_type;
  typedef typename color_type::calc_type calc_type;


  pixfmt_transposer()
  : m_pixf(0)
  {
  }
  explicit pixfmt_transposer(pixfmt_type& pixf)
  : m_pixf(&pixf)
  {
  }
  void attach(pixfmt_type& pixf)
  {
    m_pixf = &pixf;
  }


  AGG_INLINE unsigned width() const
  {
    return m_pixf->height();
  }
  AGG_INLINE unsigned height() const
  {
    return m_pixf->width();
  }


  AGG_INLINE color_type pixel(int x, int y) const
  {
    return m_pixf->pixel(y, x);
  }


  AGG_INLINE void copy_pixel(int x, int y, const color_type& c)
  {
    m_pixf->copy_pixel(y, x, c);
  }


  AGG_INLINE void blend_pixel(int x, int y, const color_type& c, int8u cover)
  {
    m_pixf->blend_pixel(y, x, c, cover);
  }


  AGG_INLINE void copy_hline(int x, int y, unsigned len, const color_type& c)
  {
    m_pixf->copy_vline(y, x, len, c);
  }


  AGG_INLINE void copy_vline(int x, int y, unsigned len, const color_type& c)
  {
    m_pixf->copy_hline(y, x, len, c);
  }


  AGG_INLINE void blend_hline(int x, int y, unsigned len, const color_type& c, int8u cover)
  {
    m_pixf->blend_vline(y, x, len, c, cover);
  }


  AGG_INLINE void blend_vline(int x, int y, unsigned len, const color_type& c, int8u cover)
  {
    m_pixf->blend_hline(y, x, len, c, cover);
  }


  AGG_INLINE void blend_solid_hspan(int x,
    int y,
    unsigned len,
    const color_type& c,
    const int8u* covers)
  {
    m_pixf->blend_solid_vspan(y, x, len, c, covers);
  }


  AGG_INLINE void blend_solid_vspan(int x,
    int y,
    unsigned len,
    const color_type& c,
    const int8u* covers)
  {
    m_pixf->blend_solid_hspan(y, x, len, c, covers);
  }


  AGG_INLINE void copy_color_hspan(int x, int y, unsigned len, const color_type* colors)
  {
    m_pixf->copy_color_vspan(y, x, len, colors);
  }


  AGG_INLINE void copy_color_vspan(int x, int y, unsigned len, const color_type* colors)
  {
    m_pixf->copy_color_hspan(y, x, len, colors);
  }


  AGG_INLINE void blend_color_hspan(int x,
    int y,
    unsigned len,
    const color_type* colors,
    const int8u* covers,
    int8u cover)
  {
    m_pixf->blend_color_vspan(y, x, len, colors, covers, cover);
  }


  AGG_INLINE void blend_color_vspan(int x,
    int y,
    unsigned len,
    const color_type* colors,
    const int8u* covers,
    int8u cover)
  {
    m_pixf->blend_color_hspan(y, x, len, colors, covers, cover);
  }

private:
  pixfmt_type* m_pixf;
};
} // namespace orion

#endif
