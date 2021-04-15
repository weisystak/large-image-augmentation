#include "tiffio.h"
#include <unistd.h>
#include <pwd.h>

int main(int argc, char* argv[])
{

	char* slide_path = "/home/jylin/aetherAI/slides/4098031e-e0dd-4c75-8023-47601e773aca/TCGA-85-8049-01Z-00-DX1.59554c0f-d04a-41f2-b152-654a848b0443.svs";
	FILE* fd = fopen("dir", "w");
    TIFF* tif = TIFFOpen(slide_path, "r");
    if (tif) {
		int dircount = 1;
		do {
			dircount++;
			TIFFPrintDirectory(tif, fd, 0x0);
		} while (TIFFReadDirectory(tif));
		printf("%d directories\n", dircount);
		TIFFClose(tif);
    }
}