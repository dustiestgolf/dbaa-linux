# Particle Mace

There have been many trials and tribulations getting Particle Mace to run on linux. This will hopefully be a useful howto to get it running more easily.

## openFramework

The first thing to do is to download [openFramework 0.9.8](https://openframeworks.cc/versions/v0.9.8/of_v0.9.8_linux64_release.tar.gz). Extract this somewhere handy I will refer to this folder as `OF_0.9.8/` Before compiling we have to fix some bugs and install some dependencies. 

### source edits

To compile successfully, open `libs/openFrameworks/utils/ofConstants.h`.
Comment out line 183, or whichever says
```
#include <GL/glext.h>
```
Edit `scripts/apothecary/formulas/poco/poco.sh` editing lines to read
```
VER=1.7.7-release
GIT-TAG=1.7.7-release
```
Finally edit `addons/ofxVectorGraphics/libs/CreEPS.cpp` by moving the lines 
```
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
```
below the line`#include "CreEPS.hpp` 


### dependencies.

Using terminal install these packages (you will likely need to use sudo)

```
apt install curl libcurl3
apt install librtaudio4
apt install libjack0
apt install libjack-jackd2-dev
```
Starting from the directory you extracted oF to
```
cd OF_0.9.8/scripts/linux/ubuntu
sudo ./install_dependencies.sh
sudo ./install_codecs.sh
```

### compiling oF

oF doesnt come compiled so we have to compile it ourselves, run
```
cd OF_0.9.8/scripts/linux
./compileOF.sh
```

### check examples
Run these commands, the first will take a while. The second will bring the first example, close this to progress to the next. Compiling is the real test here but its good to make sure they run too. Some wont work, most will. Errors should only be stuff like missing resources. As long as stuff isn't crashing you should be okay.
```
cd OF_0.9.8/scripts/linux
./buildAllExamples.sh
./testAllExamples.sh
```
