# 3D Raytracer Scene.

The scene contains simple geometric objects which incorparate physical concepts such
as refraction and reflection.

## Author

William Jelley

## How to run file

To compile and run, enter the following commands in to the linux terminal:
'''
$ g++ -Wall -o raytracer *.cpp -lm -lGL -lglut -lGLU
$ ./raytracer
'''
## Anti-aliasing feature

The anti-aliasing feature is enabled by default. If you wish to disable anti-aliasing
you must set the global boolean variable anti_alias to false (line 30 of RayTracer.cpp).

