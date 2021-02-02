# python read_svs.py &
# lsof -p $! | grep cairo  # /usr/lib/x86_64-linux-gnu/libcairo.so.2.11600.0
# lsof -p $! | grep pixman  # /usr/lib/x86_64-linux-gnu/libpixman-1.so.0.38.4

py-spy record -n -o openslide_new_cairo_pixman.svg --  python read_svs.py
