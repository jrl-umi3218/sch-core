sch-core
========

[![License](https://img.shields.io/badge/License-BSD%202--Clause-green.svg)](https://opensource.org/licenses/BSD-2-Clause)/[![License: GPL v2](https://img.shields.io/badge/License-GPL%20v2-green.svg)](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html)
[![Hosted By: Cloudsmith](https://img.shields.io/badge/OSS%20hosting%20by-cloudsmith-blue?logo=cloudsmith)](https://cloudsmith.com)
[![CI](https://github.com/jrl-umi3218/sch-core/workflows/CI%20of%20sch-core/badge.svg?branch=master)](https://github.com/jrl-umi3218/sch-core/actions?query=workflow%3A%22CI+of+sch-core%22)
[![Documentation](https://img.shields.io/badge/doxygen-online-brightgreen?logo=read-the-docs&style=flat)](http://jrl-umi3218.github.io/sch-core/doxygen/HEAD/index.html)


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
      year = {2014}
      month={June},
      volume={30},
      number={3},
      pages={666-678},
      keywords={Collision avoidance;Convergence;Optimization;Planning;Robots;Shape;Vectors;Bounding volume;continuous gradients of proximity distances;smooth and nonsmooth optimization;sphere-torus patches;strictly convex hulls},
      doi={10.1109/TRO.2013.2296332},
      ISSN={1552-3098},
      url = {https://sites.google.com/site/adrienescandehomepage/publications/2014_ITRO_Escande.pdf}
    }


License
-------

This library is provided under two licenses:

- The GPL-v2 version is the most complete, it includes inter-penetration depth computation based on the [SOLID](https://github.com/dtecta/solid3) code;
- The BSD-2-Clause version does not include this algorithm;

Note: the two versions have the same API and ABI.


Installation
------------


## Ubuntu LTS (16.04, 18.04, 20.04)

Note: the packaged version is the BSD-2-Clause library, if you require inter-penetration depth computation, you should build the library yourself.

You must first setup our package mirror:

```
curl -1sLf \
  'https://dl.cloudsmith.io/public/mc-rtc/stable/setup.deb.sh' \
  | sudo -E bash
```

You can also choose the head mirror which will have the latest version of this package:

```
curl -1sLf \
  'https://dl.cloudsmith.io/public/mc-rtc/stable/setup.deb.sh' \
  | sudo -E bash
```

You can then install the package:

```bash
sudo apt install libsch-core-dev
```

## Conan

Install the latest version using [conan](https://conan.io/)

```bash
conan remote add multi-contact https://api.bintray.com/conan/gergondet/multi-contact
# Install the latest release
conan install sch-core/latest@multi-contact/stable
# Or install the latest development version
# conan install sch-core/latest@multi-contact/dev
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

#### CMake options

- `SCH_BUILD_BSD`: If ON, build the library without its GPL components (Default: OFF)

Indentation
------------

    astyle --style=allman --lineend=linux --indent=spaces=2 --indent-namespaces


