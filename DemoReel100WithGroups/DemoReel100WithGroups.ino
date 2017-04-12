#include "FastLED.h"

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    22
//#define CLK_PIN   4
#define LED_TYPE    WS2811
//#define COLOR_ORDER GRB
#define COLOR_ORDER RGB
#define NUM_LEDS    20
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

#define NUM_GROUPS 4
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

// change to NUM PIXELS

pixel pixels[NUM_LEDS] = {
  {0,0,3,0}
  ,{1,0,3,0}
  ,{2,0,3,0}
  ,{3,0,2,0}
  ,{4,0,2,0}
  ,{5,1,1,0}
  ,{6,1,0,0}
  ,{7,1,1,0}
  ,{8,1,1,0}
  ,{9,1,1,0}
  ,{10,1,0,0}
  ,{11,1,1,0}
  ,{12,1,0,0}
  ,{13,1,0,0}
  ,{14,1,0,0}
  ,{15,1,1,0}
  ,{16,1,1,0}
  ,{17,1,0,0}
  ,{18,1,0,0}
  ,{19,3,1,0}
//pixel pixels[600] = {
//{0,0,0,0}
//,{1,0,1,0}
//,{2,0,2,0}
//,{3,0,3,0}
//,{4,0,4,0}
//,{5,0,5,0}
//,{6,0,6,0}
//,{7,0,7,0}
//,{8,0,8,0}
//,{9,0,9,0}
//,{10,0,10,0}
//,{11,0,11,0}
//,{12,0,12,0}
//,{13,0,13,0}
//,{14,0,14,0}
//,{15,0,15,0}
//,{16,0,16,0}
//,{17,0,17,0}
//,{18,0,18,0}
//,{19,0,19,0}
//,{20,0,20,0}
//,{21,0,21,0}
//,{22,0,22,0}
//,{23,0,23,0}
//,{24,0,24,0}
//,{25,0,25,0}
//,{26,0,26,0}
//,{27,0,27,0}
//,{28,0,28,0}
//,{29,0,29,0}
//,{30,0,30,0}
//,{31,0,31,0}
//,{32,0,32,0}
//,{33,0,33,0}
//,{34,0,34,0}
//,{35,0,35,0}
//,{36,0,36,0}
//,{37,0,37,0}
//,{38,0,38,0}
//,{39,0,39,0}
//,{40,0,40,0}
//,{41,0,41,0}
//,{42,0,42,0}
//,{43,0,43,0}
//,{44,0,44,0}
//,{45,0,45,0}
//,{46,0,46,0}
//,{47,0,47,0}
//,{48,0,48,0}
//,{49,0,49,0}
//,{50,0,50,0}
//,{51,0,51,0}
//,{52,0,52,0}
//,{53,0,53,0}
//,{54,0,54,0}
//,{55,0,55,0}
//,{56,0,56,0}
//,{57,0,57,0}
//,{58,0,58,0}
//,{59,0,59,0}
//,{60,0,60,0}
//,{61,0,61,0}
//,{62,0,62,0}
//,{63,0,63,0}
//,{64,0,64,0}
//,{65,0,65,0}
//,{66,0,66,0}
//,{67,0,67,0}
//,{68,0,68,0}
//,{69,0,69,0}
//,{70,0,70,0}
//,{71,0,71,0}
//,{72,0,72,0}
//,{73,0,73,0}
//,{74,0,74,0}
//,{75,1,0,2}
//,{76,1,1,2}
//,{77,1,2,2}
//,{78,1,3,2}
//,{79,1,4,2}
//,{80,1,5,2}
//,{81,1,6,2}
//,{82,1,7,2}
//,{83,1,8,2}
//,{84,1,9,2}
//,{85,1,10,2}
//,{86,1,11,2}
//,{87,1,12,2}
//,{88,1,13,2}
//,{89,1,14,2}
//,{90,1,15,2}
//,{91,1,16,2}
//,{92,1,17,2}
//,{93,1,18,2}
//,{94,1,19,2}
//,{95,1,20,2}
//,{96,1,21,2}
//,{97,1,22,2}
//,{98,1,23,2}
//,{99,1,24,2}
//,{100,1,25,2}
//,{101,1,26,2}
//,{102,1,27,2}
//,{103,1,28,2}
//,{104,1,29,2}
//,{105,1,30,2}
//,{106,1,31,2}
//,{107,1,32,2}
//,{108,1,33,2}
//,{109,1,34,2}
//,{110,1,35,2}
//,{111,1,36,2}
//,{112,1,37,2}
//,{113,1,38,2}
//,{114,1,39,2}
//,{115,1,40,2}
//,{116,1,41,2}
//,{117,1,42,2}
//,{118,1,43,2}
//,{119,1,44,2}
//,{120,1,45,2}
//,{121,1,46,2}
//,{122,1,47,2}
//,{123,1,48,2}
//,{124,1,49,2}
//,{125,1,50,2}
//,{126,1,51,2}
//,{127,1,52,2}
//,{128,1,53,2}
//,{129,1,54,2}
//,{130,1,55,2}
//,{131,1,56,2}
//,{132,1,57,2}
//,{133,1,58,2}
//,{134,1,59,2}
//,{135,1,60,2}
//,{136,1,61,2}
//,{137,1,62,2}
//,{138,1,63,2}
//,{139,1,64,2}
//,{140,1,65,2}
//,{141,1,66,2}
//,{142,1,67,2}
//,{143,1,68,2}
//,{144,1,69,2}
//,{145,1,70,2}
//,{146,1,71,2}
//,{147,1,72,2}
//,{148,1,73,2}
//,{149,1,74,2}
//,{150,1,75,2}
//,{151,1,76,2}
//,{152,1,77,2}
//,{153,1,78,2}
//,{154,1,79,2}
//,{155,1,80,2}
//,{156,1,81,2}
//,{157,1,82,2}
//,{158,1,83,2}
//,{159,1,84,2}
//,{160,1,85,2}
//,{161,1,86,2}
//,{162,1,87,2}
//,{163,1,88,2}
//,{164,2,0,4}
//,{165,2,1,4}
//,{166,2,2,4}
//,{167,2,3,4}
//,{168,2,4,4}
//,{169,2,5,4}
//,{170,2,6,4}
//,{171,2,7,4}
//,{172,2,8,4}
//,{173,2,9,4}
//,{174,2,10,4}
//,{175,2,11,4}
//,{176,2,12,4}
//,{177,2,13,4}
//,{178,2,14,4}
//,{179,2,15,4}
//,{180,2,16,4}
//,{181,2,17,4}
//,{182,2,18,4}
//,{183,2,19,4}
//,{184,2,20,4}
//,{185,2,21,4}
//,{186,2,22,4}
//,{187,2,23,4}
//,{188,2,24,4}
//,{189,2,25,4}
//,{190,2,26,4}
//,{191,2,27,4}
//,{192,2,28,4}
//,{193,2,29,4}
//,{194,2,30,4}
//,{195,2,31,4}
//,{196,2,32,4}
//,{197,2,33,4}
//,{198,2,34,4}
//,{199,2,35,4}
//,{200,2,36,4}
//,{201,2,37,4}
//,{202,2,38,4}
//,{203,2,39,4}
//,{204,2,40,4}
//,{205,2,41,4}
//,{206,2,42,4}
//,{207,2,43,4}
//,{208,2,44,4}
//,{209,2,45,4}
//,{210,2,46,5}
//,{211,2,47,5}
//,{212,2,48,5}
//,{213,2,49,5}
//,{214,2,50,5}
//,{215,2,51,5}
//,{216,2,52,5}
//,{217,2,53,5}
//,{218,2,54,5}
//,{219,2,55,5}
//,{220,2,56,5}
//,{221,2,57,5}
//,{222,2,58,5}
//,{223,2,59,5}
//,{224,2,60,5}
//,{225,2,61,5}
//,{226,2,62,5}
//,{227,2,63,5}
//,{228,2,64,5}
//,{229,2,65,5}
//,{230,2,66,5}
//,{231,2,67,5}
//,{232,2,68,5}
//,{233,2,69,5}
//,{234,2,70,5}
//,{235,2,71,5}
//,{236,2,72,5}
//,{237,2,73,5}
//,{238,2,74,5}
//,{239,2,75,5}
//,{240,2,76,5}
//,{241,2,77,5}
//,{242,2,78,5}
//,{243,2,79,5}
//,{244,2,80,5}
//,{245,2,81,5}
//,{246,2,82,5}
//,{247,2,83,5}
//,{248,2,84,5}
//,{249,2,85,5}
//,{250,2,86,5}
//,{251,2,87,5}
//,{252,2,88,5}
//,{253,2,89,5}
//,{254,2,90,5}
//,{255,2,91,5}
//,{256,2,92,5}
//,{257,2,93,5}
//,{258,1,0,3}
//,{259,1,1,3}
//,{260,1,2,3}
//,{261,1,3,3}
//,{262,1,4,3}
//,{263,1,5,3}
//,{264,1,6,3}
//,{265,1,7,3}
//,{266,1,8,3}
//,{267,1,9,3}
//,{268,1,10,3}
//,{269,1,11,3}
//,{270,1,12,3}
//,{271,1,13,3}
//,{272,1,14,3}
//,{273,1,15,3}
//,{274,1,16,3}
//,{275,1,17,3}
//,{276,1,18,3}
//,{277,1,19,3}
//,{278,1,20,3}
//,{279,1,21,3}
//,{280,1,22,3}
//,{281,1,23,3}
//,{282,1,24,3}
//,{283,1,25,3}
//,{284,1,26,3}
//,{285,1,27,3}
//,{286,1,28,3}
//,{287,1,29,3}
//,{288,1,30,3}
//,{289,1,31,3}
//,{290,1,32,3}
//,{291,1,33,3}
//,{292,1,34,3}
//,{293,1,35,3}
//,{294,1,36,3}
//,{295,1,37,3}
//,{296,1,38,3}
//,{297,1,39,3}
//,{298,1,40,3}
//,{299,1,41,3}
//,{300,1,42,3}
//,{301,1,43,3}
//,{302,1,44,3}
//,{303,1,45,3}
//,{304,1,46,3}
//,{305,1,47,3}
//,{306,1,48,3}
//,{307,1,49,3}
//,{308,1,50,3}
//,{309,1,51,3}
//,{310,1,52,3}
//,{311,1,53,3}
//,{312,1,54,3}
//,{313,1,55,3}
//,{314,1,56,3}
//,{315,1,57,3}
//,{316,1,58,3}
//,{317,1,59,3}
//,{318,1,60,3}
//,{319,1,61,3}
//,{320,1,62,3}
//,{321,1,63,3}
//,{322,1,64,3}
//,{323,1,65,3}
//,{324,1,66,3}
//,{325,1,67,3}
//,{326,1,68,3}
//,{327,1,69,3}
//,{328,1,70,3}
//,{329,1,71,3}
//,{330,1,72,3}
//,{331,1,73,3}
//,{332,1,74,3}
//,{333,1,75,3}
//,{334,1,76,3}
//,{335,1,77,3}
//,{336,1,78,3}
//,{337,1,79,3}
//,{338,1,80,3}
//,{339,1,81,3}
//,{340,1,82,3}
//,{341,1,83,3}
//,{342,1,84,3}
//,{343,1,85,3}
//,{344,1,86,3}
//,{345,0,0,1}
//,{346,0,1,1}
//,{347,0,2,1}
//,{348,0,3,1}
//,{349,0,4,1}
//,{350,0,5,1}
//,{351,0,6,1}
//,{352,0,7,1}
//,{353,0,8,1}
//,{354,0,9,1}
//,{355,0,10,1}
//,{356,0,11,1}
//,{357,0,12,1}
//,{358,0,13,1}
//,{359,0,14,1}
//,{360,0,15,1}
//,{361,0,16,1}
//,{362,0,17,1}
//,{363,0,18,1}
//,{364,0,19,1}
//,{365,0,20,1}
//,{366,0,21,1}
//,{367,0,22,1}
//,{368,0,23,1}
//,{369,0,24,1}
//,{370,0,25,1}
//,{371,0,26,1}
//,{372,0,27,1}
//,{373,0,28,1}
//,{374,0,29,1}
//,{375,0,30,1}
//,{376,0,31,1}
//,{377,0,32,1}
//,{378,0,33,1}
//,{379,0,34,1}
//,{380,0,35,1}
//,{381,0,36,1}
//,{382,0,37,1}
//,{383,0,38,1}
//,{384,0,39,1}
//,{385,0,40,1}
//,{386,0,41,1}
//,{387,0,42,1}
//,{388,0,43,1}
//,{389,0,44,1}
//,{390,0,45,1}
//,{391,0,46,1}
//,{392,0,47,1}
//,{393,0,48,1}
//,{394,0,49,1}
//,{395,0,50,1}
//,{396,0,51,1}
//,{397,0,52,1}
//,{398,0,53,1}
//,{399,0,54,1}
//,{400,0,55,1}
//,{401,0,56,1}
//,{402,0,57,1}
//,{403,0,58,1}
//,{404,0,59,1}
//,{405,0,60,1}
//,{406,0,61,1}
//,{407,0,62,1}
//,{408,0,63,1}
//,{409,0,64,1}
//,{410,0,65,1}
//,{411,0,66,1}
//,{412,0,67,1}
//,{413,0,68,1}
//,{414,0,69,1}
//,{415,0,70,1}
//,{416,0,71,1}
//,{417,0,72,1}
//,{418,0,73,1}
//,{419,0,74,1}
//,{420,0,75,1}
//,{421,0,76,1}
//,{422,0,77,1}
//,{423,0,78,1}
//,{424,0,79,1}
//,{425,0,80,1}
//,{426,0,81,1}
//,{427,1,87,3}
//,{428,1,88,3}
//,{429,1,89,3}
//,{430,1,90,3}
//,{431,1,91,3}
//,{432,1,92,3}
//,{433,1,93,3}
//,{434,1,94,3}
//,{435,1,95,3}
//,{436,1,96,3}
//,{437,1,97,3}
//,{438,1,98,3}
//,{439,1,99,3}
//,{440,1,100,3}
//,{441,1,101,3}
//,{442,1,102,3}
//,{443,1,103,3}
//,{444,2,0,5}
//,{445,2,1,5}
//,{446,2,2,5}
//,{447,2,3,5}
//,{448,2,4,5}
//,{449,2,5,5}
//,{450,2,6,5}
//,{451,2,7,5}
//,{452,2,8,5}
//,{453,2,9,5}
//,{454,2,10,5}
//,{455,2,11,5}
//,{456,2,12,5}
//,{457,2,13,5}
//,{458,2,14,5}
//,{459,2,15,5}
//,{460,2,16,5}
//,{461,2,17,5}
//,{462,2,18,5}
//,{463,2,19,5}
//,{464,2,20,5}
//,{465,2,21,5}
//,{466,2,22,5}
//,{467,2,23,5}
//,{468,2,24,5}
//,{469,2,25,5}
//,{470,2,26,5}
//,{471,2,27,5}
//,{472,2,28,5}
//,{473,2,29,5}
//,{474,2,30,5}
//,{475,2,31,5}
//,{476,2,32,5}
//,{477,2,33,5}
//,{478,2,34,5}
//,{479,2,35,5}
//,{480,3,0,6}
//,{481,3,1,6}
//,{482,3,2,6}
//,{483,3,3,6}
//,{484,3,4,6}
//,{485,3,5,6}
//,{486,3,6,6}
//,{487,3,7,6}
//,{488,3,8,6}
//,{489,3,9,6}
//,{490,3,10,6}
//,{491,3,11,6}
//,{492,3,12,6}
//,{493,3,13,6}
//,{494,3,14,6}
//,{495,3,15,6}
//,{496,3,16,6}
//,{497,3,17,6}
//,{498,3,18,6}
//,{499,3,19,6}
//,{500,3,20,6}
//,{501,3,21,6}
//,{502,3,22,6}
//,{503,3,23,6}
//,{504,3,24,6}
//,{505,3,25,6}
//,{506,3,26,6}
//,{507,3,27,6}
//,{508,3,28,6}
//,{509,3,29,6}
//,{510,2,0,5}
//,{511,2,1,5}
//,{512,2,2,5}
//,{513,2,3,5}
//,{514,2,4,5}
//,{515,2,5,5}
//,{516,2,6,5}
//,{517,2,7,5}
//,{518,2,8,5}
//,{519,2,9,5}
//,{520,2,10,5}
//,{521,2,11,5}
//,{522,2,12,5}
//,{523,2,13,5}
//,{524,2,14,5}
//,{525,2,15,5}
//,{526,2,16,5}
//,{527,2,17,5}
//,{528,2,18,5}
//,{529,2,19,5}
//,{530,2,20,5}
//,{531,2,21,5}
//,{532,2,22,5}
//,{533,2,23,5}
//,{534,2,24,5}
//,{535,1,89,2}
//,{536,1,90,2}
//,{537,1,91,2}
//,{538,1,92,2}
//,{539,1,93,2}
//,{540,1,94,2}
//,{541,1,95,2}
//,{542,1,96,2}
//,{543,1,97,2}
//,{544,1,98,2}
//,{545,1,99,2}
//,{546,1,100,2}
//,{547,1,101,2}
//,{548,1,102,2}
//,{549,0,76,0}
//,{550,0,77,0}
//,{551,0,78,0}
//,{552,0,79,0}
//,{553,0,80,0}
//,{554,0,81,0}
//,{555,0,82,0}
//,{556,0,83,0}
//,{557,0,84,0}
//,{558,0,85,0}
//,{559,0,86,0}
//,{560,0,87,0}
//,{561,0,88,0}
//,{562,0,89,0}
//,{563,0,90,0}
//,{564,0,91,0}
//,{565,0,92,0}
//,{566,0,93,0}
//,{567,0,94,0}
//,{568,0,95,0}
//,{569,0,96,0}
//,{570,0,97,0}
//,{571,0,98,0}
//,{572,0,99,0}
//,{573,0,100,0}
//,{574,0,101,0}
//,{575,0,102,0}
//,{576,0,103,0}
//,{577,0,104,0}
//,{578,0,105,0}
//,{579,0,106,0}
//,{580,0,107,0}
//,{581,0,108,0}
//,{582,0,109,0}
//,{583,0,110,0}
//,{584,0,111,0}
//,{585,0,112,0}
//,{586,0,113,0}
//,{587,0,114,0}
//,{588,0,115,0}
//,{589,0,116,0}
//,{590,0,117,0}
//,{591,0,118,0}
//,{592,0,119,0}
//,{593,0,120,0}
//,{594,0,121,0}
//,{595,0,122,0}
//,{596,0,123,0}
//,{597,0,124,0}
//,{598,0,125,0}
//,{599,0,126,0}
// 
   };

