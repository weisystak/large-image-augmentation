gcc read_svs.c  -I$HOME/.local/openslide/include/openslide -L$HOME/.local/openslide/lib -lopenslide  
# gcc -ggdb -g3 -fno-omit-frame-pointer read_svs.c -I/usr/local/include/openslide    -lopenslide  -Wl,-rpath=/usr/local/lib/
# ./a.out &
# lsof -p $! | grep openslide

# sudo perf record -g  ./a.out 
# sudo perf script > out.perf
# FlameGraph/stackcollapse-perf.pl out.perf > out.folded
# FlameGraph/flamegraph.pl out.folded > kernel.svg