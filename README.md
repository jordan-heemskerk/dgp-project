# CSC486a: Digital Geometry Processing Final Project
**Jordan Heemskerk, Jorin Weatherston, Robert Leahy**
## An Implementation of Shape-Up: Shaping Discrete Geometry With Projections

### Introduction
For this project, a C++ partial implementation of the Shape-Up paper[1] was completed. The main contribution from this paper was an engine that operated on meshes and allowed shape-based constraints to be used in a "plug and play" manner. For this to work, each different type of constraint must specify a "projection" function, which maps a given set of vertices onto the ideal case of the constraint. As an example, a plane constraint might find the best fitting plane for the given set of points and return the closest point on that plane for each point as the projection. 

The main engine works through an iterative local-global approach. The engine's goal is to minimize the distance of the mesh from every projection, relative to its given weight. The does the following steps iteratavely:
1) Compute the projection matrix b from each constraint on the *current* vertex positions.
2) Solve the system A'Ax = A'b, where A weights and mean-centers the associated vertices of each constraint. There is a row in A for each projection. 

Since the matrix A'A is specified once and is sparse, it can be Cholesky factorized to efficiently solve the 2nd step iteratively. 

## Results From Our Implementation
For our implementation, the main engine was developed, as well as a subset of the different constraints mentioned in [1], namely:
* Line and Plane Constraints
* Circle and Sphere Constraints
* Rigid and Similarity Constriants

Some examples of our results include the realtime deformation of a plane, adhering to the constraint of having isometric one-ring neighbourhoods. This can be seen in the following set of screenshots.

![quad2-1](https://github.com/jordan-heemskerk/dgp-project/blob/project/project/examples/quad2-1.png "quad2-1")
![quad2-2](https://github.com/jordan-heemskerk/dgp-project/blob/project/project/examples/quad2-2.png "quad2-2")
![quad2-3](https://github.com/jordan-heemskerk/dgp-project/blob/project/project/examples/quad2-3.png "quad2-3")

### References
[1] [Bouaziz, S., Deuss, M., Schwartzburg, Y., Weise, T., & Pauly, M. (2012). Shape‐Up: Shaping discrete geometry with projections. Computer Graphics Forum, 31(5), 1657-1667. doi:10.1111/j.1467-8659.2012.03171.x](http://lgg.epfl.ch/publications/2012/shapeup/index.php)
