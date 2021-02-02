#include "openslide.h"
#include <stdlib.h>


int main()
{
    char* slide_path = "/home/jylin/aetherAI/slides/4098031e-e0dd-4c75-8023-47601e773aca/TCGA-85-8049-01Z-00-DX1.59554c0f-d04a-41f2-b152-654a848b0443.svs";
    
    int32_t target_level = 2;
    int64_t target_width = 0, target_height = 0;
    uint32_t* buf;

    openslide_t* slide = openslide_open(slide_path);
    openslide_get_level_dimensions(slide, target_level, &target_width, &target_height);

    buf = (uint32_t*)(malloc(target_width * target_height * sizeof(uint32_t)));
    // cout<< target_width<<" "<< target_height<< endl;
    openslide_read_region(slide, buf, 0, 0, target_level, target_width, target_height);

    openslide_close(slide);
}