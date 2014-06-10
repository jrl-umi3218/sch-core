[![Build Status](https://travis-ci.org/jrl-umi3218/sch-core.svg?branch=master)](https://travis-ci.org/jrl-umi3218/sch-core)
[![Coverage Status](https://coveralls.io/repos/jrl-umi3218/sch-core/badge.png)](https://coveralls.io/r/jrl-umi3218/sch-core)

sch-core
========


Documentation
-------------

Implementation and computation algorithms for the convex hulls detailed in:

    @article{escande:itro:2014,
      author = {Adrien Escande and Sylvain Miossec and Mehdi Benallegue and Abderrahmane Kheddar},
      title = {A Strictly Convex Hull for Computing Proximity Distances with Continuous Gradients},
      journal={Robotics, IEEE Transactions on}, 
      year = {2014},
      month={June}, 
      volume={30}, 
      number={3}, 
      pages={666-678}, 
      keywords={Collision avoidance;Convergence;Optimization;Planning;Robots;Shape;Vectors;Bounding volume;continuous gradients of proximity distances;smooth and nonsmooth optimization;sphere-torus patches;strictly convex hulls}, 
      doi={10.1109/TRO.2013.2296332}, 
      ISSN={1552-3098},
      url = {https://sites.google.com/site/adrienescandehomepage/publications/2014_ITRO_Escande.pdf}
    }


Installation
------------

Building using cmake:
- create a new build directory
- run `cmake ..` in this directory 
  (you probably want to define `CMAKE_INSTALL_PREFIX`)
- `make`
- `make install`


Indentation
------------

    astyle --style=allman --lineend=linux --indent=spaces=2 --indent-namespaces

