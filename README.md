# Ray Tracer

![](renders/progress_8-6-20.jpg)

This is a ray tracer that follows [Ray Tracing from the Ground Up (1st Edition) by Kevin Suffern](https://www.crcpress.com/Ray-Tracing-from-the-Ground-Up/Suffern/p/book/9781568812724).

This is my work through of the content in the book, which so far looks really good! The starting project will be tagged when it is ready.

## Motivation

The starting project was made with code for an older version of windows, so I'm taking the liberty to update it to use cmake, and a newer version of wxWidgets.

## Dependencies

This currently depends on wxWidgets to get running. I installed this library through choco:

    choco install wxWidgets

Hopefully I'll be able to figure out a way to make it included in the project's source code so that installation on new system will be easier.

## How to build

Runt the following
  
 mkdir build

    cd build

    cmake `
    -G "Visual Studio 15 2017 Win64" `
    -DwxWidgets_ROOT_DIR="C:\wxWidgets-3.1.2" `
    -DwxWidgets_LIB_DIR="C:\wxWidgets-3.1.2\lib\vc_x64_lib" `
    ..

This should compile, and then run with the generated build system!

## Chapter Progression

A chapter will be complete when I read the material and do its exercises.

- [x] 1 - Ray Tracing Design and Programming
- [x] 2 - Some Essential Mathematics
- [ ] 3 - Bare-Bones Ray Tracing
- [ ] 4 - Antialiasing
- [ ] 5 - Sampling Techniques
- [ ] 6 - Mapping Samples to a Disk
- [ ] 7 - Mapping Samples to a Hemisphere
- [ ] 8 - Perspective Viewing
- [ ] 9 - A Practical Viewing System
- [ ] 10 - Depth of Field
- [ ] 11 - Nonlinear Projections
- [ ] 12 - Stereoscopy
- [ ] 13 - Theoretical Foundations
- [ ] 14 - Lights and Materials
- [ ] 15 - Specular Reflection
- [ ] 16 - Shadows
- [ ] 17 - Ambient Occlusion
- [ ] 18 - Area Lights
- [ ] 19 - Ray-Object Intersections
- [ ] 20 - Affine Transformations
- [ ] 21 - Transforming Objects
- [ ] 22 - Regular Grids
- [ ] 23 - Triangle Meshes
- [ ] 24 - Mirror Reflection
- [ ] 25 - Glossy Reflection
- [ ] 26 - Global Illumination
- [ ] 27 - Simple Transparency
- [ ] 28 - Realistic Transparency
- [ ] 29 - Texture Mapping
- [ ] 30 - Procedural Textures
- [ ] 31 - Noise-Based Textures
