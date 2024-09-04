// ---------------------------------------------------- //
// spiRPI.h
// ---------------------------------------------------- //
// Data: 04/09/2024
// Author: Kiryl Alsheuski
// ---------------------------------------------------- //

#define m0  0
#define m1  1
#define p0  2
#define p1  3
#define p2  4
#define u0  5
#define u1  6
#define u2  7
#define A   8
#define W   9
#define n0  10
#define n1  11
#define n2  12
#define n3  13
#define T   14
#define R   15
#define b0  16
#define b1  17
#define b2  18
#define b3  19
#define b4  20
#define b5  21

// Docs: https://abyz.me.uk/rpi/pigpio/cif.html#spiOpen

// 21  20  19  18  17  16  15  14  13  12  11  10  9  8  7   6   5   4   3   2   1   0
// b5  b4  b3  b2  b1  b0  R   T   n3  n2  n1  n0  W  A  u2  u1  u0  p2  p1  p0  m1  m0

// mm defines the SPI mode.
// Warning: modes 1 and 3 do not appear to work on the auxiliary SPI.
// Mode POL PHA
//  0    0   0
//  1    0   1
//  2    1   0
//  3    1   1

// px is 0 if CEx is active low (default) and 1 for active high.

// ux is 0 if the CEx GPIO is reserved for SPI (default) and 1 otherwise.

// A is 0 for the main SPI, 1 for the auxiliary SPI.

// W is 0 if the device is not 3-wire, 1 if the device is 3-wire. Main SPI only.

// nnnn defines the number of bytes (0-15) to write before switching the MOSI line to MISO to read data. This field is ignored if W is not set. Main SPI only.

// T is 1 if the least significant bit is transmitted on MOSI first, the default (0) shifts the most significant bit out first. Auxiliary SPI only.

// R is 1 if the least significant bit is received on MISO first, the default (0) receives the most significant bit first. Auxiliary SPI only.

// bbbbbb defines the word size in bits (0-32). The default (0) sets 8 bits per word. Auxiliary SPI only.