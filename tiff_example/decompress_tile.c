#include "tiffio.h"
#include <openjpeg.h>
#define false 0
#define true 1
#define bool int
#define OPENSLIDE_JP2K_YCBCR 1
#define OPENSLIDE_JP2K_RGB 0
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define CLAMP(x, lower, upper) (MIN(upper, MAX(x, lower)))
#include <cairo.h>

#include <stdlib.h>
#include <string.h>

const int16_t _openslide_R_Cr[256] = {
  -179, -178, -177, -175, -174, -172, -171, -170, -168, -167,
  -165, -164, -163, -161, -160, -158, -157, -156, -154, -153,
  -151, -150, -149, -147, -146, -144, -143, -142, -140, -139,
  -137, -136, -135, -133, -132, -130, -129, -128, -126, -125,
  -123, -122, -121, -119, -118, -116, -115, -114, -112, -111,
  -109, -108, -107, -105, -104, -102, -101, -100,  -98,  -97,
   -95,  -94,  -93,  -91,  -90,  -88,  -87,  -86,  -84,  -83,
   -81,  -80,  -79,  -77,  -76,  -74,  -73,  -72,  -70,  -69,
   -67,  -66,  -64,  -63,  -62,  -60,  -59,  -57,  -56,  -55,
   -53,  -52,  -50,  -49,  -48,  -46,  -45,  -43,  -42,  -41,
   -39,  -38,  -36,  -35,  -34,  -32,  -31,  -29,  -28,  -27,
   -25,  -24,  -22,  -21,  -20,  -18,  -17,  -15,  -14,  -13,
   -11,  -10,   -8,   -7,   -6,   -4,   -3,   -1,    0,    1,
     3,    4,    6,    7,    8,   10,   11,   13,   14,   15,
    17,   18,   20,   21,   22,   24,   25,   27,   28,   29,
    31,   32,   34,   35,   36,   38,   39,   41,   42,   43,
    45,   46,   48,   49,   50,   52,   53,   55,   56,   57,
    59,   60,   62,   63,   64,   66,   67,   69,   70,   72,
    73,   74,   76,   77,   79,   80,   81,   83,   84,   86,
    87,   88,   90,   91,   93,   94,   95,   97,   98,  100,
   101,  102,  104,  105,  107,  108,  109,  111,  112,  114,
   115,  116,  118,  119,  121,  122,  123,  125,  126,  128,
   129,  130,  132,  133,  135,  136,  137,  139,  140,  142,
   143,  144,  146,  147,  149,  150,  151,  153,  154,  156,
   157,  158,  160,  161,  163,  164,  165,  167,  168,  170,
   171,  172,  174,  175,  177,  178,
};

