#include "tiffio.h"
#define MAX(a,b) (((a)>(b))?(a):(b))
int main()
{
    char* slide_path = "/home/jylin/aetherAI/slides/4098031e-e0dd-4c75-8023-47601e773aca/TCGA-85-8049-01Z-00-DX1.59554c0f-d04a-41f2-b152-654a848b0443.svs";
    // TIFF* tif = TIFFOpen("10MB.tiff", "r");
    TIFF* tif = TIFFOpen(slide_path, "r");

    if (tif) {
        tdata_t buf;
        ttile_t tile;

        // buf = _TIFFmalloc(TIFFTileSize(tif));
        printf("%ld\n", TIFFTileSize(tif));  // 256*256*3
        printf("%d\n", TIFFNumberOfTiles(tif)); // 244*300 tiles(level 0)
        long long cnt = 0, max = 0;
        #pragma omp parallel num_threads(8)
        {
            buf = _TIFFmalloc(TIFFTileSize(tif));
            #pragma omp for
            for (tile = 0; tile < TIFFNumberOfTiles(tif); tile++){
                // TIFFReadEncodedTile(tif, tile, buf, (tsize_t) -1);
                long long a = TIFFReadRawTile(tif, tile, buf, TIFFTileSize(tif));
                // cnt += a;
                // max = MAX(max, a);
            }
        }
        printf("%lld \n", cnt); // 300 MB
        printf("%lld\n", max); // 14221 B
        _TIFFfree(buf);
        TIFFClose(tif);
    }
}