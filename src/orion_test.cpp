// Copyright (C) 2004-2020 Primate Labs Inc.  All Rights Reserved.

#include "base/image.h"
#include "base/image/compare.h"
#include "base/png_codec.h"
#include "base/sleep.h"
#include "base/test.h"
#include "base/timer.h"
#include "orion/pixfmt_rgba.h"
#include "orion/rasterizer_scanline_aa.h"
#include "orion/renderer_base.h"
#include "orion/renderer_scanline.h"
#include "orion/scanline_p.h"

namespace {

class Path {
protected:
  std::vector<double> points_;
  int offset_;

public:
  Path(const std::vector<double>& points)
  : points_(points)
  {
  }

  void rewind(int path = 0)
  {
    offset_ = 0;
  }

  unsigned vertex(double* x, double* y)
  {
    if (offset_ < points_.size()) {
      *x = points_[offset_++];
      *y = points_[offset_++];
      return (offset_ == 2 ? orion::path_cmd_move_to : orion::path_cmd_line_to);
    }
    return orion::path_cmd_stop;
  }
};

} // namespace

class OrionTest : public base::Test {
};

TEST_F(OrionTest, Smoke)
{
  typedef orion::pixfmt_rgba32 PixelFormat;
  typedef orion::renderer_base<PixelFormat> RendererBaseType;

  orion::rendering_buffer render_buffer;
  PixelFormat pixel_format;
  RendererBaseType render_base;

  Image<uint8_t> image(100, 100, kImageFormatRGBA);
  assert(PixelFormat::pix_width == 4);

  render_buffer.attach(image.data(), image.width(), image.height(), image.stride());
  pixel_format.attach(render_buffer);
  render_base.attach(pixel_format);

  // Clear the render buffer using transparent white as the background color.
  const orion::rgba8 background_color(0xff, 0xff, 0xff, 0);
  render_base.clear(background_color);

  orion::rasterizer_scanline_aa<> ras;
  orion::scanline_p8 scanline;

  ras.auto_close(false);

  // Draw a green square.
  {
    Path path({
      // clang-format off
      0, 0,
      0, 40,
      40, 40,
      40, 0,
      0, 0
      // clang-format on
    });

    ras.reset();
    ras.add_path(path);

    const orion::rgba8 color(0, 0xff, 0, 0xff);
    orion::render_scanlines_aa_solid(ras, scanline, render_base, color);
  }

  // Draw a red star.
  {
    Path path({
      // clang-format off
      50, 3,
      20, 97,
      95, 37,
      5, 37,
      80, 97,
      50, 3
      // clang-format on
    });

    ras.reset();
    ras.add_path(path);

    const orion::rgba8 color(0xff, 0, 0, 0xff);
    orion::render_scanlines_aa_solid(ras, scanline, render_base, color);
  }

  Image<uint8_t> reference = manager_->find_image("test/orion/smoke.png");
  EXPECT_TRUE(base::similar(image, reference, 0));
}