const int32_t _openslide_G_Cb[256] = {
   2919624,  2897070,  2874516,  2851963,  2829409,
   2806856,  2784302,  2761749,  2739195,  2716642,
   2694088,  2671534,  2648981,  2626427,  2603874,
   2581320,  2558767,  2536213,  2513659,  2491106,
   2468552,  2445999,  2423445,  2400892,  2378338,
   2355785,  2333231,  2310677,  2288124,  2265570,
   2243017,  2220463,  2197910,  2175356,  2152803,
   2130249,  2107695,  2085142,  2062588,  2040035,
   2017481,  1994928,  1972374,  1949821,  1927267,
   1904713,  1882160,  1859606,  1837053,  1814499,
   1791946,  1769392,  1746838,  1724285,  1701731,
   1679178,  1656624,  1634071,  1611517,  1588964,
   1566410,  1543856,  1521303,  1498749,  1476196,
   1453642,  1431089,  1408535,  1385982,  1363428,
   1340874,  1318321,  1295767,  1273214,  1250660,
   1228107,  1205553,  1183000,  1160446,  1137892,
   1115339,  1092785,  1070232,  1047678,  1025125,
   1002571,   980017,   957464,   934910,   912357,
    889803,   867250,   844696,   822143,   799589,
    777035,   754482,   731928,   709375,   686821,
    664268,   641714,   619161,   596607,   574053,
    551500,   528946,   506393,   483839,   461286,
    438732,   416179,   393625,   371071,   348518,
    325964,   303411,   280857,   258304,   235750,
    213196,   190643,   168089,   145536,   122982,
    100429,    77875,    55322,    32768,    10214,
    -12339,   -34893,   -57446,   -80000,  -102553,
   -125107,  -147660,  -170214,  -192768,  -215321,
   -237875,  -260428,  -282982,  -305535,  -328089,
   -350643,  -373196,  -395750,  -418303,  -440857,
   -463410,  -485964,  -508517,  -531071,  -553625,
   -576178,  -598732,  -621285,  -643839,  -666392,
   -688946,  -711499,  -734053,  -756607,  -779160,
   -801714,  -824267,  -846821,  -869374,  -891928,
   -914481,  -937035,  -959589,  -982142, -1004696,
  -1027249, -1049803, -1072356, -1094910, -1117464,
  -1140017, -1162571, -1185124, -1207678, -1230231,
  -1252785, -1275338, -1297892, -1320446, -1342999,
  -1365553, -1388106, -1410660, -1433213, -1455767,
  -1478320, -1500874, -1523428, -1545981, -1568535,
  -1591088, -1613642, -1636195, -1658749, -1681302,
  -1703856, -1726410, -1748963, -1771517, -1794070,
  -1816624, -1839177, -1861731, -1884285, -1906838,
  -1929392, -1951945, -1974499, -1997052, -2019606,
  -2042159, -2064713, -2087267, -2109820, -2132374,
  -2154927, -2177481, -2200034, -2222588, -2245141,
  -2267695, -2290249, -2312802, -2335356, -2357909,
  -2380463, -2403016, -2425570, -2448123, -2470677,
  -2493231, -2515784, -2538338, -2560891, -2583445,
  -2605998, -2628552, -2651106, -2673659, -2696213,
  -2718766, -2741320, -2763873, -2786427, -2808980,
  -2831534,
};

const int32_t _openslide_G_Cr[256] = {
   5990641,  5943839,  5897037,  5850235,  5803433,
   5756631,  5709829,  5663027,  5616225,  5569424,
   5522622,  5475820,  5429018,  5382216,  5335414,
   5288612,  5241810,  5195009,  5148207,  5101405,
   5054603,  5007801,  4960999,  4914197,  4867395,
   4820594,  4773792,  4726990,  4680188,  4633386,
   4586584,  4539782,  4492980,  4446179,  4399377,
   4352575,  4305773,  4258971,  4212169,  4165367,
   4118565,  4071763,  4024962,  3978160,  3931358,
   3884556,  3837754,  3790952,  3744150,  3697348,
   3650547,  3603745,  3556943,  3510141,  3463339,
   3416537,  3369735,  3322933,  3276132,  3229330,
   3182528,  3135726,  3088924,  3042122,  2995320,
   2948518,  2901717,  2854915,  2808113,  2761311,
   2714509,  2667707,  2620905,  2574103,  2527301,
   2480500,  2433698,  2386896,  2340094,  2293292,
   2246490,  2199688,  2152886,  2106085,  2059283,
   2012481,  1965679,  1918877,  1872075,  1825273,
   1778471,  1731670,  1684868,  1638066,  1591264,
   1544462,  1497660,  1450858,  1404056,  1357254,
   1310453,  1263651,  1216849,  1170047,  1123245,
   1076443,  1029641,   982839,   936038,   889236,
    842434,   795632,   748830,   702028,   655226,
    608424,   561623,   514821,   468019,   421217,
    374415,   327613,   280811,   234009,   187208,
    140406,    93604,    46802,        0,   -46802,
    -93604,  -140406,  -187208,  -234009,  -280811,
   -327613,  -374415,  -421217,  -468019,  -514821,
   -561623,  -608424,  -655226,  -702028,  -748830,
   -795632,  -842434,  -889236,  -936038,  -982839,
  -1029641, -1076443, -1123245, -1170047, -1216849,
  -1263651, -1310453, -1357254, -1404056, -1450858,
  -1497660, -1544462, -1591264, -1638066, -1684868,
  -1731670, -1778471, -1825273, -1872075, -1918877,
  -1965679, -2012481, -2059283, -2106085, -2152886,
  -2199688, -2246490, -2293292, -2340094, -2386896,
  -2433698, -2480500, -2527301, -2574103, -2620905,
  -2667707, -2714509, -2761311, -2808113, -2854915,
  -2901717, -2948518, -2995320, -3042122, -3088924,
  -3135726, -3182528, -3229330, -3276132, -3322933,
  -3369735, -3416537, -3463339, -3510141, -3556943,
  -3603745, -3650547, -3697348, -3744150, -3790952,
  -3837754, -3884556, -3931358, -3978160, -4024962,
  -4071763, -4118565, -4165367, -4212169, -4258971,
  -4305773, -4352575, -4399377, -4446179, -4492980,
  -4539782, -4586584, -4633386, -4680188, -4726990,
  -4773792, -4820594, -4867395, -4914197, -4960999,
  -5007801, -5054603, -5101405, -5148207, -5195009,
  -5241810, -5288612, -5335414, -5382216, -5429018,
  -5475820, -5522622, -5569424, -5616225, -5663027,
  -5709829, -5756631, -5803433, -5850235, -5897037,
  -5943839,
};

