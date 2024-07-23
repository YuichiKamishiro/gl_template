#!/bin/bash

g++ -Iinclude src/glad.c -c
g++ -Iinclude src/main.cpp glad.o -lglfw -lGL -ldl -lGLU -o out

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running the binary..."
    ./out
else
    echo "Compilation failed. Not running the binary."
fi
