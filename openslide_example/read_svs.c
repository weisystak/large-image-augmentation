#include <openslide.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    // char* slide_path = "/home/jylin/aetherAI/slides/4098031e-e0dd-4c75-8023-47601e773aca/TCGA-85-8049-01Z-00-DX1.59554c0f-d04a-41f2-b152-654a848b0443.svs";
    char* slide_path = "/home/jylin/aetherAI/slides/1f26c70d-0e98-46cf-b7f8-aae618a3bfd5/TCGA-77-7337-01Z-00-DX1.e15727e3-e9c8-44a0-87bb-caeaeb00840c.svs";
    
    int32_t target_level = 0;
    int64_t target_width = 0, target_height = 0;
    uint32_t* buf;

    openslide_t* slide = openslide_open(slide_path);
    openslide_get_level_dimensions(slide, target_level, &target_width, &target_height);

    buf = (uint32_t*)(malloc(target_width * target_height * sizeof(uint32_t)));

    printf("target_width: %ld, target_height: %ld\n", target_width, target_height);

    openslide_read_region(slide, buf, 0, 0, target_level, target_width, target_height);
    
    int x = 122*256;
    int y = 150*256;
    int n = 6;
    for (int i = y-n; i <= y+n; i++) {
        for(int j = x-n; j <= x+n; j++) {
            unsigned char* t =  (unsigned char*) (buf + (i*target_width)+j);
            for(int k = 0; k < 4; k++){
                printf("%d ", t[k]);
            }
            printf("\t");
        }
        printf("\n");
    }
    openslide_close(slide);
}