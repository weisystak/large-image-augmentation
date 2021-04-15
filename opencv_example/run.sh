cd build
conan install .. --build missing
cmake ..
make
./resize
cd ..