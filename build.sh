# clean/setup
if [ -d build ]; then
    rm build/cgame
else
    mkdir build
fi

# build
g++ app/src/main.cpp -o build/cgame && \

# run
build/cgame