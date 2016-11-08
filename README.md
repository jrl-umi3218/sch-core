sch-core
========

[![Build Status](https://travis-ci.org/jrl-umi3218/sch-core.svg?branch=master)](https://travis-ci.org/jrl-umi3218/sch-core)
[![Coverage Status](https://coveralls.io/repos/jrl-umi3218/sch-core/badge.png)](https://coveralls.io/r/jrl-umi3218/sch-core)


Documentation
-------------
Efficient implementation of GJK algorithm for proximity queries (collision detection, distance computations, penetration depths and witness points) between convex shapes.

The library can be extended to any convex shape for which we can compute the support function, but it already supports polyhedrons, boxes, spheres and ellipsoids, and it is particularly optimized for strictly convex hulls (SCH/STP-BV).

The implementation is detailed in:

    @INPROCEEDINGS{benallegue:icra:2009,
      author={Benallegue, M. and Escande, A. and Miossec, S. and Kheddar, A.},
      booktitle={Robotics and Automation, 2009. ICRA '09. IEEE International Conference on},
      title={Fast C1 proximity queries using support mapping of sphere-torus-patches bounding volumes},
      year={2009},
      month={May},
      pages={483-488},
      keywords={Application software;Assembly;Clouds;Computer graphics;Robotics and automation;Robots;Shape;Target tracking;Testing;Trajectory},
      doi={10.1109/ROBOT.2009.5152722},
      ISSN={1050-4729},
    }

And a description of strictly convext hulls is detailed in:

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


### Ubuntu 14.04 and 16.04 binary ppa install

Use the [multi-contact-unstable](https://launchpad.net/~pierre-gergondet+ppa/+archive/ubuntu/multi-contact-unstable) ppa:
```bash
sudo add-apt-repository ppa:pierre-gergondet+ppa/multi-contact-unstable
sudo apt-get update
sudo apt-get install libsch-core-dev libsch-core-doc
```

### Homebrew OS X install

Install from the command line using [Homebrew](brew.sh):

```bash
# install homebrew package manager
ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
# install caskroom application manager
brew install caskroom/cask/brew-cask
# tap homebrew-science package repository
brew tap homebrew/science
# tap ahundt-robotics repository
brew tap ahundt/robotics
# install tasks and all its dependencies
brew install sch-core
```

## Manually build from source


Building using cmake:

```bash
git clone https://github.com/jrl-umi3218/sch-core.git --recursive
mkdir -p sch-core/build
cd sch-core/build
cmake .. # you probably want to define `CMAKE_INSTALL_PREFIX`
make
sudo make install
```

Indentation
------------

    astyle --style=allman --lineend=linux --indent=spaces=2 --indent-namespaces
