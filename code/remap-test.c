#include <FastLED.h>
#define DIM             15u
// NP for No Pixel
#define NP              UINT_FAST8_MAX

#define NUM_LEDS        177u
#define LED_PIN         8u
#define MAX_BRIGHTNESS

CRGB leds[NUM_LEDS];

// TODO: Add to Setup
FastLED.addLeds<WS2812B, LED_PIN, RGB>(leds, NUM_LEDS);
FastLED.setBrightness(MAX_BRIGHTNESS);

// Takes Y and X (from Screen Top Left) and the corresponding value is the pixel address, UINT_FAST8_MAX
uint_fast8_t pixelLut[DIM][DIM] = {
    {  NP,  NP,  NP,  NP,  NP,   4,   3,   2,   1,   0,  NP,  NP,  NP,  NP,  NP},
    {  NP,  NP,  NP,   5,   6,   7,   8,   9,  10,  11,  12,  13,  NP,  NP,  NP},
    {  NP,  NP,  24,  23,  22,  21,  20,  19,  18,  17,  16,  15,  14,  NP,  NP},
    {  NP,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  NP},
    {  NP,  50,  49,  48,  47,  46,  45,  44,  43,  42,  41,  40,  39,  38,  NP},
    {  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65},
    {  80,  79,  78,  77,  76,  75,  74,  73,  72,  71,  70,  69,  68,  67,  66},
    {  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95},
    { 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100,  99,  98,  97,  96},
    { 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125},
    {  NP, 138, 137, 136, 135, 134, 133, 132, 131, 130, 129, 128, 127, 126,  NP},
    {  NP, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151,  NP},
    {  NP,  NP, 162, 161, 160, 159, 158, 157, 156, 155, 154, 153, 152,  NP,  NP},
    {  NP,  NP,  NP, 163, 164, 165, 166, 167, 168, 169, 170, 171,  NP,  NP,  NP},
    {  NP,  NP,  NP,  NP,  NP, 176, 175, 174, 173, 172,  NP,  NP,  NP,  NP,  NP}
}

bool isPixel(uint_fast8_t x, uint_fast8_t y) {
    return pixelLut[y][x] < NUM_LEDS;
}

// Updates the LEDs by passing in a 2D Array of Pixel Values (a frame) (sorted y[x], shorted as CRGB) and maps them to the display
void updateLEDs(CRGB** frame) {
    // Loop Over Pixels and update
    for (uint_fast8_t y = 0; y < DIM; y++) {
        for (uint_fast8_t y = 0; y < DIM; y++) {
            uint_fast8_t addr = pixelLut[y][x];
            if (addr < NUM_LEDS) {
                leds[addr] = frame[y][x];
            }
        }
    }
    
    FastLED.show();
}