int group[NUM_GROUPS];
CRGBPalette16 currentPalette;


void setup() {
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

  //TESTING
  int bpmIterator;
  randomSeed(analogRead(0));
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { bpmGroupBeta };
  //bpmGroup, bpmGroupGPLessIndexRange,bpmGroupRandPalette, bpmGroup60, bpmGroup120  };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  
void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 
  
  EVERY_N_SECONDS (30) { SetupTotallyRandomPalette(); CRGBPalette16 palette = currentPalette;}
  
  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))
// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}
void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}
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



void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16(13,0,NUM_LEDS);
  leds[pos] += CHSV( gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}


void bpmGroup()
{
   
    uint8_t brightness = 255;
  for( int g = 0; g < NUM_GROUPS; g++) {

    //get a random color from pallette for each group
    int randomColorIndex = map(g,0,NUM_GROUPS,0,255);
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = 60;
    CRGBPalette16 palette = PartyColors_p;
    uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
    
     for( int l = 0; l < NUM_LEDS; l++){ //9948
      leds[l] = ColorFromPalette(palette, gHue+(l*2) + randomColorIndex, beat-gHue+(l*10));
      //if(pixels[l].groupNum == g) {leds[l] = ColorFromPalette( palette, randomColorIndex, brightness);  } 
      //if(pixels[l].groupNum == g) {leds[l] =ColorFromPalette(palette, randomColorIndex, 100);}
    }
  }
}