const int16_t _openslide_B_Cb[256] = {
  -227, -225, -223, -222, -220, -218, -216, -214, -213, -211,
  -209, -207, -206, -204, -202, -200, -198, -197, -195, -193,
  -191, -190, -188, -186, -184, -183, -181, -179, -177, -175,
  -174, -172, -170, -168, -167, -165, -163, -161, -159, -158,
  -156, -154, -152, -151, -149, -147, -145, -144, -142, -140,
  -138, -136, -135, -133, -131, -129, -128, -126, -124, -122,
  -120, -119, -117, -115, -113, -112, -110, -108, -106, -105,
  -103, -101,  -99,  -97,  -96,  -94,  -92,  -90,  -89,  -87,
   -85,  -83,  -82,  -80,  -78,  -76,  -74,  -73,  -71,  -69,
   -67,  -66,  -64,  -62,  -60,  -58,  -57,  -55,  -53,  -51,
   -50,  -48,  -46,  -44,  -43,  -41,  -39,  -37,  -35,  -34,
   -32,  -30,  -28,  -27,  -25,  -23,  -21,  -19,  -18,  -16,
   -14,  -12,  -11,   -9,   -7,   -5,   -4,   -2,    0,    2,
     4,    5,    7,    9,   11,   12,   14,   16,   18,   19,
    21,   23,   25,   27,   28,   30,   32,   34,   35,   37,
    39,   41,   43,   44,   46,   48,   50,   51,   53,   55,
    57,   58,   60,   62,   64,   66,   67,   69,   71,   73,
    74,   76,   78,   80,   82,   83,   85,   87,   89,   90,
    92,   94,   96,   97,   99,  101,  103,  105,  106,  108,
   110,  112,  113,  115,  117,  119,  120,  122,  124,  126,
   128,  129,  131,  133,  135,  136,  138,  140,  142,  144,
   145,  147,  149,  151,  152,  154,  156,  158,  159,  161,
   163,  165,  167,  168,  170,  172,  174,  175,  177,  179,
   181,  183,  184,  186,  188,  190,  191,  193,  195,  197,
   198,  200,  202,  204,  206,  207,  209,  211,  213,  214,
   216,  218,  220,  222,  223,  225,
};
struct buffer_state {
  uint8_t *data;
  int32_t offset;
  int32_t length;
};

