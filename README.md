# Unittests for libEmbedded
This project contains the unittests for the [libEmbedded](https://github.com/Squantor/libEmbedded) library.
## Checking out
use ```git clone --recurse-submodules https://github.com/Squantor/libEmbeddedTests.git``` to clone the repository and its submodules.
## Building
To build the test suite execute:
```
make PROJECT=libEmbeddedTests
```
Building can be done with various configurations that set up flags and other settings, this configuration is set with the ```CONFIG``` variable. Valid configurations are ```release``` and ```debug``` where the ```debug``` configuration is default.
The ```release``` configuration has optimizations enabled (usually for size) and minimal included debugging information. The ```debug``` configuration has NO optimization and full debugging information.
For cleaning execute the following command:
```
make clean
```
To build the documentation use ```make doc```, this depends on doxygen.
### Depedencies
This project has a few dependencies:
* [squantorLibEmbedded](https://github.com/Squantor/squantorLibEmbedded) library, as it tests this
* [squantorMinUnit](https://github.com/Squantor/squantorMinUnit) minimal unittest library, used in the tests themselves.
