# JaPomoC
Just another Pokémon Clone

## Installation
To download and install JaPomoC, make sure you have Git, Cmake and your basic build tools installed.

### Installing on Linux
On Debian-like systems, you can get your basic tools by installing the following packages.
```
# apt-get install git cmake build-essential
```

#### Installing SFML
JaPomoC depends on the "Simple and Fast Multimedia Library". If you are running a Debian-like system, you can install SFML with the following instructions. For other operating systems, have a look at http://www.sfml-dev.org/tutorials/2.2/.

As of now, it seems that there is no current or well packed repository version of SFML available, so you have to build SFML from source. Hopefully, this can be changed in the future.

Install the necessary dependencies from the repositories.
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

#### Installing JaPomoC
As of today, just clone this repository and do a normal cmake installation.
```
$ git clone https://github.com/Kruecke/japomoc.git
$ cd japomoc
$ mkdir build && cd build
$ cmake ..
$ make
```
Rules for `make install` are not implemented yet. Just run the game from the current build directory by executing `$ ./japomoc`.

### Installing on Windows
These instructions base on Visual Studio 2013, but a free "Express" version should be absolutely sufficient for the build process. You can get a copy of it at http://www.visualstudio.com. Besides that, you need Git to download the recent copy of JaPomoC. You can get this free software at http://git-scm.com/download/win. Last but not least, get a copy of Cmake at http://www.cmake.org/. Install these three tools and move on to the next step.

#### Installing SFML
JaPomoC depends on the "Simple and Fast Multimedia Library". Get a copy of the library for your version of Visual Studio at http://www.sfml-dev.org/download/sfml/2.2/. Grab a 32 bit version, otherwise you have to alter this instruction slightly later on. Create a folder `Sources` somewhere and place the extracted folder `SFML-2.2` from the downloaded archive into it.

#### Installing JaPomoC
Next, start the installed Program "Git Bash" and switch to your created `Sources` folder.
```
$ cd my/path/to/Sources
```
Now download JaPomoC and generate the Visual Studio solution files. Make sure that you are in the directory where you previously placed the `SFML-2.2` folder. You can verify that by typing `$ ls` in the command prompt.
```
$ git clone https://github.com/Kruecke/japomoc.git
$ cd japomoc
$ mkdir build && cd build
$ cmake -D SFML_ROOT=../SFML-2.2 ..
$ cp ../../SFML-2.2/bin/* .
```

Finally, open your file explorer and browse to `Sources` -> `japomoc` -> `build` and double-click `japomoc.sln` to load the solution into Visual Studio. In your `Solution Explorer` (probably on the right side of your screen), right-click the `japomoc` project and choose `Set as StartUp Project`. Now you can click the green "Play" arrow at the top (or push F5) to run the game.

There is no installation routine yet. Sorry. :P
