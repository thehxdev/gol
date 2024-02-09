# GoL

[Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) written in C.


## Build

First make sure that a C compiler like `gcc` or `clang`, `cmake` and `make` are installed.

Clone the repository:
```bash
git clone --depth 1 --branch=main https://github.com/thehxdev/gol
cd gol
```

Then Build GoL:
```bash
mkdir build
cmake -B build/ -S .
cmake --build build/
```

## Usage
Once you built GoL, execute it from `build/` directory.
```bash
./build/gol
```


## Nix

> [!NOTE]
> Make sure that nix experimental features (`nix-command` and `flakes`) are enabled.

Execute GoL directly as a Nix Flake:
```bash
nix run github:thehxdev/gol
```