static inline void write_pixel_ycbcr(uint32_t *dest, uint8_t Y,
                                     int16_t R_chroma, int16_t G_chroma,
                                     int16_t B_chroma) {
  int16_t R = Y + R_chroma;
  int16_t G = Y + G_chroma;
  int16_t B = Y + B_chroma;

  R = CLAMP(R, 0, 255);
  G = CLAMP(G, 0, 255);
  B = CLAMP(B, 0, 255);

  *dest = 0xff000000 | ((uint8_t) R << 16) | ((uint8_t) G << 8) | ((uint8_t) B);
}

static inline void write_pixel_rgb(uint32_t *dest,
                                   uint8_t R, uint8_t G, uint8_t B) {
  *dest = 0xff000000 | R << 16 | G << 8 | B;
}

static void unpack_argb(int  space,
                        opj_image_comp_t *comps,
                        uint32_t *dest,
                        int32_t w, int32_t h) {
  int c0_sub_x = w / comps[0].w;
  int c1_sub_x = w / comps[1].w;
  int c2_sub_x = w / comps[2].w;
  int c0_sub_y = h / comps[0].h;
  int c1_sub_y = h / comps[1].h;
  int c2_sub_y = h / comps[2].h;

  //g_debug("color space %d, subsamples x %d-%d-%d y %d-%d-%d", space, c0_sub_x, c1_sub_x, c2_sub_x, c0_sub_y, c1_sub_y, c2_sub_y);

  if (space == OPENSLIDE_JP2K_YCBCR &&
      c0_sub_x == 1 && c1_sub_x == 2 && c2_sub_x == 2 &&
      c0_sub_y == 1 && c1_sub_y == 1 && c2_sub_y == 1) {
    // Aperio 33003
    for (int32_t y = 0; y < h; y++) {
      int32_t c0_row_base = y * comps[0].w;
      int32_t c1_row_base = y * comps[1].w;
      int32_t c2_row_base = y * comps[2].w;
      int32_t x;
      for (x = 0; x < w - 1; x += 2) {
        uint8_t c0 = comps[0].data[c0_row_base + x];
        uint8_t c1 = comps[1].data[c1_row_base + (x / 2)];
        uint8_t c2 = comps[2].data[c2_row_base + (x / 2)];
        int16_t R_chroma = _openslide_R_Cr[c2];
        int16_t G_chroma = (_openslide_G_Cb[c1] + _openslide_G_Cr[c2]) >> 16;
        int16_t B_chroma = _openslide_B_Cb[c1];
        write_pixel_ycbcr(dest++, c0, R_chroma, G_chroma, B_chroma);
        c0 = comps[0].data[c0_row_base + x + 1];
        write_pixel_ycbcr(dest++, c0, R_chroma, G_chroma, B_chroma);
      }
      if (x < w) {
        uint8_t c0 = comps[0].data[c0_row_base + x];
        uint8_t c1 = comps[1].data[c1_row_base + (x / 2)];
        uint8_t c2 = comps[2].data[c2_row_base + (x / 2)];
        int16_t R_chroma = _openslide_R_Cr[c2];
        int16_t G_chroma = (_openslide_G_Cb[c1] + _openslide_G_Cr[c2]) >> 16;
        int16_t B_chroma = _openslide_B_Cb[c1];
        write_pixel_ycbcr(dest++, c0, R_chroma, G_chroma, B_chroma);
      }
    }

  } else if (space == OPENSLIDE_JP2K_YCBCR) {
    // Slow fallback


    for (int32_t y = 0; y < h; y++) {
      int32_t c0_row_base = (y / c0_sub_y) * comps[0].w;
      int32_t c1_row_base = (y / c1_sub_y) * comps[1].w;
      int32_t c2_row_base = (y / c2_sub_y) * comps[2].w;
      for (int32_t x = 0; x < w; x++) {
        uint8_t c0 = comps[0].data[c0_row_base + (x / c0_sub_x)];
        uint8_t c1 = comps[1].data[c1_row_base + (x / c1_sub_x)];
        uint8_t c2 = comps[2].data[c2_row_base + (x / c2_sub_x)];
        int16_t R_chroma = _openslide_R_Cr[c2];
        int16_t G_chroma = (_openslide_G_Cb[c1] + _openslide_G_Cr[c2]) >> 16;
        int16_t B_chroma = _openslide_B_Cb[c1];
        write_pixel_ycbcr(dest++, c0, R_chroma, G_chroma, B_chroma);
      }
    }

  } else if (space == OPENSLIDE_JP2K_RGB &&
             c0_sub_x == 1 && c1_sub_x == 1 && c2_sub_x == 1 &&
             c0_sub_y == 1 && c1_sub_y == 1 && c2_sub_y == 1) {
    // Aperio 33005
    for (int32_t y = 0; y < h; y++) {
      int32_t c0_row_base = y * comps[0].w;
      int32_t c1_row_base = y * comps[1].w;
      int32_t c2_row_base = y * comps[2].w;
      for (int32_t x = 0; x < w; x++) {
        uint8_t c0 = comps[0].data[c0_row_base + x];
        uint8_t c1 = comps[1].data[c1_row_base + x];
        uint8_t c2 = comps[2].data[c2_row_base + x];
        write_pixel_rgb(dest++, c0, c1, c2);
      }
    }

  } else if (space == OPENSLIDE_JP2K_RGB) {
    // Slow fallback
    

    for (int32_t y = 0; y < h; y++) {
      int32_t c0_row_base = (y / c0_sub_y) * comps[0].w;
      int32_t c1_row_base = (y / c1_sub_y) * comps[1].w;
      int32_t c2_row_base = (y / c2_sub_y) * comps[2].w;
      for (int32_t x = 0; x < w; x++) {
        uint8_t c0 = comps[0].data[c0_row_base + (x / c0_sub_x)];
        uint8_t c1 = comps[1].data[c1_row_base + (x / c1_sub_x)];
        uint8_t c2 = comps[2].data[c2_row_base + (x / c2_sub_x)];
        write_pixel_rgb(dest++, c0, c1, c2);
      }
    }
  }
}

