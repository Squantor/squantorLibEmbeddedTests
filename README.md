# Unittests for libEmbedded
This project contains the unittests for the [libEmbedded](https://github.com/Squantor/libEmbedded) library.
## Checking out
use ```git clone --recurse-submodules https://github.com/Squantor/libEmbeddedTests.git``` to clone the repository and its submodules.
## Compiling
This project uses Gnu Make to build. Use ```make``` to build the project with the default configuration which is Debug mode. To explicitly build a configuration use ```make CONFIG=configuration```, valid confugrations are ```debug``` and ```release```.

To clean all the build output files use ```make clean```.

To build the documentation use ```make doc```, this depends on doxygen.

To build everything and delete the results run ```./build.sh```, it is used as a quick check if everything works.
### Depedencies
This project has a few dependencies:
* [libEmbedded](https://github.com/Squantor/libEmbedded) library, as it tests this
* [MinUnit](https://github.com/Squantor/MinUnit) minimal unittest library, used in the tests themselves.
