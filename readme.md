To execute imageDisplayer:

1) Go in the out folder

2)g++ -W -Wall -pedantic -o main -p apps/imageDisplayer/imageDisplayer.cpp -lstdc++fs -lopencv_highgui -lopencv_imgcodecs -lopencv_core

3)Execute ./main

# Yocto/PathExtension: On Histogram-preserving Blending for Randomized Texture Tiling
 **Riccard Gozzovelli - 1849977**

In this project we will present a possible implementation of how Texture Synthesis can be achieved for the Yocto/GL library. The main reference paper used is the one proposed by the [Walt Disney Animation Studios](http://www.jcgt.org/published/0008/04/02/paper.pdf) in 2019 which in turn, tried to enhance the already good results obtained by [Heitz and Neyret](https://hal.inria.fr/hal-01824773) in 2018.

We will provide first a small introduction about what Texture Synthesis is and how it can be effectively confronted. We will then illustrate our implementation and the results obtained with the help of some images.

## Introduction
Texture mapping is that method that allows to map the pixels of a texture to a 3D surface. Independently from the available resources, being able to create highly realistic scenes with many elements and high-resolution textures is always very difficult. Most of the time infact, textures are hand-painted and therefore small in size. If not properly handled, it will be possible to notice every single patch of the original texture applied to the object. To avoid this effect many techniques have been developed, combine two or multiple layers of the same texture with slight offsets, use random noise function to obtain different patterns or resynthesize similar looking textures. In any case we always look for methods that are fast and that can produce photo-realistic results.

Texture Synthesis is another possible method involved in generating large images starting from small ones. *Perlin* or *Worley* noise are probably the oldest methods that tried to achieve procedural textures by exploiting **noise functions**. But using those methods for real-time renderings it's a very bad choiche since their speed perfomances are very poor. That's why in 2018, Eric Heitz and Fabrice Neyret proposed a novel way to generate good-looking large texture in a very short time. One year later this method was enhanced to make it more efficient (faster and less memory demanding) but also to address different needs like handling high-resolution textures (4096x4096) and grayscale textures.

### Implementation
The way in which this method is implemented is straight-forward. It consists of two main operations:

- Texture Gaussianization
- Histogram-preserving blending

Both of these operations are the same that were introduced in the original paper but with some relevant differences. 

#### TEXTURE GAUSSIANIZATION
The first step of the method is to gaussianize the texture immediately after having loaded. This is done in the yscenetrace.cpp (or ysceneitrace.cpp) files when initializing materials. 
The algorithm starts at line 2147 and it is implemented as follows (steps are per channel):

- Loop over each texel of the texture, normalize the value in the range [0, 255] and update the number of occurence for that particular value inside a vector called *histogram_X* ( with X = {R,G,B} ).

- Loop over the elements in *histogram_X* and update the value of each element *i* as the sum of the current with the previous one *i-1* .

- Construct a 1D lookup table (**LUT**) where each element is computed as the inverse CDF of the input histogram. The LUT will therefore contain a mapping between the normalized texel value and their gaussianized representation.

- Add the attribute LUT to the Texture struct (inside *yocto_pathtrace.h*) and fill it with the values previously computed. 

The idea behind texture gaussianization is to make the histogram's channels of the image to follow a gaussian distribution. This should prevent the blending operation to produce unwanted color artifacts. Here some examples obtained:

![Image](images/texture_gaussianization3.png)

![Image](images/texture_gaussianization2.png)

![Image](images/texture_gaussianization1.png)

From left to right we have:
- The first image is the one obtained with the Yocto/GL implementation of the previous algorithm. It is possible to notice two things. The first one is that the patches of the original texture can be easily detected. The second is that the channels' histograms seems not to be completely gaussian. We believe that this might due to the fact that we are manipulating the texture through linear blending.
- The second image is the original texture used. Notice that the channels' histograms are not gaussian at all. 
- The third image was produced in order to prove that the first image is correct. These images are infact obtained in the same identical way to the original but without applying them to an object.

We conclude by pointing out that in the main reference paper, the texture gaussianization is applied only on one channel rather than in all of three.



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




## Submission

To submit the homework, you need to pack a ZIP file that contains all the code
you wrote, a readme file, all scenes and images you generated.
**Both people in the group should submit the same material.**
The file should be called `<lastname>_<firstname>_<studentid>.zip` 
(`<cognome>_<nome>_<matricola>.zip`) and you should exclude 
all other directories. Send it on Google Classroom.
 