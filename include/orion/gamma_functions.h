// Copyright (C) 2002-2005 Maxim Shmanarev (http://www.antigrain.com)
// Copyright (c) 2004-2021 Primate Labs Inc.
// All rights reserved.
//
// Use of this source code is governed by the BSD 3-Clause License that can
// be found in the LICENSE file.

#ifndef ORION_GAMMA_FUNCTIONS_H__
#define ORION_GAMMA_FUNCTIONS_H__

#include <math.h>

#include "orion/basics.h"

namespace orion {

struct gamma_none {
  double operator()(double x) const
  {
    return x;
  }
};


class gamma_power {
public:
  gamma_power()
  : m_gamma(1.0)
  {
  }
  gamma_power(double g)
  : m_gamma(g)
  {
  }

  void gamma(double g)
  {
    m_gamma = g;
  }
  double gamma() const
  {
    return m_gamma;
  }

  double operator()(double x) const
  {
    return pow(x, m_gamma);
  }

private:
  double m_gamma;
};


class gamma_threshold {
public:
  gamma_threshold()
  : m_threshold(0.5)
  {
  }
  gamma_threshold(double t)
  : m_threshold(t)
  {
  }

  void threshold(double t)
  {
    m_threshold = t;
  }
  double threshold() const
  {
    return m_threshold;
  }

  double operator()(double x) const
  {
    return (x < m_threshold) ? 0.0 : 1.0;
  }

private:
  double m_threshold;
};


class gamma_linear {
public:
  gamma_linear()
  : m_start(0.0)
  , m_end(1.0)
  {
  }
  gamma_linear(double s, double e)
  : m_start(s)
  , m_end(e)
  {
  }

  void set(double s, double e)
  {
    m_start = s;
    m_end = e;
  }
  void start(double s)
  {
    m_start = s;
  }
  void end(double e)
  {
    m_end = e;
  }
  double start() const
  {
    return m_start;
  }
  double end() const
  {
    return m_end;
  }

  double operator()(double x) const
  {
    if (x < m_start)
      return 0.0;
    if (x > m_end)
      return 1.0;
    return (x - m_start) / (m_end - m_start);
  }

private:
  double m_start;
  double m_end;
};


class gamma_multiply {
public:
  gamma_multiply()
  : m_mul(1.0)
  {
  }
  gamma_multiply(double v)
  : m_mul(v)
  {
  }

  void value(double v)
  {
    m_mul = v;
  }
  double value() const
  {
    return m_mul;
  }

  double operator()(double x) const
  {
    double y = x * m_mul;
    if (y > 1.0)
      y = 1.0;
    return y;
  }

private:
  double m_mul;
};
} // namespace orion

#endif
