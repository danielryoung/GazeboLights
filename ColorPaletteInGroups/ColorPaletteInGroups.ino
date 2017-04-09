#include <FastLED.h>

#define LED_PIN     22
#define NUM_LEDS    450
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
// Grouping
#define NUM_GROUPS 4

CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 1




// This example shows several ways to set up and use 'palettes' of colors
// with FastLED.
//
// These compact palettes provide an easy way to re-colorize your
// animation on the fly, quickly, easily, and with low overhead.
//
// USING palettes is MUCH simpler in practice than in theory, so first just
// run this sketch, and watch the pretty lights as you then read through
// the code.  Although this sketch has eight (or more) different color schemes,
// the entire sketch compiles down to about 6.5K on AVR.
//
// FastLED provides a few pre-configured color palettes, and makes it
// extremely easy to make up your own color schemes with palettes.
//
// Some notes on the more abstract 'theory and practice' of
// FastLED compact palettes are at the bottom of this file.

struct pixel
   //place in array is according to strip sequence
   {
      uint16_t index;
      
      uint8_t groupNum;
      // this is a group it belongs to
      unsigned long radialPosition;
      // this is an int indicating close to center. 0 is center 8 is outside
      uint8_t cluster;
   };

pixel pixels[NUM_LEDS] = {
//  {0,0,3,0}
//  ,{1,0,3,0}
//  ,{2,0,3,0}
//  ,{3,0,2,0}
//  ,{4,0,2,0}
//  ,{5,1,1,0}
//  ,{6,2,0,0}
//  ,{7,1,1,0}
//  ,{8,1,1,0}
//  ,{9,1,1,0}
//  ,{10,2,0,0}
//  ,{11,1,1,0}
//  ,{12,2,0,0}
//  ,{13,2,0,0}
//  ,{14,2,0,0}
//  ,{15,3,1,0}
//  ,{16,3,1,0}
//  ,{17,3,0,0}
//  ,{18,3,0,0}
//  ,{19,3,1,0}
    {0,1,1,1}
,{1,1,1,1}
,{2,1,1,1}
,{3,1,1,1}
,{4,1,1,1}
,{5,1,1,1}
,{6,1,1,1}
,{7,1,1,1}
,{8,1,1,1}
,{9,1,1,1}
,{10,1,1,1}
,{11,1,1,1}
,{12,1,1,1}
,{13,1,1,1}
,{14,1,1,1}
,{15,1,1,1}
,{16,1,1,1}
,{17,1,1,1}
,{18,1,1,1}
,{19,1,1,1}
,{20,1,1,1}
,{21,1,1,1}
,{22,1,1,1}
,{23,1,1,1}
,{24,1,1,1}
,{25,1,1,1}
,{26,1,1,1}
,{27,1,1,1}
,{28,1,1,1}
,{29,1,1,1}
,{30,1,1,1}
,{31,1,1,1}
,{32,1,1,1}
,{33,1,1,1}
,{34,1,1,1}
,{35,1,1,1}
,{36,1,1,1}
,{37,1,1,1}
,{38,1,1,1}
,{39,1,1,1}
,{40,1,1,1}
,{41,1,1,1}
,{42,1,1,1}
,{43,1,1,1}
,{44,1,1,1}
,{45,1,1,1}
,{46,1,1,1}
,{47,1,1,1}
,{48,1,1,1}
,{49,1,1,1}
,{50,1,1,1}
,{51,1,1,1}
,{52,1,1,1}
,{53,1,1,1}
,{54,1,1,1}
,{55,1,1,1}
,{56,1,1,1}
,{57,1,1,1}
,{58,1,1,1}
,{59,1,1,1}
,{60,1,1,1}
,{61,1,1,1}
,{62,1,1,1}
,{63,1,1,1}
,{64,1,1,1}
,{65,1,1,1}
,{66,1,1,1}
,{67,1,1,1}
,{68,1,1,1}
,{69,1,1,1}
,{70,1,1,1}
,{71,1,1,1}
,{72,1,1,1}
,{73,1,1,1}
,{74,1,1,1}
,{75,2,1,3}
,{76,2,1,3}
,{77,2,1,3}
,{78,2,1,3}
,{79,2,1,3}
,{80,2,1,3}
,{81,2,1,3}
,{82,2,1,3}
,{83,2,1,3}
,{84,2,1,3}
,{85,2,1,3}
,{86,2,1,3}
,{87,2,1,3}
,{88,2,1,3}
,{89,2,1,3}
,{90,2,1,3}
,{91,2,1,3}
,{92,2,1,3}
,{93,2,1,3}
,{94,2,1,3}
,{95,2,1,3}
,{96,2,1,3}
,{97,2,1,3}
,{98,2,1,3}
,{99,2,1,3}
,{100,2,1,3}
,{101,2,1,3}
,{102,2,1,3}
,{103,2,1,3}
,{104,2,1,3}
,{105,2,1,3}
,{106,2,1,3}
,{107,2,1,3}
,{108,2,1,3}
,{109,2,1,3}
,{110,2,1,3}
,{111,2,1,3}
,{112,2,1,3}
,{113,2,1,3}
,{114,2,1,3}
,{115,2,1,3}
,{116,2,1,3}
,{117,2,1,3}
,{118,2,1,3}
,{119,2,1,3}
,{120,2,1,3}
,{121,2,1,3}
,{122,2,1,3}
,{123,2,1,3}
,{124,2,1,3}
,{125,2,1,3}
,{126,2,1,3}
,{127,2,1,3}
,{128,2,1,3}
,{129,2,1,3}
,{130,2,1,3}
,{131,2,1,3}
,{132,2,1,3}
,{133,2,1,3}
,{134,2,1,3}
,{135,2,1,3}
,{136,2,1,3}
,{137,2,1,3}
,{138,2,1,3}
,{139,2,1,3}
,{140,2,1,3}
,{141,2,1,3}
,{142,2,1,3}
,{143,2,1,3}
,{144,2,1,3}
,{145,2,1,3}
,{146,2,1,3}
,{147,2,1,3}
,{148,2,1,3}
,{149,2,1,3}
,{150,2,1,3}
,{151,2,1,3}
,{152,2,1,3}
,{153,2,1,3}
,{154,2,1,3}
,{155,2,1,3}
,{156,2,1,3}
,{157,2,1,3}
,{158,2,1,3}
,{159,2,1,3}
,{160,2,1,3}
,{161,2,1,3}
,{162,2,1,3}
,{163,2,1,3}
,{164,3,1,5}
,{165,3,1,5}
,{166,3,1,5}
,{167,3,1,5}
,{168,3,1,5}
,{169,3,1,5}
,{170,3,1,5}
,{171,3,1,5}
,{172,3,1,5}
,{173,3,1,5}
,{174,3,1,5}
,{175,3,1,5}
,{176,3,1,5}
,{177,3,1,5}
,{178,3,1,5}
,{179,3,1,5}
,{180,3,1,5}
,{181,3,1,5}
,{182,3,1,5}
,{183,3,1,5}
,{184,3,1,5}
,{185,3,1,5}
,{186,3,1,5}
,{187,3,1,5}
,{188,3,1,5}
,{189,3,1,5}
,{190,3,1,5}
,{191,3,1,5}
,{192,3,1,5}
,{193,3,1,5}
,{194,3,1,5}
,{195,3,1,5}
,{196,3,1,5}
,{197,3,1,5}
,{198,3,1,5}
,{199,3,1,5}
,{200,3,1,5}
,{201,3,1,5}
,{202,3,1,5}
,{203,3,1,5}
,{204,3,1,5}
,{205,3,1,5}
,{206,3,1,5}
,{207,3,1,5}
,{208,3,1,5}
,{209,3,1,5}
,{210,3,1,6}
,{211,3,1,6}
,{212,3,1,6}
,{213,3,1,6}
,{214,3,1,6}
,{215,3,1,6}
,{216,3,1,6}
,{217,3,1,6}
,{218,3,1,6}
,{219,3,1,6}
,{220,3,1,6}
,{221,3,1,6}
,{222,3,1,6}
,{223,3,1,6}
,{224,3,1,6}
,{225,3,1,6}
,{226,3,1,6}
,{227,3,1,6}
,{228,3,1,6}
,{229,3,1,6}
,{230,3,1,6}
,{231,3,1,6}
,{232,3,1,6}
,{233,3,1,6}
,{234,3,1,6}
,{235,3,1,6}
,{236,3,1,6}
,{237,3,1,6}
,{238,3,1,6}
,{239,3,1,6}
,{240,3,1,6}
,{241,3,1,6}
,{242,3,1,6}
,{243,3,1,6}
,{244,3,1,6}
,{245,3,1,6}
,{246,3,1,6}
,{247,3,1,6}
,{248,3,1,6}
,{249,3,1,6}
,{250,3,1,6}
,{251,3,1,6}
,{252,3,1,6}
,{253,3,1,6}
,{254,3,1,6}
,{255,3,1,6}
,{256,3,1,6}
,{257,3,1,6}
,{258,2,1,4}
,{259,2,1,4}
,{260,2,1,4}
,{261,2,1,4}
,{262,2,1,4}
,{263,2,1,4}
,{264,2,1,4}
,{265,2,1,4}
,{266,2,1,4}
,{267,2,1,4}
,{268,2,1,4}
,{269,2,1,4}
,{270,2,1,4}
,{271,2,1,4}
,{272,2,1,4}
,{273,2,1,4}
,{274,2,1,4}
,{275,2,1,4}
,{276,2,1,4}
,{277,2,1,4}
,{278,2,1,4}
,{279,2,1,4}
,{280,2,1,4}
,{281,2,1,4}
,{282,2,1,4}
,{283,2,1,4}
,{284,2,1,4}
,{285,2,1,4}
,{286,2,1,4}
,{287,2,1,4}
,{288,2,1,4}
,{289,2,1,4}
,{290,2,1,4}
,{291,2,1,4}
,{292,2,1,4}
,{293,2,1,4}
,{294,2,1,4}
,{295,2,1,4}
,{296,2,1,4}
,{297,2,1,4}
,{298,2,1,4}
,{299,2,1,4}
,{300,2,1,4}
,{301,2,1,4}
,{302,2,1,4}
,{303,2,1,4}
,{304,2,1,4}
,{305,2,1,4}
,{306,2,1,4}
,{307,2,1,4}
,{308,2,1,4}
,{309,2,1,4}
,{310,2,1,4}
,{311,2,1,4}
,{312,2,1,4}
,{313,2,1,4}
,{314,2,1,4}
,{315,2,1,4}
,{316,2,1,4}
,{317,2,1,4}
,{318,2,1,4}
,{319,2,1,4}
,{320,2,1,4}
,{321,2,1,4}
,{322,2,1,4}
,{323,2,1,4}
,{324,2,1,4}
,{325,2,1,4}
,{326,2,1,4}
,{327,2,1,4}
,{328,2,1,4}
,{329,2,1,4}
,{330,2,1,4}
,{331,2,1,4}
,{332,2,1,4}
,{333,2,1,4}
,{334,2,1,4}
,{335,2,1,4}
,{336,2,1,4}
,{337,2,1,4}
,{338,2,1,4}
,{339,2,1,4}
,{340,2,1,4}
,{341,2,1,4}
,{342,2,1,4}
,{343,2,1,4}
,{344,2,1,4}
,{345,1,1,2}
,{346,1,1,2}
,{347,1,1,2}
,{348,1,1,2}
,{349,1,1,2}
,{350,1,1,2}
,{351,1,1,2}
,{352,1,1,2}
,{353,1,1,2}
,{354,1,1,2}
,{355,1,1,2}
,{356,1,1,2}
,{357,1,1,2}
,{358,1,1,2}
,{359,1,1,2}
,{360,1,1,2}
,{361,1,1,2}
,{362,1,1,2}
,{363,1,1,2}
,{364,1,1,2}
,{365,1,1,2}
,{366,1,1,2}
,{367,1,1,2}
,{368,1,1,2}
,{369,1,1,2}
,{370,1,1,2}
,{371,1,1,2}
,{372,1,1,2}
,{373,1,1,2}
,{374,1,1,2}
,{375,1,1,2}
,{376,1,1,2}
,{377,1,1,2}
,{378,1,1,2}
,{379,1,1,2}
,{380,1,1,2}
,{381,1,1,2}
,{382,1,1,2}
,{383,1,1,2}
,{384,1,1,2}
,{385,1,1,2}
,{386,1,1,2}
,{387,1,1,2}
,{388,1,1,2}
,{389,1,1,2}
,{390,1,1,2}
,{391,1,1,2}
,{392,1,1,2}
,{393,1,1,2}
,{394,1,1,2}
,{395,1,1,2}
,{396,1,1,2}
,{397,1,1,2}
,{398,1,1,2}
,{399,1,1,2}
,{400,1,1,2}
,{401,1,1,2}
,{402,1,1,2}
,{403,1,1,2}
,{404,1,1,2}
,{405,1,1,2}
,{406,1,1,2}
,{407,1,1,2}
,{408,1,1,2}
,{409,1,1,2}
,{410,1,1,2}
,{411,1,1,2}
,{412,1,1,2}
,{413,1,1,2}
,{414,1,1,2}
,{415,1,1,2}
,{416,1,1,2}
,{417,1,1,2}
,{418,1,1,2}
,{419,1,1,2}
,{420,1,1,2}
,{421,1,1,2}
,{422,1,1,2}
,{423,1,1,2}
,{424,1,1,2}
,{425,1,1,2}
,{426,1,1,2}
,{427,2,1,4}
,{428,2,1,4}
,{429,2,1,4}
,{430,2,1,4}
,{431,2,1,4}
,{432,2,1,4}
,{433,2,1,4}
,{434,2,1,4}
,{435,2,1,4}
,{436,2,1,4}
,{437,2,1,4}
,{438,2,1,4}
,{439,2,1,4}
,{440,2,1,4}
,{441,2,1,4}
,{442,2,1,4}
,{443,2,1,4}
,{444,3,1,6}
,{445,3,1,6}
,{446,3,1,6}
,{447,3,1,6}
,{448,3,1,6}
,{449,3,1,6}
 
   };

