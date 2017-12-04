// Common header for christmas Tree serial connected seahorse lights

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


// Header common to Cuttletree applications

#ifndef CUTTLETREE_H
#define CUTTLETREE_H

// Enum for colors

enum led_color {
  R,
  G,
  X
};

// Structure for describing LEDs.

struct led_info
{
  int             pin;
  enum led_color  color;
  int             on;		// HIGH or LOW
  int             off;		// HIGH or LOW
};

// Structure describing pattern functions

struct pat_info {
  void (*func) (int);
  int  arg;
};

#endif	// CUTTLETREE_H
