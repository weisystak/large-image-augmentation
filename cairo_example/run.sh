export C_INCLUDE_PATH="/usr/include/cairo"
gcc -o hello hello.c -lcairo
gcc  -o drawing drawing.c  -lcairo
gcc -o line line.c -lcairo