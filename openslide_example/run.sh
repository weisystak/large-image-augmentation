gcc read_svs.c  -I/usr/local/include/openslide -lopenslide
# gcc -ggdb -g3 -fno-omit-frame-pointer read_svs.c -I/usr/local/include/openslide    -lopenslide  -Wl,-rpath=/usr/local/lib/
# ./a.out &
# lsof -p $! | grep openslide

# sudo perf record -g  ./a.out 
# sudo perf script > out.perf
# FlameGraph/stackcollapse-perf.pl out.perf > out.folded
# FlameGraph/flamegraph.pl out.folded > kernel.svg