int group[NUM_GROUPS];


CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;


void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
    randomSeed(analogRead(0));
}


//void loop()
//{
//    ChangePalettePeriodically();
//    
//    static uint8_t startIndex = 0;
//    startIndex = startIndex + 1; /* motion speed */
//    
//    FillLEDsFromPaletteColors( startIndex);
//    
//    FastLED.show();
//    FastLED.delay(1000 / UPDATES_PER_SECOND);
//}

void loop()
{

  ChangePalettePeriodically();
   
   // do this every two minutes
  FillGroupsFromPaletteColors();

  //hue = map8( sin8( myValue), HUE_BLUE, HUE_RED);
  
//  for( int g = 0; g < NUM_GROUPS; g++) {
//
//    //get a random color from pallette for each group
//    int randomColorIndex = random(255);
//
//    //assign the random color to each led l in the group g
//    for( int l = 0; l < NUM_LEDS; l++){
//       if(pixels[l].groupNum == g) {leds[l] = ColorFromPalette( currentPalette, randomColorIndex, brightness, currentBlending);  } 
//    }
//
//    
//    //FillGroupFromPalletteColors(i,);
//  }
  addGlitter(80);
  
  FastLED.show();
  //FastLED.delay(1000 / UPDATES_PER_SECOND);
  FastLED.delay(10000);
}

