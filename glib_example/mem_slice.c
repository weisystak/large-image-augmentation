#include <gmodule.h>

int main()
{
    gchar *mem[10000];
    gint i;

    // Allocate 10000 blocks.
    for (i = 0; i < 10000; i++)
    {
        mem[i] = g_slice_alloc (50);

        // Fill in the memory with some junk.
        for (j = 0; j < 50; j++)
        mem[i][j] = i * j;
    }

    // Now free all of the blocks.
    for (i = 0; i < 10000; i++)
    g_slice_free1 (50, mem[i]);

    // And here is an example for using the using the slice allocator with data structures:

    GRealArray *array;

    // Allocate one block, using the g_slice_new() macro.
    array = g_slice_new (GRealArray);

    // We can now use array just like a normal pointer to a structure.
    array->data            = NULL;
    array->len             = 0;
    array->alloc           = 0;
    array->zero_terminated = (zero_terminated ? 1 : 0);
    array->clear           = (clear ? 1 : 0);
    array->elt_size        = elt_size;

    // We can free the block, so it can be reused.
    g_slice_free (GRealArray, array);
}


