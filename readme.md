### Build

command line:
```
cmake -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - MinGW Makefiles" -S . -B build
cmake --build build --target all -- -j 3
```
or
```
cmake -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - MinGW Makefiles" -S . -B build
cmake --build build --target install
```
