# JaPomoC
Just another Pokémon Clone

## Installation
To download and install JaPomoC, make sure you have git, cmake and your basic build tools installed. On Debian-like systems, you can ensure that by installing the following packages.
```
# apt-get install git cmake build-essential
```

### Installing SFML
JaPomoC depends on the "Simple and Fast Multimedia Library". If you are running a Debian-like system, you can install SFML with the following instructions. For other operating systems, have a look at http://www.sfml-dev.org/tutorials/2.2/.

First, check the `libcsfml-dev` package in your repository. If it's version is 2.0 or greater, just go ahead, install the package and you can skip to "Installing JaPomoC".

If the repository version is not recent enough, you have to build SFML from source. Install the necessary dependencies from the repositories.
```
# apt-get install libx11-dev libxrandr-dev libgl1-mesa-dev libx11-xcb-dev libxcb-icccm4-dev libxcb-image0-dev libxcb-randr0-dev libxcb-util0-dev libudev-dev libglew-dev libjpeg8-dev libfreetype6-dev libopenal-dev libsndfile1-dev
```

Next, clone the github repository, build everything and finally install SFML.
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