void bpmGroupBeta()
{
   
    uint8_t brightness = 255;

  for( int g = 0; g < NUM_GROUPS; g++) {

    //get a random color from pallette for each group
    int randomColorIndex = randomColorIndex + map(g,0, NUM_GROUPS ,15,105);
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = 62;
    //CRGBPalette16 palette = ForestColors_p;
     CRGBPalette16 palette = RainbowColors_p;
    //CRGBPalette16 palette = currentPalette; 
    uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
    
     for( int l = 0; l < NUM_LEDS; l++){ //9948
      //leds[l] = ColorFromPalette(palette, gHue+(l*2) + randomColorIndex, beat-gHue+(l*10)); regular group full rainbow
      leds[l] = ColorFromPalette(palette, randomColorIndex + (l *3 ) + gHue, beat-gHue+(l*2));
      //if(pixels[l].groupNum == g) {leds[l] = ColorFromPalette( palette, randomColorIndex, brightness);  } 
      //if(pixels[l].groupNum == g) {leds[l] =ColorFromPalette(palette, randomColorIndex, 100);}
    }
  }
}

void bpmGroupMusic()
{
   
    uint8_t brightness = 255;

  for( int g = 0; g < NUM_GROUPS; g++) {

    //get a random color from pallette for each group
    int randomColorIndex = randomColorIndex + map(g,0, NUM_GROUPS ,15,105);
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = 62;
    //CRGBPalette16 palette = ForestColors_p;
     CRGBPalette16 palette = RainbowColors_p;
    //CRGBPalette16 palette = currentPalette; 
    uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
    
     for( int l = 0; l < NUM_LEDS; l++){ //9948
      //leds[l] = ColorFromPalette(palette, gHue+(l*2) + randomColorIndex, beat-gHue+(l*10)); regular group full rainbow
      leds[l] = ColorFromPalette(palette, randomColorIndex + (l *3 ) + gHue, beat-gHue+(l*2));
      //if(pixels[l].groupNum == g) {leds[l] = ColorFromPalette( palette, randomColorIndex, brightness);  } 
      //if(pixels[l].groupNum == g) {leds[l] =ColorFromPalette(palette, randomColorIndex, 100);}
    }
  }
}


