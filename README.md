# Linker

This is a linker for a made up assembly language. The machine has a memory with 216 16-bit words, a program counter register, PC and an accumulator registerm, ACC, both with 16 bits. There are three instruction types:

 1. Opcode
 2. Opcode Address
 3. Opcode Address Address

For more info on the machine, check the [assembler](https://github.com/MatTerra/montador).
## First Steps

This program depends on cmake, make and g++ to build. It uses C++11. Please install cmake, make and C++11 before proceeding.

### Compiling

To compile the project, follow the steps below.

First, run cmake to generate the makefiles:
```
cmake -B build
```

Then, go into the build dir, and run make (you may add `-j<cores>` to speed up compilation):
```
cd build && make
```

After that, the program is compiled and available in the src folder of the build dir.
```
cd src && ls ligador
```

You may copy it to the folder you would like to use and run it as following. The o_files may be the absolute or relative paths to the assembled object files that compose the program. They must have an .o extension. The `ligador` will generate an .obj file in the same folder as the first object file if it succeeds:
```
./ligador <o_files>
```

## Implementation Details

The assembly language expects the `PUBLIC` and `EXTERN` directives to be used in the `TEXT` section only.
This linker operates on files with the following format

```asm
H: main
H: 6
H: 010100
H: U externSymbol 1 3
H: D publicSymbol 5
T: 01 00 13 00 14 05
```

There may be as many use table lines and definition table lines as there are public and extern directives.
First the source code of all the modules is concatenated and the offsets are applied. Then, the use table is resolved.

## Running Unit Tests

The project was developed through an TDD approach, thus, it contains a thorough test suite, which is built with the executable. To run it, access the tests folder in the build dir and run the following command:

```
./ligador_tst
```

## Build tools

* [CMake](https://cmake.org/)
* [Make](https://www.gnu.org/software/make/)

## Contributing

This repository doesn't accept contributions until December 2021. If you must contribute, please reach out for the author.

## Authors

* **Mateus Berardo** - *Initial Work* - [MatTerra](https://github.com/MatTerra)

Also check out the [contributors](graphs/contributors).

## License

The author reserves all rights to the code hereby provided. It is strictly prohibited to copy or modify the code provided. It is allowed to use the code for educational purposes only and only if the author is credited. For any other use or more permissive conditions, contact the author. Any exceptions made by the author for third-parties does not mean changes in this license's terms for other people.

## Acknoledgments

* **Billie Thompson** - *README template* - [PurpleBooth](https://github.com/PurpleBooth)

