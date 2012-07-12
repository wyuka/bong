bong
====

Description
-----------

A library that allows reading and editing of non-po translation files.

Build Requirements
------------------

You need to have the following packages installed (for Fedora)

cmake
automake
glib2-devel
qt-devel

Build instructions
------------------

To build, use the following commands from the source tree.

mkdir -p build
cd build
cmake ..
make

To install, use this command from the same directory (as root, if necessary)

make install

Build options
-------------

While using the cmake command, you can modify its behaviour using the following flags

-DCMAKE_INSTALL_PREFIX=<path to your install prefix>
This will install the libraries to a location other than /usr/local (the default install prefix)

-DBUILD_TESTS=off
This will prevent the tests from building

-DBUILD_DTD_TESTS=off
This will prevent the tests of the Mozilla DTD backend of the Bong library (using GLib)

-DBUILD_PROPERTIES_TESTS=off
This will prevent the tests of the Mozilla Properties backend of the Bong library (using GLib)

-DBUILD_PROPERTIES_QT_TESTS=off
This will prevent the tests of the Qt wrapper to the Mozilla Properties backend of the Bong library.