void bpmGroupGPLessIndexRange()
{
   
// uint8_t brightness = 255;
 SetupPurpleAndGreenPalette();
 CRGBPalette16 palette = currentPalette;
 
  for( int g = 0; g < NUM_GROUPS; g++) {

    //get a random color from pallette for each group
    int randomColorIndex = map(g,0,NUM_GROUPS,0,255);
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = 30;

    uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
    
     for( int l = 0; l < NUM_LEDS; l++){ //9948
      leds[l] = ColorFromPalette(palette,  randomColorIndex, beat-gHue+(l*2));
      //if(pixels[l].groupNum == g) {leds[l] = ColorFromPalette( palette, randomColorIndex, brightness);  } 
      //if(pixels[l].groupNum == g) {leds[l] =ColorFromPalette(palette, randomColorIndex, 100);}
    }
  }
}

void bpmGroupRandPalette()
{
   
 //uint8_t brightness = 255;
//SetupTotallyRandomPalette(); 
 CRGBPalette16 palette = currentPalette;
 
  for( int g = 0; g < NUM_GROUPS; g++) {

    //get a random color from pallette for each group
    int randomColorIndex = map(g,0,NUM_GROUPS,0,255);
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = 60;

    uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
    
     for( int l = 0; l < NUM_LEDS; l++){ //9948
      leds[l] = ColorFromPalette(palette, gHue+(l*2) + randomColorIndex, beat-gHue+(l*10));
      //if(pixels[l].groupNum == g) {leds[l] = ColorFromPalette( palette, randomColorIndex, brightness);  } 
      //if(pixels[l].groupNum == g) {leds[l] =ColorFromPalette(palette, randomColorIndex, 100);}
    }
  }
}

