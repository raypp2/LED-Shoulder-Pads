// Helper functions for a two-dimensional XY matrix of pixels.
// Special credit to Mark Kriegsman
// https://macetech.github.io/FastLED-XY-Map-Generator/
//
//              This special 'XY' code simulates an 8x11 matrix (square)
//
//              Writing to and reading from the 'holes' in the layout is 
//              also allowed; holes retain their data, it's just not displayed.
//
//              You can also test to see if you're on or off the layout
//              like this
//                if( XY(x,y) > LAST_VISIBLE_LED ) { ...off the layout...}
//
//              X and Y bounds checking is also included, so it is safe
//              to just do this without checking x or y in your code:
//                leds[ XY(x,y) ] == CRGB::Red;
//              All out of bounds coordinates map to the first hidden pixel.
//
//     XY(x,y) takes x and y coordinates and returns an LED index number,
//             for use like this:  leds[ XY(x,y) ] == CRGB::Red;


// Params for width and height
const uint8_t kMatrixWidth = 9;
const uint8_t kMatrixHeight = 16;

#define NUM_LEDS (kMatrixWidth * kMatrixHeight)
CRGB leds[ NUM_LEDS ];


// This function will return the right 'led index number' for 
// a given set of X and Y coordinates 
// This code, plus the supporting 80-byte table is much smaller 
// and much faster than trying to calculate the pixel ID with code.

#define LAST_VISIBLE_LED 91
uint8_t XY( uint8_t x, uint8_t y)
{
  // any out of bounds address maps to the first hidden pixel
  if( (x >= kMatrixWidth) || (y >= kMatrixHeight) ) {
    return (LAST_VISIBLE_LED + 1);
  }

  const uint8_t XYTable[] = {
    92,  93,   0,   1,   2,   3,   4,  94,  95,
    98,  10,   9,   8,   7,   6,   5,  97,  96,
    99,  11,  12,  13,  14,  15,  16, 100, 101,
   103,  23,  22,  21,  20,  19,  18,  17, 102,
   104,  24,  25,  26,  27,  28,  29,  30, 105,
   106,  38,  37,  36,  35,  34,  33,  32,  31,
   107,  39,  40,  41,  42,  43,  44,  45,  46,
    55,  54,  53,  52,  51,  50,  49,  48,  47,
    56,  57,  58,  59, 108,  60,  61,  62,  63,
   111,  69,  68,  67, 110,  66,  65,  64, 109,
   112,  70,  71,  72, 113,  73,  74,  75, 114,
   119, 118,  79,  78, 117,  77,  76, 116, 115,
   120,  80,  81, 121, 122, 123,  82,  83, 124,
   129, 128,  87,  86, 127,  85,  84, 126, 125,
   130, 131,  88, 132, 133, 134,  89, 135, 136,
   143, 142, 141,  91, 140,  90, 139, 138, 137
  };

  uint8_t i = (y * kMatrixWidth) + x;
  uint8_t j = XYTable[i];
  return j;
}