void FillGroupsFromPaletteColors(){

    uint8_t brightness = 255;
    
    for( int g = 0; g < NUM_GROUPS; g++) {

    //get a random color from pallette for each group
    int randomColorIndex = random(255);

    //assign the random color to each led l in the group g
    for( int l = 0; l < NUM_LEDS; l++){
       if(pixels[l].groupNum == g) {leds[l] = ColorFromPalette( currentPalette, randomColorIndex, brightness, currentBlending);  } 
    }    
    //FillGroupFromPalletteColors(i,);
  }
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}


// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.

void ChangePalettePeriodically()
{
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;
    
    if( lastSecond != secondHand) {
        lastSecond = secondHand;
        if( secondHand ==  0)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
        if( secondHand == 10)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
        if( secondHand == 15)  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
        if( secondHand == 20)  { SetupPurpleAndGreenPalette();             currentBlending = LINEARBLEND; }
        if( secondHand == 25)  { SetupTotallyRandomPalette();              currentBlending = LINEARBLEND; }
        if( secondHand == 30)  { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; }
        if( secondHand == 35)  { SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND; }
        if( secondHand == 40)  { currentPalette = CloudColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 45)  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 50)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;  }
        if( secondHand == 55)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND; }
    }
}

// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;
    
}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};



// Additionl notes on FastLED compact palettes:
//
// Normally, in computer graphics, the palette (or "color lookup table")
// has 256 entries, each containing a specific 24-bit RGB color.  You can then
// index into the color palette using a simple 8-bit (one byte) value.
// A 256-entry color palette takes up 768 bytes of RAM, which on Arduino
// is quite possibly "too many" bytes.
//
// FastLED does offer traditional 256-element palettes, for setups that
// can afford the 768-byte cost in RAM.
//
// However, FastLED also offers a compact alternative.  FastLED offers
// palettes that store 16 distinct entries, but can be accessed AS IF
// they actually have 256 entries; this is accomplished by interpolating
// between the 16 explicit entries to create fifteen intermediate palette
// entries between each pair.
//
// So for example, if you set the first two explicit entries of a compact 
// palette to Green (0,255,0) and Blue (0,0,255), and then retrieved 
// the first sixteen entries from the virtual palette (of 256), you'd get
// Green, followed by a smooth gradient from green-to-blue, and then Blue.