void bpmGroup60()
{
   
  //  uint8_t brightness = 255;
  for( int g = 0; g < NUM_GROUPS; g++) {

    //get a random color from pallette for each group
    int randomColorIndex = map(g,0,NUM_GROUPS,0,255);
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = 60;
    CRGBPalette16 palette = PartyColors_p;
    uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
    
     for( int l = 0; l < NUM_LEDS; l++){ //9948
      leds[l] = ColorFromPalette(palette, gHue+(l*2) + randomColorIndex, beat-gHue+(l*10));
      //if(pixels[l].groupNum == g) {leds[l] = ColorFromPalette( palette, randomColorIndex, brightness);  } 
      //if(pixels[l].groupNum == g) {leds[l] =ColorFromPalette(palette, randomColorIndex, 100);}
    }
  }
}

void bpmGroup120()
{
   
   // uint8_t brightness = 255;
  for( int g = 0; g < NUM_GROUPS; g++) {

    //get a random color from pallette for each group
    int randomColorIndex = map(g,0,NUM_GROUPS,0,255);
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = 120;
    CRGBPalette16 palette = PartyColors_p;
    uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
    
     for( int l = 0; l < NUM_LEDS; l++){ //9948
      leds[l] = ColorFromPalette(palette, gHue+(l*2) + randomColorIndex, beat-gHue+(l*10));
      //if(pixels[l].groupNum == g) {leds[l] = ColorFromPalette( palette, randomColorIndex, brightness);  } 
      //if(pixels[l].groupNum == g) {leds[l] =ColorFromPalette(palette, randomColorIndex, 100);}
    }
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16(i+7,0,NUM_LEDS)] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}

