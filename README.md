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
Make sure that your files will be found, if you use `/usr/local/` as your installation prefix.
```
$ echo "export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:\$PKG_CONFIG_PATH" >> ~/.profile
$ echo "export LD_LIBRARY_PATH=/usr/local/lib:\$LD_LIBRARY_PATH"           >> ~/.profile
```

## Installing GLFW (no longer needed)
On Debian, make sure you have `xorg-dev` and `libglu1-mesa-dev` installed. See http://www.glfw.org/docs/latest/compile.html for other operating systems.
```
$ git clone https://github.com/glfw/glfw.git
$ cd glfw
$ mkdir build && cd build
$ cmake -DBUILD_SHARED_LIBS=ON ..
$ make
# make install
```
Make sure that your files will be found, if you use `/usr/local/` as your installation prefix.
```
$ echo "export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:\$PKG_CONFIG_PATH" >> ~/.profile
$ echo "export LD_LIBRARY_PATH=/usr/local/lib:\$LD_LIBRARY_PATH"           >> ~/.profile
```
