#include "tiffio.h"
int main()
{
//     TIFF* tif = TIFFOpen("5184x3456.tiff", "r");
    TIFF* tif = TIFFOpen("10MB.tiff", "r");

    if (tif) {
        tdata_t buf;
        tstrip_t strip;
        uint32* bc;
        uint32 stripsize;

        TIFFGetField(tif, TIFFTAG_STRIPBYTECOUNTS, &bc);
        stripsize = bc[0];
        buf = _TIFFmalloc(stripsize);
        
        printf("%d\n", TIFFNumberOfStrips(tif));

        for (strip = 0; strip < TIFFNumberOfStrips(tif); strip++) {
            if (bc[strip] > stripsize) {
                buf = _TIFFrealloc(buf, bc[strip]);
                stripsize = bc[strip];
            }
            printf("%d\n", bc[strip]);
            TIFFReadRawStrip(tif, strip, buf, bc[strip]);
        }
        _TIFFfree(buf);
        TIFFClose(tif);
    }
}