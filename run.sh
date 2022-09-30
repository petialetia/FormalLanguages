TARGET="$1"

./build.sh $TARGET

if [[($TARGET == "--test")]]
then 
    ./bin/Tests.out
elif [[($TARGET == "--coverage")]]
then
    xdg-open build/ccov/Tests/index.html
else
    ./bin/Main.out
fi