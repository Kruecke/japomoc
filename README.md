# JaPomoC
Just another Pokémon Clone

## Installation

### Installing SFML
If you are running a Debian-like system, you can install SFML with the following instructions. For other operating systems, have a look at http://www.sfml-dev.org/tutorials/2.2/.

First, have a look at the `libcsfml-dev` package in your repository. If it's version is 2.0 or greater, just go ahead, install the package and you're done for this step.

If the repository version is not recent enough, we have to build SFML from source. Install the necessary dependencies from the repositories.
```
# apt-get install libglu1-mesa-dev libx11-xcb-dev libxrandr-dev libfreetype6-dev libglew-dev libsndfile1-dev libopenal-dev libxcb-icccm4-dev libxcb-image0-dev libxcb-randr0-dev libxcb-util0-dev libudev-dev libjpeg8-dev
```

Next, clone the github repository, then build and install SFML.
```
$ git clone https://github.com/LaurentGomila/SFML.git
$ cd SFML
$ mkdir build && cd build
$ cmake ..
$ make
# make install
```

### Installing JaPomoC
As of today, just clone this repository and do a normal cmake installation.
```
$ git clone https://github.com/Kruecke/japomoc.git
$ cd japomoc
$ mkdir build && cd build
$ cmake ..
$ make
```
Rules for `make install` are not implemented yet. Sorry. :P
