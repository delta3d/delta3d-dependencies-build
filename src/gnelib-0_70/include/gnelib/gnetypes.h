#ifndef _GNETYPES_H_
#define _GNETYPES_H_

/* GNE - Game Networking Engine, a portable multithreaded networking library.
 * Copyright (C) 2001-2006 Jason Winnebeck 
 * Project website: http://www.gillius.org/gne/
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

//Header file containing GNE-wide typedefs.
#include <boost/cstdint.hpp>

namespace GNE {
  /**
   * Typedefs for the variable types that are common to all GNE
   * implementations (as defined in the GNE protocol document).
   * "u" type variables denote unsigned versions.
   */
  typedef boost::int8_t  gint8;
  typedef boost::uint8_t guint8;
  typedef guint8         gbyte;

  /**
   * A gbool is 'false' only when its value is 0, else it is 'true'.
   */
  typedef guint8         gbool;

  /**
   * One possible true value for a gbool.
   */
  const gbool gTrue = 1;
  /**
   * The only false value for a gbool.
   */
  const gbool gFalse = 0;
  
  typedef boost::int16_t  gint16;
  typedef boost::uint16_t guint16;
  
  typedef boost::int32_t  gint32;
  typedef boost::uint32_t  guint32;
  
  /**
   * A single precision 32-bit IEEE 754 floating point variable.
   */
  typedef float          gsingle;
  /**
   * A double precision 64-bit IEEE 754 floating point variable.
   */
  typedef double         gdouble;
};

#endif