static OPJ_SIZE_T read_callback(void *buf, OPJ_SIZE_T count, void *data) {
  struct buffer_state *state = data;

  count = MIN(count, (OPJ_SIZE_T) (state->length - state->offset));
  if (!count) {
    return (OPJ_SIZE_T) -1;
  }
  memcpy(buf, state->data + state->offset, count);
  state->offset += count;
  return count;
}

static OPJ_OFF_T skip_callback(OPJ_OFF_T count, void *data) {
  struct buffer_state *state = data;

  int32_t orig_offset = state->offset;
  state->offset = CLAMP(state->offset + count, 0, state->length);
  if (count && state->offset == orig_offset) {
    return -1;
  }
  return state->offset - orig_offset;
}

static OPJ_BOOL seek_callback(OPJ_OFF_T offset, void *data) {
  struct buffer_state *state = data;

  if (offset < 0 || offset > state->length) {
    return OPJ_FALSE;
  }
  state->offset = offset;
  return OPJ_TRUE;
}

bool decompress(uint32_t *dest,
                int32_t w, int32_t h,
                void *data, int32_t datalen,
                int space){

  opj_image_t *image = NULL;
  void *tmp_err = NULL;
  // GError *tmp_err = NULL;

  bool success = false;


  // init stream
  // avoid tracking stream offset (and implementing skip callback) by having
  // OpenJPEG read the whole buffer at once
  opj_stream_t *stream = opj_stream_create(datalen, true);
  struct buffer_state state = {
      .data = data,
      .length = datalen,
  };
  opj_stream_set_user_data(stream, &state, NULL);
  opj_stream_set_user_data_length(stream, datalen);
  opj_stream_set_read_function(stream, read_callback);
  opj_stream_set_skip_function(stream, skip_callback);
  opj_stream_set_seek_function(stream, seek_callback);

  // init codec
  opj_codec_t *codec = opj_create_decompress(OPJ_CODEC_J2K);
  opj_dparameters_t parameters;
  opj_set_default_decoder_parameters(&parameters);
  opj_setup_decoder(codec, &parameters);

  // enable error handlers
  // note: don't use info_handler, it outputs lots of junk
  // opj_set_warning_handler(codec, warning_callback, &tmp_err);
  // opj_set_error_handler(codec, error_callback, &tmp_err);

  // read header
  opj_read_header(stream, codec, &image);

  if(! opj_decode(codec, stream, image))
    goto DONE;

  // copy pixels
  unpack_argb(space, image->comps, dest, w, h);

  success = true;

DONE:
  opj_image_destroy(image);
  opj_destroy_codec(codec);
  opj_stream_destroy(stream);
  return success;
}


