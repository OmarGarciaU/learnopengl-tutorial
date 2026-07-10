# learnopengl-tutorial

## Setup 

I have found a way to succefully set up an openGL graphics project on Mac using GLFW and GLAD with GLM math libraries

There are 3 main categories in this set up:
* Makefile 
* src
* bin

### Makefile
This Project uses the makefile as a build script to compile the project into an executable in the bin folder

### src 

In src directory there is an include directory which contains the glad c and header files with the glad binary as glad.o 

In include I have all the libs neccessary for building the project 
I have edited all the .h files in include so that all headers are called properly 

### bin
Stores the necessary files and executables to run the program

## Running the code 
Execute the makefile using the make command
```
make && bin/myApp && cd ..
```

## Goals
My first goal for this repo is to document my C++/C/OpenGL journey.
My second goal for this repo is to have a repo available to run openGL code out of 
the box without the struggle of building something from scratch on Mac
