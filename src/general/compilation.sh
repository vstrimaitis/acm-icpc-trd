# Simple compile
g++ -DLOCAL -O2 -o main.exe -std-c++17 -Wall -Wno-unused-result -Wshadow main.cpp
# Debug
g++ -DLOCAL -std=c++17 -Wshadow -Wall -o main.exe main.cpp -fsanitize=address -fsanitize=undefined -fuse-ld=gold -D_GLIBCXX_DEBUG -g