// Christmas Tree serial connected cuttlefish lights

// Copyright (C) 2016, 2017 Embecosm Limited <www.embecosm.com>

// Contributor Peter Bennett <thelargeostrich@gmail.com>
// Contributor Jeremy Bennett <jeremy.bennett@embecosm.com>

// This file is part of the Embecosm Christmas Tree decoration project 2016.

// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.

// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.

// You should have received a copy of the GNU General Public License along
// with this program.  If not, see <http://www.gnu.org/licenses/>. */


// Flash a seahorse in a pattern according to anything received on the serial
// port.

#include "../common/cuttletree.h"

// Vector describing all lights clockwise from the belly

// Vector describing all lights clockwise from the highest numbered pin

static struct led_info leds [] =
  { { 18, G, HIGH, LOW  },
    { 16, R, HIGH, LOW  },
    { 14, G, HIGH, LOW  },
    { 13, R, LOW , HIGH },
    { 11, G, LOW,  HIGH },
    {  9, R, LOW , HIGH },
    {  8, G, HIGH, LOW  },
    {  6, R, HIGH, LOW  },
    {  4, G, LOW,  HIGH },
    {  2, R, LOW , HIGH } };

// Vector of pins to hold HIGH

static int high_leds [] =
  {
    12, 10, 3
  };

// Vector of pins to hold LOW

static int low_leds [] =
  {
    17, 15, 7, 5
  };

#include "../common/cuttletree.ino"
