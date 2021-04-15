export C_INCLUDE_PATH="/usr/include/openjpeg-2.3:/usr/include/cairo"
gcc decompress_tile.c -ltiff -lopenjp2 -lcairo