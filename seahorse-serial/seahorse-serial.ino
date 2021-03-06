// Christmas Tree serial connected seahorse lights

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

static struct led_info leds [] =
  { { 13, X, LOW,  HIGH },
    { 12, G, HIGH, LOW  },
    { 10, R, LOW , HIGH },
    {  9, G, HIGH, LOW  },
    { 11, R, LOW , HIGH },
    {  7, G, HIGH, LOW  },
    {  8, R, LOW , HIGH },
    {  6, G, HIGH, LOW  },
    {  5, R, LOW , HIGH },
    {  3, R, LOW , HIGH },
    { 16, G, HIGH, LOW  },
    { 18, R, LOW , HIGH },
    { 17, G, HIGH, LOW  } };

// Vector of pins to hold HIGH

static int high_leds [] = {};

// Vector of pins to hold LOW

static int low_leds [] = {};

#include "../common/cuttletree.ino"
