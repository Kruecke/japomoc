# JaPomoC
Just another Pokémon Clone

[![Build Status](https://travis-ci.org/Kruecke/japomoc.svg)](https://travis-ci.org/Kruecke/japomoc)

## Installation
To download and install JaPomoC, make sure you have Git, Cmake and your basic build tools installed.

### Installing on Linux
On Debian-like systems, you can get your basic tools by installing the following packages.
```
# apt-get install git cmake build-essential
```

#### Building SFML
JaPomoC depends on the "Simple and Fast Multimedia Library". If you are running a Debian-like system, you can install SFML with the following instructions. For other operating systems, have a look at http://www.sfml-dev.org/tutorials/.

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

#### Building JaPomoC
As of today, just clone this repository and do a normal cmake installation.
```
$ git clone --recursive https://github.com/Kruecke/japomoc.git
$ cd japomoc
$ mkdir build && cd build
$ cmake ..
$ make
```
Rules for `make install` are not implemented yet. Just run the game from the current build directory by executing `$ ./japomoc`.

### Installing on Windows
These instructions base on Visual Studio 2013 Professional, but the free "Express" version should be absolutely sufficient for the build process. You can get a copy of it at http://www.visualstudio.com. Besides that, you need Git to download the recent copy of JaPomoC. You can get this free software at http://git-scm.com/download/win. Last but not least, get a copy of Cmake at http://www.cmake.org/. Install these three tools and move on to the next step.

#### Downloading JaPomoC
Start the installed Program "Git Bash" to open a command prompt and use `cd` to switch to a directory of your choise where you want to download JaPomoC to. Then run git to download the latest version of JaPomoC.
```
$ cd path/to/some/folder # this is optional
$ git clone https://github.com/Kruecke/japomoc.git
```

Don't close "Git Bash" just yet. You need it later on.

#### Getting SFML
JaPomoC depends on the "Simple and Fast Multimedia Library". You could check out JaPomoCs submodules to get the latest sources, but most times it is more convenient to just download a prebuild version from http://www.sfml-dev.org/download.php. Make sure you download the files for your version of Visual Studio and grab a 32 bit version, otherwise you have to alter this instruction slightly later on. Once you've downloaded the archive, open your file explorer, extract the containing folder `SFML-2.x` and copy it's contents to `japomoc` -> `lib` -> `SFML`.

#### Building JaPomoC
To build the Visual Studio solution for JaPomoC, switch back to "Git Bash" and `cd` into the JaPomoC folder.
```
$ cd japomoc
```

Next, type in the following lines to create the Visual Studio solution files in a subfolder called `build` and to copy some SFML binaries to our `build` folder.
```
$ mkdir build && cd build
$ cmake -D SFML_ROOT=lib/SFML ..
$ cp ../lib/SFML/bin/* .
```

Finally, open your file explorer once again, browse to `japomoc` -> `build` and double-click `japomoc.sln` to load the solution into Visual Studio. In your `Solution Explorer` (probably on the right side of your screen), right-click the `japomoc` project and choose `Set as StartUp Project`. Now you can click the green "Play" arrow at the top (or push F5) to run the game. (This can take a moment the first time you run it.)

Unfortunately there is no installation routine yet. You have to run the game from Visual Studio (or from the `build` directory via command line). Sorry. :P
