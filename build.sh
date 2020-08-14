# build everything
#!/bin/bash
make -j18 CONFIG=debug
make -j18 CONFIG=release
make -j18 doc
make -j18 clean
