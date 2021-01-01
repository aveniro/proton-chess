<h3 align="center">
    <img alt="Logo" src="media/chess-clock.svg" width="350"/>
</h3>

<h3 align="center">
    Tiny, embeddable chess.
</h3>

<h3 align="center">
    <img alt="GitHub Workflow Status" src="https://img.shields.io/github/workflow/status/NateSeymour/proton-chess/ci-linux-x86_64">
    <img alt="Made in France" src="https://img.shields.io/badge/made_in-france-blue">
    <img alt="Builds with CMake" src="https://img.shields.io/badge/builds_with-cmake-brightgreen">
</h3>

Chess should be for everyone. Proton Chess is a chess engine that aims to be as small and portable as possible. 

## Building

Proton Chess doesn't have any dependencies. That means that building it is a rather simple affair. 

All you need is `cmake` and a `C99` compatible compiler.

```shell
# Clone the GitHub repository
git clone https://github.com/NateSeymour/proton-chess.git
cd proton-chess

# Make build directory
mkdir build && cd build

# Configure the project (see build options below)
cmake .. -DBUILD_TYPE=Release 

# Build project
cmake --build . --target protonchess

# Optional: Build latest documentation (requires doxygen)
cmake --build . --target documentation

# Optional: Build and run tests (requires -DENABLE_TESTING=ON)
cmake --build . --target tests
./tests
```

### Build Configuration

Option | Possible Values | Description | Default
---|---|---|---
`-DBUILD_TYPE` | `Release`, `Debug` | Controls build optimization and the inclusion of debugging symbols. | `Debug`
`-DFEN_EXTENSIONS` | `ON`, `OFF` | Inclusion of the FEN Notation extensions for Proton Chess. These can be disabled with `NO` to produce smaller binaries. | `ON`
