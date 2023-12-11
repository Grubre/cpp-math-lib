cd build
cmake .. -DENABLE_TESTS=OFF -DENABLE_EXAMPLES=ON
cmake --build .
./examples/$1
