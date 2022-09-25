TARGET="$1"

mkdir -p build
cd build
cmake ..

if [[($TARGET == "--test")]]
then
    cmake --build . --target Tests -j 16
else
    cmake --build . -j 16
fi