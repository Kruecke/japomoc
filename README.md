# JaPomoC
Just another Pokémon Clone

## Installing GLFW
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
