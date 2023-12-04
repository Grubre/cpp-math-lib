cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1
cmake --build build
rm compile_commands.json
ln -s build/compile_commands.json compile_commands.json
for test in "$@"
do
    ./build/$test
done