int main()
{
    char* slide_path = "/home/jylin/aetherAI/slides/4098031e-e0dd-4c75-8023-47601e773aca/TCGA-85-8049-01Z-00-DX1.59554c0f-d04a-41f2-b152-654a848b0443.svs";
    // TIFF* tif = TIFFOpen("10MB.tiff", "r");
    TIFF* tif = TIFFOpen(slide_path, "r");
    TIFF* out = TIFFOpen("output_tile.tif", "w");


    if (tif) {
        tdata_t buf;
        ttile_t tile_no=32000;

        printf("TIFFTileSize: %ld\n", TIFFTileSize(tif));  // 256*256*3
        printf("Number Of Tiles: %d\n", TIFFNumberOfTiles(tif)); // 244*300 tiles(level 0)
        long long cnt = 0, max = 0;

        // get tile size
        toff_t *sizes;
        if (TIFFGetField(tif, TIFFTAG_TILEBYTECOUNTS, &sizes) == 0) {
          printf("error get tile size\n");
          return 1;
        }
        tsize_t tile_size = sizes[tile_no];
        printf("compressed tile size: %ld\n", tile_size);
        // buf = _TIFFmalloc(TIFFTileSize(tif));
        // long long a = TIFFReadRawTile(tif, tile_no, buf, TIFFTileSize(tif));
        buf = _TIFFmalloc(tile_size);
        long long a = TIFFReadRawTile(tif, tile_no, buf, tile_size);
        TIFFWriteRawTile(out, 0, buf, tile_size);

        uint32_t* dest = (uint32_t*) malloc(TIFFTileSize(tif));
        // int space;
        // switch (l->compression) {
        // case 33003:
        //     space = OPENSLIDE_JP2K_YCBCR;
        //     break;
        // case 33005:
        //     space = OPENSLIDE_JP2K_RGB;
        //     break;
        // }
        
        /*
        for (tile = 0; tile < TIFFNumberOfTiles(tif); tile++){
            // TIFFReadEncodedTile(tif, tile, buf, (tsize_t) -1);
            long long a = TIFFReadRawTile(tif, tile, buf, TIFFTileSize(tif));
            // cnt += a;
            // max = MAX(max, a);
        }
        */
        printf("%lld \n", cnt); // 300 MB
        printf("%lld\n", max); // 14221 B

        if(!decompress(dest,
                256, 256,
                buf, tile_size,
                33003))
                printf("error decompress \n");

        cairo_surface_t *surface = cairo_image_surface_create_for_data(
                (unsigned char *) (dest),
                CAIRO_FORMAT_ARGB32, 256, 256, 256 * 4);
        cairo_t *cr = cairo_create (surface);
        cairo_surface_write_to_png (surface, "tile.png");

        unsigned char* c = (unsigned char*) dest;
        for(int i = 0; i < 20; i++) {
          printf("%d ", *c++);
          if(i%4==3)
            printf("\n");
        }
        _TIFFfree(buf);
        TIFFClose(tif);
    }
}