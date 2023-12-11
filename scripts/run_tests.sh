cd build
cmake .. -DENABLE_TESTS=ON -DENABLE_EXAMPLES=OFF
cmake --build .
ctest $1
