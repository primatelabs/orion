// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_GSV_TEXT_H__
#define ORION_GSV_TEXT_H__

#include "orion/array.h"
#include "orion/conv_stroke.h"
#include "orion/conv_transform.h"

namespace orion {


//
// See Implementation agg_gsv_text.cpp
//
class gsv_text {
  enum status { initial, next_char, start_glyph, glyph };

public:
  gsv_text();

  void font(const void* font);
  void flip(bool flip_y)
  {
    m_flip = flip_y;
  }
  void load_font(const char* file);
  void size(double height, double width = 0.0);
  void space(double space);
  void line_space(double line_space);
  void start_point(double x, double y);
  void text(const char* text);

  double text_width();

  void rewind(unsigned path_id);
  unsigned vertex(double* x, double* y);

private:
  // not supposed to be copied
  gsv_text(const gsv_text&);
  const gsv_text& operator=(const gsv_text&);

  int16u value(const int8u* p) const
  {
    int16u v;
    if (m_big_endian) {
      *(int8u*)&v = p[1];
      *((int8u*)&v + 1) = p[0];
    } else {
      *(int8u*)&v = p[0];
      *((int8u*)&v + 1) = p[1];
    }
    return v;
  }

private:
  double m_x;
  double m_y;
  double m_start_x;
  double m_width;
  double m_height;
  double m_space;
  double m_line_space;
  char m_chr[2];
  char* m_text;
  pod_array<char> m_text_buf;
  char* m_cur_chr;
  const void* m_font;
  pod_array<char> m_loaded_font;
  status m_status;
  bool m_big_endian;
  bool m_flip;
  int8u* m_indices;
  int8* m_glyphs;
  int8* m_bglyph;
  int8* m_eglyph;
  double m_w;
  double m_h;
};


template <class Transformer = trans_affine>
class gsv_text_outline {
public:
  gsv_text_outline(gsv_text& text, const Transformer& trans)
  : m_polyline(text)
  , m_trans(m_polyline, trans)
  {
  }

  void width(double w)
  {
    m_polyline.width(w);
  }

  void transformer(const Transformer* trans)
  {
    m_trans->transformer(trans);
  }

  void rewind(unsigned path_id)
  {
    m_trans.rewind(path_id);
    m_polyline.line_join(round_join);
    m_polyline.line_cap(round_cap);
  }

  unsigned vertex(double* x, double* y)
  {
    return m_trans.vertex(x, y);
  }

private:
  conv_stroke<gsv_text> m_polyline;
  conv_transform<conv_stroke<gsv_text>, Transformer> m_trans;
};
} // namespace orion


#endif
