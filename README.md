# TP3 Crypo_Eng

The goal of this exercise is to write a simple implementation of Pollard’s Kangaroo algorithm to compute the discrete logarithm of a group element whose exponent is known to lie in a “small” interval, without using (much) memory.

## Directory Structure

- **`src/`**: Contains source code
- **`test/`**: Contains test files to validate the implementation.
- **`tools/`**: Contains additional tools and helper functions.
- **`doc/`**: Documentation files including the subject of the project and the specifications.
- **`Makefile`**: Script to compile the project and run tests.
- **`README.md`**: This file.
- **`rendu.md`**: Summary or notes related to the project.

## Requirements

- **Compiler**: `gcc`
- **Flags**: The project uses `-Wall` and `-Wextra` flags for additional warnings.

## Compilation Instructions

To compile the project and build all tests:

```bash
make
```

To run all test executables:

```bash
make test
```

To remove all compiled object files and executables:

```bash
make clean
```
