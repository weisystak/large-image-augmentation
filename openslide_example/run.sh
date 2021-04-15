gcc read_svs.c  -I$HOME/.local/openslide/include/openslide -L$HOME/.local/openslide/lib -lopenslide  
echo "original" > a.log
./a.out >> a.log 
sudo ln -sf $HOME/.local/openslide/lib/libopenslide.so.0.4.1  /usr/lib/x86_64-linux-gnu/libopenslide.so.0
gcc read_svs.c  -I$HOME/.local/openslide/include/openslide -L$HOME/.local/openslide/lib -lopenslide  
echo "remove cairo" >> a.log
./a.out >> a.log
# reset
sudo ln -sf  /usr/lib/x86_64-linux-gnu/libopenslide.so.0.4.1   /usr/lib/x86_64-linux-gnu/libopenslide.so.0
# gcc -ggdb -g3 -fno-omit-frame-pointer read_svs.c -I/usr/local/include/openslide    -lopenslide  -Wl,-rpath=/usr/local/lib/
# ./a.out &
# lsof -p $! | grep openslide

# sudo perf record -g  ./a.out 
# sudo perf script > out.perf
# FlameGraph/stackcollapse-perf.pl out.perf > out.folded
# FlameGraph/flamegraph.pl out.folded > kernel.svg