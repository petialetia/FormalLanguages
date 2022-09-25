TARGET="$1"

./build.sh $TARGET

if [[($TARGET == "--test")]]
then 
    ./bin/Tests.out
else
    ./bin/MinimalDFA.out
fi