# CSC486a: Digital Geometry Processing Final Project
**Jordan Heemskerk, Jorin Weatherston, Robert Leahy**
## An Implementation of Shape-Up: Shaping Discrete Geometry With Projections

### Introduction
For this project, a C++ partial implementation of the Shape-Up paper[1] was completed. The main contribution from this paper was an engine that operated on meshes and allowed shape-based constraints to be used in a "plug and play" manner. For this to work, each different type of constraint must specify a "projection" function, which maps a given set of vertices onto the ideal case of the constraint. As an example, a plane constraint might find the best fitting plane for the given set of points and return the closest point on that plane for each point as the projection. 

The main engine works through an iterative local-global approach. The engine's goal is to minimize the distance of the mesh from every projection, relative to its given weight. The engine does the following steps iteratavely:
 1. Compute the projection matrix b from each constraint on the *current* vertex positions.
 2. Solve the system A'Ax = A'b, where A weights and mean-centers the associated vertices of each constraint. There is a row in A for each projection. 

Since the matrix A'A is specified once and is sparse, it can be Cholesky factorized to efficiently solve the 2nd step iteratively. 

### Results From Our Implementation
For our implementation, the main engine was developed, as well as a subset of the different constraints mentioned in [1], namely:
* Scale and Closeness Constraints
* Line and Plane Constraints
* Circle and Sphere Constraints
* Rigid and Similarity Constriants

Some examples of our results include the realtime deformation of a plane, adhering to the constraint of having isometric one-ring neighbourhoods. This can be seen in the following set of screenshots.

![quad2-1](https://github.com/jordan-heemskerk/dgp-project/blob/project/project/examples/quad2-1.png "quad2-1")
![quad2-2](https://github.com/jordan-heemskerk/dgp-project/blob/project/project/examples/quad2-2.png "quad2-2")
![quad2-3](https://github.com/jordan-heemskerk/dgp-project/blob/project/project/examples/quad2-3.png "quad2-3")

### Future Work
As seen in the rigid demo with quad3 (see Demos), growing the number of vertices starts to have an effect on the performance of the system. This is largely due to unoptimized code in the projection stage. Currently there is a lot of memory allocation that could be preallocated instead of doing it each time. Optimizing each of the projection functions, and the way that the entire projection vector is built would probably help our implementation to run on larger meshes.

### Building

```bash
cmake .
cd project
make
./project rigid quad2.obj    # isometric one rings on quad (example above)
```

### Controls

Depending on which demo you run, there are some different controls available. For the rigid examples the arrow keys move the movable handle in 2 dimensions, the other dimension is controlled by the comma and period keys. Clicking in some examples will print the vertex index to the console. Clicking in the scalable constraint demo will add a scaling constriant to the vertices which have been clicked.


### Demos

```bash
./project rigid quad2.obj # must use only these meshes to have handles defined
./project rigid bunny.obj
./project rigid quad3.obj

./project pick <any mesh> # interface for determining vertex indices

./project test <any mesh> # add scalable constraint to clicked vertices (closeness on all others)

./project sphere <any mesh> # project all vertices onto the best fitting sphere
```


### References
[1] [Bouaziz, S., Deuss, M., Schwartzburg, Y., Weise, T., & Pauly, M. (2012). Shape‐Up: Shaping discrete geometry with projections. Computer Graphics Forum, 31(5), 1657-1667. doi:10.1111/j.1467-8659.2012.03171.x](http://lgg.epfl.ch/publications/2012/shapeup/index.php)
