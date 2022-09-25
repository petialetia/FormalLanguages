TARGET="$1"

mkdir -p build
cd build

if [[($TARGET == "--debug")]]
then
    cmake -DCMAKE_BUILD_TYPE=Debug ..
else
    cmake ..
fi

if [[($TARGET == "--test")]]
then
    cmake --build . --target Tests -j 16
else
    cmake --build . -j 16
fi