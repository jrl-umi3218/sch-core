

=== Documentation ===
Implementation of the convex hulls detailed in:

@article{escande:itro:2014,
  author = {Adrien Escande and Sylvain Miossec and Mehdi Benallegue and Abderrahmane Kheddar},
  title = {A Strictly Convex Hull for Computing Proximity Distances with Continuous Gradients},
  journal = {IEEE Transactions on Robotics},
  year = {2014},
  note = {in press},
  url = {https://sites.google.com/site/adrienescandehomepage/publications/2014_ITRO_Escande.pdf}
}


=== Installation ===
Building using cmake:
- create a new build directory
- run cmake .. in this directory 
  (you probably want to define CMAKE_INSTALL_PREFIX)
- make
- make install

=== Indentation ===
astyle --style=allman --lineend=linux --indent=spaces=2

