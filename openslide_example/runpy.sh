# python read_svs.py &
# lsof -p $! | grep cairo  # /usr/lib/x86_64-linux-gnu/libcairo.so.2.11600.0

py-spy record -n -o openslide_new.svg --  python read_svs.py
