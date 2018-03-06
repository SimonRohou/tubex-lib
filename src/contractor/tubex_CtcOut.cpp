/* ============================================================================
 *  tubex-lib - CtcOut class
 * ============================================================================
 *  Copyright : Copyright 2017 Simon Rohou
 *  License   : This program is distributed under the terms of
 *              the GNU Lesser General Public License (LGPL).
 *
 *  Author(s) : Simon Rohou
 *  Bug fixes : -
 *  Created   : 2015
 * ---------------------------------------------------------------------------- */

#include "tubex_CtcOut.h"

using namespace std;
using namespace ibex;

namespace tubex
{
  CtcOut::CtcOut(const ibex::Interval *t, const ibex::Interval *y) : m_t(t), m_y(y)
  {

  }

  bool CtcOut::contract()
  {
    /* TO APPEAR SOON */

    return false;
  }
}