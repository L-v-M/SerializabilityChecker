# Serializability Checker

Checks if a schedule is serializable.

## Usage

In order to build and run the program execute the following commands:

```bash
mkdir build
cd build
cmake -G "Ninja" -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
ninja serializability-checker
./src/serializability-checker w 1 x r 2 x w 2 y r 3 y w 3 z r 1 z
```

## Tests

To additionally build and run the tests execute the following commands
([Catch2 test framework](https://github.com/catchorg/Catch2) must be installed on your system):

````bash
cd build
ninja tests
cd tests
ctest
```
