To execute imageDisplayer:

1) Go in the out folder

2)g++ -W -Wall -pedantic -o main -p apps/imageDisplayer/imageDisplayer.cpp -lstdc++fs -lopencv_highgui -lopencv_imgcodecs -lopencv_core

3)Execute ./main

# Yocto/PathExtension: On Histogram-preserving Blending for Randomized Texture Tiling
 **Riccard Gozzovelli - 1849977**

In this project we will present a possible implementation of how Texture Synthesis can be achieved for the Yocto/GL library. The main reference paper used is the one proposed by the [Walt Disney Animation Studios](http://www.jcgt.org/published/0008/04/02/paper.pdf) in 2019 which in turn, tried to enhance the already good results obtained by [Heitz and Neyret](https://hal.inria.fr/hal-01824773) in 2018.

We will provide first a small introduction about what Texture Synthesis is and how it can be effectively confronted. We will then illustrate our implementation and the results obtained with the help of some images.

## Introduction
Texture mapping is that method that allows to map the pixels of a texture to a 3D surface. Independently from the available resources, being able to create highly realistic scenes with many elements and high-resolution textures is always very difficult. Most of the time infact, textures are hand-painted and therefore small in size. To avoid repetitions many techniques have been developed, each of them with its own advantages and disadvantages. We do not only look for photo-realistic results, but we would also like to work with very fast methods. 

Texture Synthesis is indeed one of the processes involved in generating large images starting from small ones. *Perlin* or *Worley* noise are probably the oldest methods that tried to achieve procedural textures by exploiting **noise functions**. But using those methods for real-time renderings it's a very bad choiche since their speed perfomances are very poor. That's why in 2018, Eric Heitz and Fabrice Neyret proposed a novel way to generate good-looking large texture in a very short time.

### High-Performance By-Example Noise using Histogram-Preserving Blending Operator
We will only give a very small introduction of this paper in order to lay the foundations for the main reference on which the project is based upon. We can divide this method in two parts: 
- Tiling and Blending operation
- Histogram Transformations

#### TILING AND BLENDING
The input image is tiled with a equilater-triangle lattice in such a way to obtain a triangle grid. Given a point in the uv space, we can compute the local triangle  to which it belongs and the barycentric coordinates inside of it. By doing this, each point is covered always by three tiles. 
Next, the vertices of the triangle are altered with a small offset in order to fetch the original texture three times.

![Image](images/tiling_and_blending.png)

These three points are then linearly blended together using as weights the barycentric coordinates previously computed: I = w<sub>1</sub>I<sub>1</sub> + w<sub>2</sub>I<sub>2</sub> + w<sub>3</sub>I<sub>3</sub>

##### HISTOGRAM TRANSFORMATION
By simply linearly blending points it will be very likely to generate visual artifacts. Actually this occurs always when the histogram of the original image does not follow a gaussian distribution. In order to avoid this situation it is required to define a correct blending operator that can prevent this situation. Now, without going more in depth, the basic idea is to use a 3D look-up table (3D LUT) that allows to map the original pixel values to the transformed ones and viceversa.

### On Histogram-preserving Blending for Randomized Texture Tiling
The method illustrated so far is powerful but presents still some problems concerning:

- Speed
- Dimension of the textures
- No handle of grayscale textures
- 3D LUT is inefficient



## Submission

To submit the homework, you need to pack a ZIP file that contains all the code
you wrote, a readme file, all scenes and images you generated.
**Both people in the group should submit the same material.**
The file should be called `<lastname>_<firstname>_<studentid>.zip` 
(`<cognome>_<nome>_<matricola>.zip`) and you should exclude 
all other directories. Send it on Google Classroom.
 