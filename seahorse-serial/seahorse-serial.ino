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

static int num_leds;

// How many patterns and which one are we using.

static int num_pats;
static unsigned int curr_pat = 0;


// Flash the lights, allowing the specified millisecs between each.

static void
flashy (int ms)
{
  int j;

  // Alternate having the green and red LEDs on.

  for (j = 0; j < ms; j++)
    {
      int  i;

      for (i = 0; i < num_leds; i++)
	if (leds[i].color == G)
	  {
	    int dir = (((j % 4) == 0) || (leds[i].color == X))
	      ? leds[i].on : leds[i].off;

	    digitalWrite (leds[i].pin, dir);
	  }
	else
	  {
	    digitalWrite (leds[i].pin, leds[i].off);
	  }

      delay(1);               // wait for a millisecond
    }

  for (j = 0; j < ms; j++)
    {
      int  i;

      for (i = 0; i < num_leds; i++)
	if (leds[i].color != G)
	  {
	    int dir = (((j % 4) == 0) || (leds[i].color == X))
	      ? leds[i].on : leds[i].off;

	    digitalWrite (leds[i].pin, dir);
	  }
	else
	  {
	    digitalWrite (leds[i].pin, leds[i].off);
	  }

      delay(1);               // wait for a millisecond
    }
}	// flashy


// Sinusoidal fading. Arg specifies number of slices (more = slower)

static void
blender (int slices)
{
  float j;

  for (j = 0.0; j < (2.0 * PI); j += PI / static_cast<float> (slices))
  {
    int i;
    int red   = max ((int) (8.0 * sinf (j)) + 6, 0);
    int green = max (6 - (int) (8.0 * sinf (j)), 0);

    for (i = 0; i < num_leds; i++)
      if (leds[i].color == G)
        digitalWrite (leds[i].pin, leds[i].on);		// GREEN On
      else
        digitalWrite (leds[i].pin, leds[i].off);	// RED/Unknown Off

    delay (green);

    for (i = 0; i < num_leds; i++)
      if (leds[i].color != G)
        digitalWrite (leds[i].pin, leds[i].on)	;	// RED/Unknown On
      else
        digitalWrite (leds[i].pin, leds[i].off);	// GREEN Off

    delay(red);

    for (i = 0; i < num_leds; i++)
      digitalWrite (leds[i].pin, leds[i].off);		// All Off
  }
}	// blender ()


// Loop clockwise, with specified millisec delay between each step

static void
clock_loop (int ms)
{
  int i;

  for (i = 0; i < num_leds; i++)
    digitalWrite (leds[i].pin, leds[i].off);	// All Off

  // Turn the current and prev pin on and the one two before off

  for (i = 0; i < num_leds + 1; i++)
    {
      int j;
      int p1 = i - 1;
      int p2 = i - 2;

      for (j = 0; j < ms; j++)
	{
	  // Current LED

	  if (i < num_leds)
	    {
	      int dir = (((j % 4) == 0) || (leds[i].color == X))
		? leds[i].on : leds[i].off;

	      digitalWrite (leds[i].pin, dir);		// Current pin on?
	    }

	  // Prev LED

	  if ((0 <= p1) && (p1 < num_leds))
	    {
	      int dir = (((j % 4) == 0) || (leds[p1].color == X))
		? leds[p1].on : leds[p1].off;
		digitalWrite (leds[p1].pin, dir);	// Prev pin on?
	    }

	  // Prev but 2 LED

	  if ((0 <= p2) && (p2 < num_leds))
	    digitalWrite (leds[p2].pin, leds[p2].off);	// Prev pin but 2 off

	  delay (1);
	}
    }

  for (i = 0; i < num_leds; i++)
    digitalWrite (leds[i].pin, leds[i].off);	// All Off

}	// clock_loop ()


// Loop anti-clockwise, with specified millisec delay between each step

static void
anticlock_loop (int ms)
{
  int i;

  for (i = 0; i < num_leds; i++)
    digitalWrite (leds[i].pin, leds[i].off);	// All Off

  // Turn the current and next pin on and the one two after off

  for (i = num_leds - 1; i >= -1; i--)
    {
      int j;
      int n1 = i + 1;
      int n2 = i + 2;

      for (j = 0; j < ms; j++)
	{
	  // Current LED

	  if (i >= 0)
	    {
	      int dir = (((j % 4) == 0) || (leds[i].color == X))
		? leds[i].on : leds[i].off;

	      digitalWrite (leds[i].pin, dir);	// Current pin on
	    }

	  // Next LED

	  if ((0 <= n1) && (n1 < num_leds))
	    {
	      int dir = (((j % 4) == 0) || (leds[n1].color == X))
		? leds[n1].on : leds[n1].off;
		digitalWrite (leds[n1].pin, dir);	// Prev pin on?
	    }

	  // Prev but 2 LED

	  if ((0 <= n2) && (n2 < num_leds))
	    digitalWrite (leds[n2].pin, leds[n2].off);	// Prev pin but 2 off

	  delay (1);
	}
    }
}	// anticlock_loop ()


// Structure describing pattern functions

struct pat_info {
  void (*func) (int);
  int  arg;
};

// Vector of functions

static struct pat_info pats [] =
  { {&blender,         30},
    {&clock_loop,     100},
    {&flashy,         380},
    {&anticlock_loop, 100},
    {&blender,        100},
    {&clock_loop,      30},
    {&flashy,         125},
    {&anticlock_loop,  30} };


// the setup routine runs once when you press reset:

void setup() {
  int  i;

  num_leds = sizeof (leds) / sizeof (led_info);
  num_pats = sizeof (pats) / sizeof (pat_info);

  // initialize the pins as output

  for (i = 0; i < num_leds; i++)
    pinMode(leds[i].pin, OUTPUT);

  // Open up serial input

  Serial.begin (9600);

}	// setup ()


// the loop routine runs over and over again forever:

void loop () {

  // Change function?

  if (Serial.available () > 0)
    curr_pat = Serial.read () % num_pats;

  // Apply the currently selected function

  pats[curr_pat].func (pats[curr_pat].arg);

}	// loop ()
