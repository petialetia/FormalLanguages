TARGET="$1"

mkdir -p build
cd build

if [[($TARGET == "--coverage")]]
then
    cmake -DCODE_COVERAGE=ON ..
elif [[($TARGET == "--debug")]]
then
    cmake -DCMAKE_BUILD_TYPE=Debug ..
else
    cmake ..
fi

if [[($TARGET == "--test")]]
then
    cmake --build . --target Tests -j 16
elif [[($TARGET == "--coverage")]]
then 
    cmake --build . --target ccov -j 16
else
    cmake --build . -j 16
fi