export C_INCLUDE_PATH="/usr/include/cairo"
# gcc -o hello hello.c -lcairo
# gcc  -o drawing drawing.c  -lcairo
# gcc -o line line.c -lcairo
gcc -o source_operator source_operator.c -lcairo
# gcc -o paint paint.c -lcairo -ljpeg
# gcc -o push_pop push_pop.c -lcairo 
# gcc -o pattern pattern.c -lcairo

