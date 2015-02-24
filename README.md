# JaPomoC
Just another Pokémon Clone

TODO: Have a look at http://www.sfml-dev.org/documentation/2.2/
      This might be a good alternative to GLFW, maybe even a better one.

## Installing SFML
Have a look at http://www.sfml-dev.org/tutorials/2.2/. On Debian, install the following dependencies.
```
# apt-get install libglu1-mesa-dev libx11-xcb-dev libxrandr-dev libfreetype6-dev libglew-dev libsndfile1-dev libopenal-dev libxcb-icccm4-dev libxcb-image0-dev libxcb-randr0-dev libxcb-util0-dev libudev-dev libjpeg8-dev
```
Next build and install SFML
```
$ git clone https://github.com/LaurentGomila/SFML.git
$ cd SFML
$ mkdir build && cd build
$ make
# make install
```
