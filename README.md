# The Cuttletree

This is Embecosm's entry in the 2017 Lymington Christmas Tree festival.

## Overall design

In 2016, our Christmas tree was decorated with a collection of cuttlefishes
and seahorses running a pre-programmed sequence of LED patterns. See
https://github.com/embecosm/ding-dong for the source code.

For 2017 those boards are now controlled centrally from a Raspberry Pi 3 via a
multiplexed serial connection. The Pi in turn listens to twitter and changes
patterns according.

## Arduino software design

The main loop frequently tests the serial Rx port (digital pin 0). If it is
low, then a serial input is coming, and the Arduino reads a single character
to determine what to do. Any 7-bit printable character can be used (ASCII 0x20
thru 0x7e).

Directory `common` has code common to both cuttlefish and seahorse
implementations, directories `cuttlefish-serial` and `seahorse-serial` have
the specific code, which is little more than a specification of the LED pin
sequence and which pins need driving to fixed value.
