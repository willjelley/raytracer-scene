# 3D Raytracer Scene.

The scene contains simple geometric objects which incorparate physical concepts such
as refraction and reflection. This was completed as an assignment for COSC363 Computer
Graphics at University of Canterbury in May 2016.

## Author

William Jelley

## How to run file

To compile and run, enter the following commands in to the linux terminal:

$ g++ -Wall -o raytracer *.cpp -lm -lGL -lglut -lGLU

$ ./raytracer

## Anti-aliasing feature

The anti-aliasing feature is enabled by default. If you wish to disable anti-aliasing
you must set the global boolean variable anti_alias to false (line 30 of RayTracer.cpp).
Note that without anti-aliasing the raytracer will take less time to load, but some
objects may appear more jagged around the edges.

