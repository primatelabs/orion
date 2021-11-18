cmake_minimum_required(VERSION 3.5)

project(orion CXX)

# Soname
# MAJOR is incremented when symbols are removed or changed in an incompatible way
# MINOR is incremented when new symbols are added
set(PROJECT_MAJOR 0)
set(PROJECT_MINOR 0)

set(SOURCE_ORION
  src/arc.cpp
  src/arrowhead.cpp
  src/bezier_arc.cpp
  src/bspline.cpp
  src/curves.cpp
  src/embedded_raster_fonts.cpp
  src/gsv_text.cpp
  src/image_filters.cpp
  src/line_aa_basics.cpp
  src/line_profile_aa.cpp
  src/rounded_rect.cpp
  src/sqrt_tables.cpp
  src/trans_affine.cpp
  src/trans_double_path.cpp
  src/trans_single_path.cpp
  src/trans_warp_magnifier.cpp
  src/vcgen_bspline.cpp
  src/vcgen_contour.cpp
  src/vcgen_dash.cpp
  src/vcgen_markers_term.cpp
  src/vcgen_smooth_poly1.cpp
  src/vcgen_stroke.cpp
  src/vpgen_clip_polygon.cpp
  src/vpgen_clip_polyline.cpp
  src/vpgen_segmentator.cpp
)

set(HEADER_ORION
  include/orion/alpha_mask_u8.h
  include/orion/arc.h
  include/orion/array.h
  include/orion/arrowhead.h
  include/orion/basics.h
  include/orion/bezier_arc.h
  include/orion/bitset_iterator.h
  include/orion/blur.h
  include/orion/bounding_rect.h
  include/orion/bspline.h
  include/orion/clip_liang_barsky.h
  include/orion/color_gray.h
  include/orion/color_rgba.h
  include/orion/config.h
  include/orion/conv_adaptor_vcgen.h
  include/orion/conv_adaptor_vpgen.h
  include/orion/conv_bspline.h
  include/orion/conv_clip_polygon.h
  include/orion/conv_clip_polyline.h
  include/orion/conv_close_polygon.h
  include/orion/conv_concat.h
  include/orion/conv_contour.h
  include/orion/conv_curve.h
  include/orion/conv_dash.h
  include/orion/conv_marker.h
  include/orion/conv_marker_adaptor.h
  include/orion/conv_segmentator.h
  include/orion/conv_shorten_path.h
  include/orion/conv_smooth_poly1.h
  include/orion/conv_stroke.h
  include/orion/conv_transform.h
  include/orion/conv_unclose_polygon.h
  include/orion/curves.h
  include/orion/dda_line.h
  include/orion/ellipse.h
  include/orion/ellipse_bresenham.h
  include/orion/embedded_raster_fonts.h
  include/orion/font_cache_manager.h
  include/orion/gamma_functions.h
  include/orion/gamma_lut.h
  include/orion/glyph_raster_bin.h
  include/orion/gradient_lut.h
  include/orion/gsv_text.h
  include/orion/image_accessors.h
  include/orion/image_filters.h
  include/orion/line_aa_basics.h
  include/orion/math.h
  include/orion/math_stroke.h
  include/orion/path_length.h
  include/orion/path_storage.h
  include/orion/path_storage_integer.h
  include/orion/pattern_filters_rgba.h
  include/orion/pixfmt_amask_adaptor.h
  include/orion/pixfmt_gray.h
  include/orion/pixfmt_rgb.h
  include/orion/pixfmt_rgb_packed.h
  include/orion/pixfmt_rgba.h
  include/orion/pixfmt_transposer.h
  include/orion/rasterizer_cells_aa.h
  include/orion/rasterizer_compound_aa.h
  include/orion/rasterizer_outline.h
  include/orion/rasterizer_outline_aa.h
  include/orion/rasterizer_scanline_aa.h
  include/orion/rasterizer_sl_clip.h
  include/orion/renderer_base.h
  include/orion/renderer_markers.h
  include/orion/renderer_mclip.h
  include/orion/renderer_outline_aa.h
  include/orion/renderer_outline_image.h
  include/orion/renderer_primitives.h
  include/orion/renderer_raster_text.h
  include/orion/renderer_scanline.h
  include/orion/rendering_buffer.h
  include/orion/rendering_buffer_dynarow.h
  include/orion/rounded_rect.h
  include/orion/scanline_bin.h
  include/orion/scanline_boolean_algebra.h
  include/orion/scanline_p.h
  include/orion/scanline_storage_aa.h
  include/orion/scanline_storage_bin.h
  include/orion/scanline_u.h
  include/orion/shorten_path.h
  include/orion/simul_eq.h
  include/orion/span_allocator.h
  include/orion/span_converter.h
  include/orion/span_gouraud.h
  include/orion/span_gouraud_gray.h
  include/orion/span_gouraud_rgba.h
  include/orion/span_gradient.h
  include/orion/span_gradient_alpha.h
  include/orion/span_image_filter.h
  include/orion/span_image_filter_gray.h
  include/orion/span_image_filter_rgb.h
  include/orion/span_image_filter_rgba.h
  include/orion/span_interpolator_adaptor.h
  include/orion/span_interpolator_linear.h
  include/orion/span_interpolator_persp.h
  include/orion/span_interpolator_trans.h
  include/orion/span_pattern_gray.h
  include/orion/span_pattern_rgb.h
  include/orion/span_pattern_rgba.h
  include/orion/span_solid.h
  include/orion/span_subdiv_adaptor.h
  include/orion/trans_affine.h
  include/orion/trans_bilinear.h
  include/orion/trans_double_path.h
  include/orion/trans_perspective.h
  include/orion/trans_single_path.h
  include/orion/trans_viewport.h
  include/orion/trans_warp_magnifier.h
  include/orion/vcgen_bspline.h
  include/orion/vcgen_contour.h
  include/orion/vcgen_dash.h
  include/orion/vcgen_markers_term.h
  include/orion/vcgen_smooth_poly1.h
  include/orion/vcgen_stroke.h
  include/orion/vcgen_vertex_sequence.h
  include/orion/vertex_sequence.h
  include/orion/vpgen_clip_polygon.h
  include/orion/vpgen_clip_polyline.h
  include/orion/vpgen_segmentator.h
)

set(PROJECT_LIB_VERSION ${PROJECT_MAJOR}.${PROJECT_MINOR}.0)
set(PROJECT_SO_VERSION ${PROJECT_MAJOR})

add_library(${PROJECT_NAME} ${SOURCE_ORION})
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_LIB_VERSION} SOVERSION ${PROJECT_SO_VERSION})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 14
    PUBLIC_HEADER "${HEADER_ORION}"
)

# Export orion includes.
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

